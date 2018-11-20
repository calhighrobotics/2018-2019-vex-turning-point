#include "capIntake.hpp"
#include "motor.hpp"

using namespace motor;

/** Wrist rotation power. */
static constexpr int wristPower = 127;

void capIntake::rotate(int direction)
{
    lock();
    set(WRIST, wristPower * direction);
    unlock();
}
