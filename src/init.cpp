#include "drive.hpp"
#include "lcd.hpp"
#include "lift.hpp"
#include "main.hpp"
#include "motor.hpp"
#include <API.h>

void initializeIO()
{
}

void initialize()
{
    setTeamName("1516B");
    initMotors();
    lcd::init();
    drive::initEncoders();
    lift::enablePid();
}
