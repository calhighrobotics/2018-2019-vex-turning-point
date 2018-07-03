#include "puncher.hpp"
#include "motor.hpp"
#include <API.h>

using namespace motor;

void puncher::set(int power)
{
    motorSet(PUNCHER, power);
}