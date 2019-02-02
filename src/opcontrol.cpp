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
    lift::enablePid();
    //lift::disablePid();

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
            // position offset when going up to offset proportion term
            static constexpr float liftUpOffset = 0.1;
            // position offset when going down to offset gravity+momentum
            static constexpr float liftDownOffset = 0.05;

            static int liftButton = 0;
            static int lastLiftButton;
            lastLiftButton = liftButton;
            liftButton = joystick::lift();
            if (liftButton > 0) lift::setTargetPos(1);
            else if (liftButton < 0) lift::setTargetPos(0);
            else if (lastLiftButton)
            {
                // just released lift button so hold current pos
                if (lift::isDown()) lift::setTargetPos(0);
                else if (lift::getCurrentPos() < lift::getTargetPos())
                {
                    // set target higher than normal so the proportional term
                    //  catches up faster
                    lift::setTargetPos(lift::getCurrentPos() + liftUpOffset);
                }
                // set target lower than normal so the pid decelerates to a stop
                //  better
                else lift::setTargetPos(lift::getCurrentPos() - liftDownOffset);
            }
        }
        else lift::set(joystick::lift());

        // wait for the motors to update before receiving input again
        taskDelayUntil(&wakeTime, MOTOR_DELAY);
    }
}
