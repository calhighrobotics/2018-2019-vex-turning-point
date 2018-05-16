#include "motor.hpp"
#include <API.h>

// list of all motor ports
enum Port: unsigned char
{
    DRIVE_LF = 2,
    DRIVE_LB = 3,
    DRIVE_RF = 8,
    DRIVE_RB = 9
};

void driveLeft(int power)
{
    motorSet(DRIVE_LF, -power);
    motorSet(DRIVE_LB, -power);
}

void driveRight(int power)
{
    motorSet(DRIVE_LF, power);
    motorSet(DRIVE_LB, power);
}
