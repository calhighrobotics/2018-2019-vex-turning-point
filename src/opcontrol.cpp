#include "main.hpp"
#include "ballIntake.hpp"
#include "capIntake.hpp"
#include "drive.hpp"
#include "joystick.hpp"
#include "lcd.hpp"
#include "lift.hpp"
#include "puncher.hpp"
#include "speaker.hpp"
#include <API.h>

void operatorControl()
{
    speaker::init();
    speaker::play();
    initMotors();
    lcd::init();

    unsigned long wakeTime = millis();
    while (true)
    {
        // tank controls
        drive::left(joystick::driveLeft());
        drive::right(joystick::driveRight());

        if (joystick::puncher()) puncher::launch();
        // TODO: move speed constants to component code
        puncher::set(127 * joystick::puncherDebug());
        lift::set(127 * joystick::lift());
        capIntake::pitch(joystick::capPitch());
        capIntake::rotate(joystick::wrist());
        ballIntake::set(joystick::ballIntake());

        // wait for the motors to update before receiving input again
        taskDelayUntil(&wakeTime, MOTOR_DELAY);
    }
}
