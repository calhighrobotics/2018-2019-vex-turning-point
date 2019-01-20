#ifndef JOYSTICK_HPP
#define JOYSTICK_HPP

/** Joystick-related functions. */
namespace joystick
{
/** Gets the joystick value for the left drivetrain. */
int driveLeft();
/** Gets the joystick value for the right drivetrain. */
int driveRight();
/** Gets the button value for the puncher. */
bool puncher();
/** Gets the button value (-1, 0, 1) for the puncher motor direction. */
int puncherDebug();
/** Gets the button value (-1, 0, 1) for the lift direction. */
int lift();
/** Gets the button value (-1, 0, 1) for the cap intake rotation direction. */
int wrist();
/** Gets the button value (-1, 0, 1) for the ball intake. */
int ballIntake();
} // end namespace joystick

#endif // JOYSTICK_HPP
