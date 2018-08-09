#include "drive.hpp"
#include "motor.hpp"
#include "sensor.hpp"
#include <API.h>

using namespace motor;
using namespace sensor;

/** Right drive train encoder. */
static Encoder rightEncoder;
static Gyro gyro;

void drive::initEncoders()
{
    rightEncoder = encoderInit(DT_RIGHT_TOP, DT_RIGHT_BOTTOM,
        /*reverse=*/ false);
}

void drive::initGyro()
{
    gyro = gyroInit(GYRO, /*multiplier=*/ 0);
}

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
