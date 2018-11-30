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
static PID leftPid{ 1, 0, 0 };

static void setRight(int power)
{
    set(LIFT_RIGHT, -power);
}

static MutexVar<int> rightPos = 0;
static Encoder rightEnc = nullptr;
static PID rightPid{ 1, 0, 0 };

/** Updates the PIDs on the lift motors. */
static void pidLoop()
{
    leftPos = encoderGet(leftEnc);
    setLeft(leftPid.update(leftPos, MOTOR_DELAY));

    rightPos = encoderGet(rightEnc);
    setRight(rightPid.update(rightPos, MOTOR_DELAY));
}

void lift::init()
{
    leftEnc = encoderInit(LIFT_LEFT_TOP, LIFT_LEFT_BOTTOM, /*reverse*/ true);
    encoderReset(leftEnc);
    leftPos.init();
    leftPid.init();

    rightEnc = encoderInit(LIFT_RIGHT_TOP, LIFT_RIGHT_BOTTOM,
        /*reverse*/ false);
    encoderReset(rightEnc);
    rightPos.init();
    rightPid.init();

    taskRunLoop(pidLoop, MOTOR_DELAY);
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
    printf("target pos: %.2f, enc: %d", position, target);
    leftPid.setTargetPos(target);
    rightPid.setTargetPos(target);
}

void lift::set(int power)
{
    setLeft(power);
    setRight(power);
}
