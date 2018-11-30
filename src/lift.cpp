#include "lift.hpp"
#include "main.hpp"
#include "motor.hpp"
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

static Encoder leftEnc = nullptr;
static int leftPos = 0;
static PID leftPid{ 1, 0, 0 };

static void setRight(int power)
{
    set(LIFT_RIGHT, -power);
}

static Encoder rightEnc = nullptr;
static int rightPos = 0;
static PID rightPid{ 1, 0, 0 };

static void pidLoop()
{
    leftPos = encoderGet(leftEnc);
    setLeft(leftPid.update(leftPos, MOTOR_DELAY));

    rightPos = encoderGet(rightEnc);
    setRight(rightPid.update(rightPos, MOTOR_DELAY));
}

void lift::init()
{
    leftEnc = encoderInit(LIFT_LEFT_TOP, LIFT_LEFT_BOTTOM, /*reverse=*/ true);
    encoderReset(leftEnc);
    leftPid.init();

    rightEnc = encoderInit(LIFT_RIGHT_TOP, LIFT_RIGHT_BOTTOM,
        /*reverse=*/ false);
    encoderReset(rightEnc);
    rightPid.init();

    taskRunLoop(pidLoop, MOTOR_DELAY);
}

float lift::getCurrentPos()
{
    // average the two sides
    return (leftPos + rightPos) / 2;
}

void lift::setTargetPos(float position)
{
    // convert position to encoder ticks
    int target = ticksForExtension * std::max(0.f, std::min(position, 1.f));
    printf("target enc: %d", target);
    leftPid.setTargetPos(target);
    rightPid.setTargetPos(target);
}

void lift::set(int power)
{
    setLeft(power);
    setRight(power);
}
