#include "capIntake.hpp"
#include "motor.hpp"

using namespace motor;

/** Claw grab power. */
static constexpr int grabPower = 63;
/** Wrist rotation power. */
static constexpr int wristPower = 31;

void capIntake::grab(int direction)
{
    lock();
    set(CLAW, grabPower * direction);
    unlock();
}

void capIntake::rotate(int direction)
{
    lock();
    set(WRIST, wristPower * direction);
    unlock();
}
