#include "main.hpp"
#include "ballIntake.hpp"
#include "drive.hpp"
#include "lift.hpp"
#include "puncher.hpp"

/** Minimum joystick analog value. Used by {@link deadzone}. */
static constexpr int DEADZONE = 20;

/**
 * Applies a deadzone to a joystick analog value.
 * @param analog Joystick value.
 * @return Zero if `analog` is below {@link DEADZONE} in absolute value,
 * otherwise what was given.
 */
static int deadzone(int analog);

void operatorControl()
{
    initMotors();

    unsigned long wakeTime = millis();
    while (true)
    {
        // tank controls
        drive::left(deadzone(joystickGetAnalog(1, 3)));
        drive::right(deadzone(joystickGetAnalog(1, 2)));

        // puncher: 7u
        if (joystickGetDigital(1, 7, JOY_UP))
        {
            puncher::launch();
        }

        // ball intake: 6u/d
        bool intakeForward = joystickGetDigital(1, 6, JOY_UP);
        bool intakeBackward = joystickGetDigital(1, 6, JOY_DOWN);
        if (intakeForward && !intakeBackward)
        {
            ballIntake::set(1);
        }
        else if (!intakeForward && intakeBackward)
        {
            ballIntake::set(-1);
        }
        else
        {
            ballIntake::set(0);
        }

        // puncher debug: 8u/d
        bool puncherForward = joystickGetDigital(1, 8, JOY_UP);
        bool puncherBackward = joystickGetDigital(1, 8, JOY_DOWN);
        if (puncherForward && !puncherBackward)
        {
            puncher::set(127);
        }
        else if (!puncherForward && puncherBackward)
        {
            puncher::set(-127);
        }
        else
        {
            puncher::set(0);
        }

        // lift: 5u/d
        bool liftUp = joystickGetDigital(1, 5, JOY_UP);
        bool liftDown = joystickGetDigital(1, 5, JOY_DOWN);
        if (liftUp && !liftDown)
        {
            lift::set(127);
        }
        else if (!liftUp && liftDown)
        {
            lift::set(-127);
        }
        else
        {
            lift::set(0);
        }

        // wait for the motors to update before receiving input again
        taskDelayUntil(&wakeTime, MOTOR_DELAY);
    }
}

int deadzone(int analog)
{
    if (abs(analog) <= DEADZONE)
    {
        return 0;
    }
    return analog;
}
