#ifndef BALLINTAKE_HPP
#define BALLINTAKE_HPP

/** Ball intake related functions. */
namespace ballIntake
{
/**
 * Powers the ball intake.
 * @param direction Intake direction. Positive is in, negative is out, zero is
 * off.
 */
void set(int direction);
} // end namespace ballIntake

#endif // BALLINTAKE_HPP
