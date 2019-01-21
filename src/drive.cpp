#include "drive.hpp"
#include "motor.hpp"
#include "sensor.hpp"
#include <API.h>

using namespace motor;
using namespace sensor;

/** Right drive train encoder. */
static Encoder rightEncoder = nullptr;

void drive::initEncoders()
{
    rightEncoder = encoderInit(DT_RIGHT_TOP, DT_RIGHT_BOTTOM,
        /*reverse=*/ false);
}

void drive::left(int power)
{
    set(DRIVE_LF, power);
    set(DRIVE_LB, power);
}

void drive::right(int power)
{
    set(DRIVE_RF, -power);
    set(DRIVE_RB, -power);
}
