#include "lift.hpp"
#include "main.hpp"
#include "motor.hpp"
#include "pid.hpp"
#include "sensor.hpp"
#include <API.h>
#include <algorithm>
#include <cmath>

using namespace motor;
using namespace sensor;

/** How many encoder ticks between retracted and fully extended. */
static constexpr int ticksForExtension = 80;

/** Left encoder. */
static Encoder leftEnc = nullptr;
/** Right encoder. */
static Encoder rightEnc = nullptr;

static int getLeftPos()
{
    return encoderGet(leftEnc);
}

static void setLeft(int power)
{
    motor::lock();
    motor::set(LIFT_LEFT, power);
    motor::unlock();
}

static int getRightPos()
{
    return encoderGet(rightEnc);
}

static void setRight(int power)
{
    motor::lock();
    motor::set(LIFT_RIGHT, -power);
    motor::unlock();
}

/** Left side. */
static PID leftPid{ 1, 0, 0, getLeftPos, setLeft };
/** Right side. */
static PID rightPid{ 1, 0, 0, getRightPos, setRight };

static void liftEventLoop()
{
    leftPid.update(MOTOR_DELAY);
    rightPid.update(MOTOR_DELAY);
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

    taskRunLoop(liftEventLoop, MOTOR_DELAY);
}

float lift::getCurrentPos()
{
    // average the two sides
    return (leftPid.getCurrentPos() + rightPid.getCurrentPos()) / 2;
}

void lift::setTargetPos(float position)
{
    // convert position to encoder ticks
    position = ticksForExtension * std::max(0.f, std::min(position, 1.f));
    leftPid.setTargetPos(position);
    rightPid.setTargetPos(position);
}

void lift::set(int power)
{
    setLeft(power);
    setRight(power);
}
