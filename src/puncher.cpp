#include "puncher.hpp"
#include "motor.hpp"

using namespace motor;

void puncher::set(int power)
{
    lock();
    set(PUNCHER, power);
    unlock();
}