#include "drive.hpp"
#include "lift.hpp"
#include "puncher.hpp"

// not having these will cause an undefined reference error
void* __dso_handle;
extern "C" void _fini(){}

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
