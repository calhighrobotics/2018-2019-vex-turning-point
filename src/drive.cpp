#include "drive.hpp"
#include "main.hpp"
#include "motor.hpp"
#include "pid.hpp"
#include "sensor.hpp"
#include <algorithm>

using namespace motor;
using namespace sensor;

/** Approximation of pi. */
#define PI 22/7
/** Approximation of the reciprocal of pi. */
#define PI_RECIPROCAL 7/22

/** Omni wheel radius in 1/16in. */
static constexpr int wheelRadius = 32;
/** Distance between wheels in 1/16in. */
static constexpr int botRadius = 120;

/** Left drive train encoder. */
static Encoder leftEnc = nullptr;

void drive::initEncoders()
{
    leftEnc = encoderInit(DT_LEFT_TOP, DT_LEFT_BOTTOM, /*reverse=*/ false);
}

void drive::left(int power)
{
    set(DRIVE_LF, power);
    set(DRIVE_LB, power);
}

void drive::right(int power)
{
    set(DRIVE_RF, -power);
    set(DRIVE_RB, -power);
}

void drive::stop()
{
    left(0);
    right(0);
}

/** Parameters for the `drive::straight` functions. */
struct StraightTaskArgs
{
    int distance;
    bool decelerate;
    int tolerance;
};

/**
 * TaskCode for driving forward/backward.
 * @param params A `malloc`'d pointer to a StraightTaskArgs object.
 */
static void straightTask(void* params)
{
    auto* args = static_cast<StraightTaskArgs*>(params);
    drive::straightSync(args->distance, args->decelerate, args->tolerance);
    free(args);
}

TaskHandle drive::straight(int distance, bool decelerate, int tolerance)
{
    auto* params = static_cast<StraightTaskArgs*>(malloc(
            sizeof(StraightTaskArgs)));
    params->distance = distance;
    params->decelerate = decelerate;
    params->tolerance = tolerance;

    return taskCreate(straightTask, TASK_DEFAULT_STACK_SIZE, params,
        TASK_PRIORITY_DEFAULT - 1);
}

void drive::straightSync(int distance, bool decelerate, int tolerance)
{
    // calculate number of encoder ticks needed
    const int target = distance * 180 * PI_RECIPROCAL / wheelRadius;

    if (decelerate)
    {
        PID pid;
        pid.init(2, 0, 1);
        pid.setTargetPos(target);

        int ticks;
        encoderReset(leftEnc);
        unsigned long wakeTime = millis();
        while (abs(ticks = encoderGet(leftEnc)) < abs(target) - tolerance)
        {
            print("straight pid: ");
            const int power = pid.update(ticks, MOTOR_DELAY);
            left(power);
            right(power);
            taskDelayUntil(&wakeTime, MOTOR_DELAY);
        }

        // stop driving once target is reached
        stop();
    }
    else
    {
        const int power = distance < 0 ? -127 : 127;
        left(power);
        right(power);

        int ticks;
        encoderReset(leftEnc);
        while (abs(ticks = encoderGet(leftEnc)) < abs(target) - tolerance)
        {
            printf("straight no pid: target=%d, enc=%d\n", target, ticks);
            delay(MOTOR_DELAY);
        }
    }
}

/** Parameters for the `drive::turn` functions. */
struct TurnTaskArgs
{
    int angle;
    int radius;
    int outer;
    int tolerance;
};

/**
 * TaskCode for turning.
 * @param params A `malloc`'d pointer to a TurnTaskArgs object.
 */
static void turnTask(void* params)
{
    auto* args = static_cast<TurnTaskArgs*>(params);
    drive::turnSync(args->angle, args->radius, args->outer, args->tolerance);
    free(args);
}

TaskHandle drive::turn(int angle, int radius, int outer, int tolerance)
{
    auto* params = static_cast<TurnTaskArgs*>(malloc(sizeof(TurnTaskArgs)));
    params->angle = angle;
    params->radius = radius;
    params->outer = outer;
    params->tolerance = tolerance;

    return taskCreate(turnTask, TASK_DEFAULT_STACK_SIZE, params,
        TASK_PRIORITY_DEFAULT - 1);
}

void drive::turnSync(int angle, int radius, int outer, int tolerance)
{
    if (angle == 0) return;

    // calculate ratio between inner power and outer power
    const float innerRatio = static_cast<float>(radius - botRadius) /
        (radius + botRadius);

    // calculate left encoder target ticks
    int target;
    if (angle > 0) target = (radius + botRadius) * angle / wheelRadius;
    else target = (radius - botRadius) * angle / wheelRadius;

    if (outer == 0)
    {
        PID pid;
        if (angle > 0) pid.init(2, 0, 1);
        else if (angle < 0)
        {
            // leftEnc is on the inner part of the circle so it needs to go
            //  slower
            pid.init(2, 0, 1, -127 * innerRatio, 127 * innerRatio);
        }
        pid.setTargetPos(target);

        int ticks;
        encoderReset(leftEnc);
        unsigned long wakeTime = millis();
        while (abs(ticks = encoderGet(leftEnc)) < abs(target) - tolerance)
        {
            print("turn pid: ");
            const int leftPower = pid.update(ticks, MOTOR_DELAY);
            int rightPower = leftPower;
            if (angle > 0) rightPower *= innerRatio;
            if (angle < 0) rightPower /= innerRatio;
            left(leftPower);
            right(rightPower);
            taskDelayUntil(&wakeTime, MOTOR_DELAY);
        }

        // stop driving once target is reached
        stop();
    }
    else
    {
        int leftPower = outer;
        int rightPower = outer * innerRatio;
        // if ccw, the left side would be the inner part of the turning circle
        if (angle < 0) std::swap(leftPower, rightPower);

        left(leftPower);
        right(rightPower);
        int ticks;
        encoderReset(leftEnc);
        while (abs(ticks = encoderGet(leftEnc)) < abs(target) - tolerance)
        {
            printf("turn no pid: target=%d, enc=%d\n", target, ticks);
            delay(MOTOR_DELAY);
        }
    }
}
