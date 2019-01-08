#include "main.hpp"
#include "ballIntake.hpp"
#include "capIntake.hpp"
#include "drive.hpp"
#include "joystick.hpp"
#include "lcd.hpp"
#include "lift.hpp"
#include "pid.hpp"
#include "puncher.hpp"
#include "speaker.hpp"
#include <API.h>

void operatorControl()
{
    speaker::init();
    speaker::play();
    initMotors();
    lcd::init();
    //lift::enablePid();

    unsigned long wakeTime = millis();
    while (true)
    {
        // tank controls
        drive::left(joystick::driveLeft());
        drive::right(joystick::driveRight());

        if (joystick::puncher()) puncher::launch();
        // TODO: move speed constants to component code
        puncher::set(127 * joystick::puncherDebug());
        capIntake::pitch(joystick::capPitch());
        capIntake::rotate(joystick::wrist());
        ballIntake::set(joystick::ballIntake());

        if (lift::isPidEnabled())
        {
            static constexpr float liftIncrement = 0.5;
            int l = joystick::lift();
            lift::setTargetPos(lift::getCurrentPos() +
                (l > 0 ? liftIncrement : l < 0 ? -liftIncrement : 0));
        }
        else lift::set(127 * joystick::lift());

        // wait for the motors to update before receiving input again
        taskDelayUntil(&wakeTime, MOTOR_DELAY);
    }
}
