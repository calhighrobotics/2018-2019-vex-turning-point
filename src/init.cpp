#include "drive.hpp"
#include "lift.hpp"
#include "puncher.hpp"

// not having this causes an undefined reference error for now
void* __dso_handle;

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
