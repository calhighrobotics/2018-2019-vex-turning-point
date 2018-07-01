#include "drive.hpp"
#include "motor.hpp"
#include <API.h>

using namespace motor;

void drive::left(int power)
{
    motorSet(DRIVE_LF, -power);
    motorSet(DRIVE_LB, -power);
}

void drive::right(int power)
{
    motorSet(DRIVE_LF, power);
    motorSet(DRIVE_LB, power);
}
