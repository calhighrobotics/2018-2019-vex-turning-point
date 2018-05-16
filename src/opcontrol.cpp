#include "main.hpp"
#include "motor.hpp"

constexpr int DEADZONE = 20;

// applies a deadzone to a joystick analog value
static int deadzone(int analog);

void operatorControl()
{
	while (true)
	{
		// standard tank controls
		driveLeft(deadzone(joystickGetAnalog(1, 3)));
		driveRight(deadzone(joystickGetAnalog(1, 2)));
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
