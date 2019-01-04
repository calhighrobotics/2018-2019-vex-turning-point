#ifndef CAPINTAKE_HPP
#define CAPINTAKE_HPP

/** Cap intake related functions. */
namespace capIntake
{
/**
 * Powers the cap intake claw.
 * @param power Claw direction. 1 is close, -1 is open.
 */
void grab(int direction);

/**
 * Rotates the cap intake.
 * @param power Wrist motor direction. 1 is clockwise, -1 is counterclockwise.
 */
void rotate(int direction);

/**
 * Pitches the cap intake.
 * @param direction Intake direction. -1 is down, 1 is up.
 */
void pitch(int direction);
} // end namespace capIntake

#endif // CAPINTAKE_HPP
