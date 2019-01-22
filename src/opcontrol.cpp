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
    //lift::enablePid();
    lift::disablePid();

    unsigned long wakeTime = millis();
    while (true)
    {
        // tank controls
        drive::left(joystick::driveLeft());
        drive::right(joystick::driveRight());

        puncher::set(joystick::puncher());
        capIntake::rotate(joystick::wrist());
        ballIntake::set(joystick::ballIntake());

        if (lift::isPidEnabled())
        {
            // set the lift target position (liftIncrement*100)% above/below the
            //  current position
            static constexpr float liftIncrement = 0.1;
            int l = joystick::lift();
            // target pos should stay if the lift buttons aren't pressed,
            //  meaning it should hold its position
            if (l)
            {
                lift::setTargetPos(lift::getCurrentPos() +
                    (l > 0 ? liftIncrement : l < 0 ? -liftIncrement : 0));
            }
        }
        else lift::set(joystick::lift());

        // wait for the motors to update before receiving input again
        taskDelayUntil(&wakeTime, MOTOR_DELAY);
    }
}
