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

/** The event loop task handle. */
static TaskHandle eventLoopTask = nullptr;

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

static int getRightPos()
{
    return encoderGet(rightEnc);
}

static int getLiftPos()
{
    return (getLeftPos() + getRightPos()) / 2;
}

static PID liftPid{ 1, 0, 0, getLiftPos, lift::set };
static Velocity leftVel{ getLeftPos };
static Velocity rightVel{ getRightPos };

void lift::initEncoders()
{
    leftEnc = encoderInit(LIFT_LEFT_TOP, LIFT_LEFT_BOTTOM, /*reverse=*/ true);
    rightEnc = encoderInit(LIFT_RIGHT_TOP, LIFT_RIGHT_BOTTOM,
        /*reverse=*/ false);
}

/** Learning rate of the power amplifier variables. */
static constexpr float velLearningRate = 0.1;

/** Left power amplifier. */
static float kLeft = 1;
/** Right power amplifier. */
static float kRight = 1;

static void eventLoopTick()
{
    // update position/velocity tracker
    leftVel.update(MOTOR_DELAY);
    rightVel.update(MOTOR_DELAY);

    // learn how much faster one motor is than the other
    const float velError = velLearningRate *
        (leftVel.getVel() - rightVel.getVel());
    kLeft -= velError;
    kRight += velError;
}

void lift::initEventLoop()
{
    eventLoopTask = taskRunLoop(eventLoopTick, MOTOR_DELAY);
}

void lift::setLiftPosition(float position)
{
    liftPid.setTargetPos(ticksForExtension *
            std::max(0.f, std::min(position, 1.f)));
}

void lift::set(int power)
{
    lock();
    set(LIFT_LEFT, kLeft * power);
    set(LIFT_RIGHT, kRight * -power);
    unlock();
}
