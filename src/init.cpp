#include "drive.hpp"
#include "lift.hpp"
#include "puncher.hpp"

void initializeIO()
{
    puncher::initLimit();
}

void initialize()
{
    drive::initEncoders();
    drive::initGyro();
    lift::initEncoders();
}
