#include "main.hpp"
#include "drive.hpp"
#include "ballIntake.hpp"

/** Minimum joystick analog value. Used by {@link deadzone}. */
static constexpr int DEADZONE = 20;

/**
 * Applies a deadzone to a joystick analog value.
 * @param analog Joystick value.
 * @returns Zero if `analog` is below {@link DEADZONE} in absolute value,
 * otherwise what was given.
 */
static int deadzone(int analog);

void operatorControl()
{
	while (true)
	{
		// tank controls
		drive::left(deadzone(joystickGetAnalog(1, 3)));
		drive::right(deadzone(joystickGetAnalog(1, 2)));

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

		// wait for the motors to update before receiving input again
		delay(MOTOR_DELAY);
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
