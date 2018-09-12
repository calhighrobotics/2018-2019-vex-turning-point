#include "lift.hpp"
#include "motor.hpp"

using namespace motor;

void lift::set(int power)
{
    lock();
    set(LIFT_LEFT, -power);
    set(LIFT_RIGHT, power);
    unlock();
}
