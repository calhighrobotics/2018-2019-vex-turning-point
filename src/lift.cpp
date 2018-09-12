#include "lift.hpp"
#include "main.hpp"
#include "motor.hpp"
#include "sensor.hpp"

using namespace motor;
using namespace sensor;

/** Left lift encoder. */
static Encoder leftEncoder = nullptr;
/** Right lift encoder. */
static Encoder rightEncoder = nullptr;

void lift::initEncoders()
{
    leftEncoder = encoderInit(LIFT_LEFT_TOP, LIFT_LEFT_BOTTOM,
        /*reverse=*/ true);
    rightEncoder = encoderInit(LIFT_RIGHT_TOP, LIFT_RIGHT_BOTTOM,
        /*reverse=*/ false);
}

void lift::set(int power)
{
    lock();
    set(LIFT_LEFT, -power);
    set(LIFT_RIGHT, power);
    unlock();
}
