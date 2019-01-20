#include "joystick.hpp"
#include <API.h>

/**
 * Translates two booleans (forward/backward) into a -1/0/1 quantity.
 * @param forward To go forward.
 * @param backward To go backward.
 * @return -1 for backward, 1 for forward, or 0 for stop.
 */
static int buttonControl(bool forward, bool backward)
{
    return forward - backward;
}

/**
 * Applies a deadzone to a joystick analog value.
 * @param analog Joystick value.
 * @return Zero if `analog` is below {@link DEADZONE} in absolute value,
 * otherwise what was given.
 */
static int deadzone(int analog)
{
    // deadzone value
    static constexpr int value = 20;
    return abs(analog) > value ? analog : 0;
}

int joystick::driveLeft()
{
    return deadzone(joystickGetAnalog(1, 3));
}

int joystick::driveRight()
{
    return deadzone(joystickGetAnalog(1, 2));
}

bool joystick::puncher()
{
    //return joystickGetDigital(1, 7, JOY_UP);
    return false;
}

int joystick::puncherDebug()
{
    bool puncherForward = joystickGetDigital(1, 8, JOY_UP);
    bool puncherBackward = joystickGetDigital(1, 8, JOY_DOWN);
    return buttonControl(puncherForward, puncherBackward);
}

int joystick::capPitch()
{
    bool up = joystickGetDigital(1, 7, JOY_UP);
    bool down = joystickGetDigital(1, 7, JOY_DOWN);
    return buttonControl(up, down);
}

int joystick::lift()
{
    bool liftUp = joystickGetDigital(1, 5, JOY_UP);
    bool liftDown = joystickGetDigital(1, 5, JOY_DOWN);
    return buttonControl(liftUp, liftDown);
}

int joystick::wrist()
{
    bool wristClockwise = joystickGetDigital(1, 7, JOY_RIGHT);
    bool wristCounterClockwise = joystickGetDigital(1, 7, JOY_LEFT);
    return buttonControl(wristClockwise, wristCounterClockwise);
}

int joystick::ballIntake()
{
    bool intakeForward = joystickGetDigital(1, 6, JOY_UP);
    bool intakeBackward = joystickGetDigital(1, 6, JOY_DOWN);
    return buttonControl(intakeForward, intakeBackward);
}
