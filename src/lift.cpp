#include "lift.hpp"
#include "main.hpp"
#include "motor.hpp"
#include "mutexVar.hpp"
#include "pid.hpp"
#include "sensor.hpp"
#include <API.h>
#include <algorithm>

using namespace motor;
using namespace sensor;

/** How many encoder ticks between fully retracted and extended. */
static constexpr int ticksForExtension = 80;

static void setLeft(int power)
{
    set(LIFT_LEFT, power);
}

static MutexVar<int> leftPos = 0;
static Encoder leftEnc = nullptr;
static PID leftPid;

static void setRight(int power)
{
    set(LIFT_RIGHT, -power);
}

static MutexVar<int> rightPos = 0;
static Encoder rightEnc = nullptr;
static PID rightPid;

/** Whether the PID task should be deinitialized. */
static bool stopPid = false;

/** Updates the PIDs on the lift motors. */
static void pidLoop()
{
    if (stopPid)
    {
        set(0);
        encoderShutdown(leftEnc);
        encoderShutdown(rightEnc);
        taskDelete(nullptr);
        return;
    }

    leftPos = encoderGet(leftEnc);
    fputs("left: ", stdout);
    setLeft(leftPid.update(leftPos, MOTOR_DELAY));

    rightPos = encoderGet(rightEnc);
    fputs("right: ", stdout);
    setRight(rightPid.update(rightPos, MOTOR_DELAY));
}

void lift::init()
{
    leftEnc = encoderInit(LIFT_LEFT_TOP, LIFT_LEFT_BOTTOM, /*reverse*/ true);
    encoderReset(leftEnc);
    leftPos.init();
    leftPid.init(1.f / 31, 0, 0);

    rightEnc = encoderInit(LIFT_RIGHT_TOP, LIFT_RIGHT_BOTTOM,
        /*reverse*/ false);
    encoderReset(rightEnc);
    rightPos.init();
    rightPid.init(1.f / 31, 0, 0);

    taskRunLoop(pidLoop, MOTOR_DELAY);
}

void lift::kill()
{
    stopPid = true;
}

float lift::getCurrentPos()
{
    // average the two sides and convert to 0-1 scalar
    return (leftPos + rightPos) / (2.f * ticksForExtension);
}

void lift::setTargetPos(float position)
{
    position = std::max(0.f, std::min(position, 1.f));
    // convert position to encoder ticks
    int target = ticksForExtension * position;
    printf("target pos: %.2f, target enc: %d\n", position, target);
    leftPid.setTargetPos(target);
    rightPid.setTargetPos(target);
}

void lift::set(int power)
{
    setLeft(power);
    setRight(power);
}

void lift::kP(float inc)
{
    leftPid.kP += inc;
    rightPid.kP += inc;
}

float lift::kP()
{
    // both PIDs are handled separately, but they should have similar constants
    return (leftPid.kP + rightPid.kP) / 2;
}
