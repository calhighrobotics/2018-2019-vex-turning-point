#include "main.hpp"
#include "ballIntake.hpp"
#include "capIntake.hpp"
#include "drive.hpp"
#include "joystick.hpp"
#include "lcd.hpp"
#include "lift.hpp"
#include "pid.hpp"
#include "puncher.hpp"
#include <API.h>

void operatorControl()
{
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
        capIntake::rotate(joystick::wrist());
        ballIntake::set(joystick::ballIntake());

        //lift::set(127 * joystick::lift());
        // after 1s of holding down the button, the lift should aim to be fully
        //  raised
        static constexpr float liftIncrement = MOTOR_DELAY / 1000;
        lift::setTargetPos(lift::getCurrentPos() +
            liftIncrement * joystick::lift());

        // wait for the motors to update before receiving input again
        taskDelayUntil(&wakeTime, MOTOR_DELAY);
    }
}
