#include "lift.hpp"
#include "main.hpp"
#include "motor.hpp"
#include "mutexVar.hpp"
#include "pid.hpp"
#include "sensor.hpp"
#include <API.h>
#include <algorithm>

/** How many encoder ticks between fully retracted and extended. */
static constexpr int ticksForExtension = 80;

/** Power when fully raising the lift. */
static constexpr int upPower = 127;
/** Power when fully lowering the lift. Adjusted for gravity. */
static constexpr int downPower = -95;

static void setLeft(int power)
{
    using namespace motor;
    set(LIFT_LEFT, power);
}

static MutexVar<int> leftPos = 0;
static Encoder leftEnc = nullptr;
static PID leftPid;

static void setRight(int power)
{
    using namespace motor;
    set(LIFT_RIGHT, -power);
}

static MutexVar<int> rightPos = 0;
static Encoder rightEnc = nullptr;
static PID rightPid;

/** Whether the PID task should be deinitialized. */
static bool stopPid = true;

/**
 * Translates a power value from the PID loop to one that's suitable for the
 * lift.
 * @param power Desired motor power from -127 to 127.
 * @returns A scaled power value in the range [downPower, upPower] using the
 * constants defined above.
 */
static int translatePower(int power)
{
    // turn power into a nonnegative number
    power += 127;
    // scale units from -127/127 to downPower/upPower
    power = power * (upPower - downPower + 1) / 255;
    // translate back down into the negative space
    power += downPower;
    return power;
}

/** Updates the PIDs on the lift motors. */
static void pidLoop()
{
    if (stopPid)
    {
        lift::set(0);
        encoderShutdown(leftEnc);
        encoderShutdown(rightEnc);
        // delete this task
        taskDelete(nullptr);
        return;
    }

    leftPos = encoderGet(leftEnc);
    fputs("left: ", stdout);
    setLeft(translatePower(leftPid.update(leftPos, MOTOR_DELAY)));

    rightPos = encoderGet(rightEnc);
    fputs("right: ", stdout);
    setRight(translatePower(rightPid.update(rightPos, MOTOR_DELAY)));
}

void lift::enablePid()
{
    using namespace sensor;

    if (isPidEnabled()) return;
    stopPid = false;

    leftEnc = encoderInit(LIFT_LEFT_TOP, LIFT_LEFT_BOTTOM, /*reverse*/ true);
    encoderReset(leftEnc);
    leftPos.init();
    leftPid.init(4.f / 31, 0, 0);

    rightEnc = encoderInit(LIFT_RIGHT_TOP, LIFT_RIGHT_BOTTOM,
        /*reverse*/ false);
    encoderReset(rightEnc);
    rightPos.init();
    rightPid.init(4.f / 31, 0, 0);

    taskRunLoop(pidLoop, MOTOR_DELAY);
}

bool lift::isPidEnabled()
{
    return !stopPid;
}

void lift::disablePid()
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

void lift::set(int direction)
{
    int power;
    if (direction < 0) power = downPower;
    else if (direction > 0) power = upPower;
    else power = 0;
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
