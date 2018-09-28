#include "main.hpp"
#include "ballIntake.hpp"
#include "capIntake.hpp"
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

/**
 * Translates two booleans (forward/backward) into a -1/0/1 quantity.
 * @param forward To go forward.
 * @param backward To go backward.
 * @return -1 for backward, 1 for forward, or 0 for stop.
 */
static int buttonControl(bool forward, bool backward);

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

        // wrist: 7r/l
        bool wristClockwise = joystickGetDigital(1, 6, JOY_RIGHT);
        bool wristCounterClockwise = joystickGetDigital(1, 6, JOY_LEFT);
        capIntake::rotate(buttonControl(wristClockwise, wristCounterClockwise));

        // ball intake: 6u/d
        bool intakeForward = joystickGetDigital(1, 6, JOY_UP);
        bool intakeBackward = joystickGetDigital(1, 6, JOY_DOWN);
        ballIntake::set(127 * buttonControl(intakeForward, intakeBackward));

        // puncher debug: 8u/d
        bool puncherForward = joystickGetDigital(1, 8, JOY_UP);
        bool puncherBackward = joystickGetDigital(1, 8, JOY_DOWN);
        puncher::set(127 * buttonControl(puncherForward, puncherBackward));

        // lift: 5u/d
        bool liftUp = joystickGetDigital(1, 5, JOY_UP);
        bool liftDown = joystickGetDigital(1, 5, JOY_DOWN);
        lift::set(127 * buttonControl(liftUp, liftDown));

        // claw: 8r/l
        bool clawOpen = joystickGetDigital(1, 6, JOY_RIGHT);
        bool clawClose = joystickGetDigital(1, 6, JOY_LEFT);
        capIntake::grab(buttonControl(clawOpen, clawClose));

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

int buttonControl(bool forward, bool backward)
{
    return forward - backward;
}
