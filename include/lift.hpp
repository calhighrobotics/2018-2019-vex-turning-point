#ifndef LIFT_HPP
#define LIFT_HPP

/** Lift-related functions. */
namespace lift
{
/**
 * Initializes the lift encoders.
 */
void initEncoders();

/**
 * Sets the lift motors.
 * @param power Motor power.
 */
void set(int power);
} // end namespace lift

#endif // LIFT_HPP
