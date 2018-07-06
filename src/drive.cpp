#include "drive.hpp"
#include "motor.hpp"

using namespace motor;

void drive::left(int power)
{
    lock();
    set(DRIVE_LF, power);
    set(DRIVE_LB, power);
    unlock();
}

void drive::right(int power)
{
    lock();
    set(DRIVE_RF, -power);
    set(DRIVE_RB, -power);
    unlock();
}
