#include "capIntake.hpp"
#include "motor.hpp"

using namespace motor;

/** Wrist rotation power. */
static constexpr int wristPower = 127;
/** Servo position up. */
static constexpr int pitchUp = 90;
/** Servo position down. */
static constexpr int pitchDown = 0;

void capIntake::rotate(int direction)
{
    lock();
    set(WRIST, wristPower * direction);
    unlock();
}

void capIntake::setup()
{
    pitch(-1);
}

void capIntake::pitch(int direction)
{
    if (direction == 1)
    {
        lock();
        set(CAP_PITCH, pitchDown);
        unlock();
    }
    else if (direction == -1)
    {
        lock();
        set(CAP_PITCH, pitchUp);
        unlock();
    }
}
