#include "lift.hpp"
#include "main.hpp"
#include "motor.hpp"
#include "sensor.hpp"
#include <cmath>

using namespace motor;
using namespace sensor;

/** Left lift encoder. */
static Encoder leftEncoder = nullptr;

/** Right lift encoder. */
static Encoder rightEncoder = nullptr;

/** The event loop object. */
static TaskHandle eventLoopTask = nullptr;

/** The desired position of the lift. */
static float targetPosition = 0;

/** How many encoder values between retracted and fully extended. */
static constexpr int ticksForExtension = 360;

/** Length of a tick of encoder */
static constexpr int tickTime = 15;

void lift::initEncoders()
{
    leftEncoder = encoderInit(LIFT_LEFT_TOP, LIFT_LEFT_BOTTOM,
        /*reverse=*/ true);
    rightEncoder = encoderInit(LIFT_RIGHT_TOP, LIFT_RIGHT_BOTTOM,
        /*reverse=*/ false);
}

static void eventLoopTick(void*)
{
    unsigned long lastTaskRunTime = millis();

    while (true)
    {
        // Do happy things
        float targetLiftPosition = targetPosition;
        int targetEncoderValue = ticksForExtension * targetLiftPosition;

        // TODO: handle syncing of multiple encoders
        int currentEncoderValue = encoderGet(rightEncoder);

        // Determine which way we should go
        int encoderDelta = targetEncoderValue - currentEncoderValue;

        // Returns power (clamped to [-127, 127]) given encoder delta.
        int power = round(127 * tanh((1.0f / ticksForExtension) * encoderDelta));
        lift::set(power);

        taskDelayUntil(&lastTaskRunTime, tickTime);
    }
}

void lift::initEventLoop()
{
    eventLoopTask = taskCreate(eventLoopTick, TASK_DEFAULT_STACK_SIZE, nullptr, TASK_PRIORITY_DEFAULT);
}

void lift::setLiftPosition(float position)
{
    targetPosition = position;
}

void lift::set(int power)
{
    lock();
    set(LIFT_LEFT, power);
    set(LIFT_RIGHT, -power);
    unlock();
}
