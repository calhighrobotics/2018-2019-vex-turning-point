#include "capIntake.hpp"
#include "motor.hpp"

using namespace motor;

/** Wrist rotation power. */
static constexpr int wristPower = 127;
/** Pitch position up. */
static constexpr int pitchUp = 127;
/** Pitch position down. */
static constexpr int pitchDown = -127;

void capIntake::rotate(int direction)
{
    set(WRIST, wristPower * direction);
}

void capIntake::pitch(int direction)
{
    set(CAP_PITCH, direction == 1 ? pitchUp : direction == -1 ? pitchDown : 0);
}
