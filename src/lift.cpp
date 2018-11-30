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

static int getLeftPos()
{
    mutexTake(leftPosMutex, 0);
    int pos = leftPos;
    mutexGive(leftPosMutex);
    return pos;
}

static void setLeft(int power)
{
    set(LIFT_LEFT, power);
}

static int leftPos = 0;
static Mutex leftPosMutex = nullptr;
static Encoder leftEnc = nullptr;
static PID leftPid{ 1, 0, 0 };

static int getRightPos()
{
    mutexTake(rightPosMutex, 0);
    int pos = rightPos;
    mutexGive(rightPosMutex);
    return pos;
}

static void setRight(int power)
{
    set(LIFT_RIGHT, -power);
}

static int rightPos = 0;
static Mutex rightPosMutex = nullptr;
static Encoder rightEnc = nullptr;
static PID rightPid{ 1, 0, 0 };

/** Updates the PIDs on the lift motors. */
static void pidLoop()
{
    mutexTake(leftPosMutex, 0);
    leftPos = encoderGet(leftEnc);
    int value = leftPos;
    mutexGive(leftPosMutex);
    setLeft(leftPid.update(value, MOTOR_DELAY));

    mutexTake(rightPosMutex, 0);
    rightPos = encoderGet(rightEnc);
    int value = leftPos;
    mutexGive(rightPosMutex);
    setRight(rightPid.update(value, MOTOR_DELAY));
}

void lift::init()
{
    leftPosMutex = mutexCreate();
    leftEnc = encoderInit(LIFT_LEFT_TOP, LIFT_LEFT_BOTTOM, /*reverse*/ true);
    encoderReset(leftEnc);
    leftPid.init();

    rightPosMutex = mutexCreate();
    rightEnc = encoderInit(LIFT_RIGHT_TOP, LIFT_RIGHT_BOTTOM,
        /*reverse*/ false);
    encoderReset(rightEnc);
    rightPid.init();

    taskRunLoop(pidLoop, MOTOR_DELAY);
}

float lift::getCurrentPos()
{
    // average the two sides and convert to 0-1 scalar
    return(getLeftPos() + getRightPos()) / (2.f * ticksForExtension);
}

void lift::setTargetPos(float position)
{
    position = std::max(0.f, std::min(position, 1.f))
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
