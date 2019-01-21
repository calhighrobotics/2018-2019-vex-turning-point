#include "puncher.hpp"
#include "motor.hpp"
#include <API.h>

/** Power to set the puncher at when launching. */
static constexpr int launchPower = -127;

void puncher::set(int direction)
{
    using namespace motor;
    set(PUNCHER, launchPower * direction);
}

