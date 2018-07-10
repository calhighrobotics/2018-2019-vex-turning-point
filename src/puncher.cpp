#include "puncher.hpp"
#include "motor.hpp"

using namespace motor;

void puncher::set(int power)
{
    lock();
    set(PUNCHER_1, power);
    set(PUNCHER_2, -power);
    unlock();
}