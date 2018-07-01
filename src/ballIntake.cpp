#include "ballIntake.hpp"
#include "motor.hpp"
#include <API.h>
#include <algorithm>

using namespace motor;

/** Motor power of the intake to set. */
static constexpr int POWER = 127;

void ballIntake::set(int direction)
{
    // clamp direction between -1 and 1 just to be safe
    direction = std::max(-1, std::min(1, direction));

    motorSet(BALL_INTAKE, direction * POWER);
}
