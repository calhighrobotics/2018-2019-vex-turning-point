#include "drive.hpp"
#include "puncher.hpp"

void initializeIO()
{
    puncher::initLimit();
}

void initialize()
{
    drive::initEncoders();
}
