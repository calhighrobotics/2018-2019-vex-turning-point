#ifndef LIFT_HPP
#define LIFT_HPP

/** Lift-related functions. */
namespace lift
{
/** Initializes the lift encoders and PID task. */
void init();

/**
 * Gets the current lift position.
 * @returns A value from 0 to 1 specifying current extension of the lift.
 */
float getCurrentPos();

/**
 * Sets target lift position.
 * @param position A value from 0 to 1 specifying extension of the lift.
 */
void setTargetPos(float position);

/**
 * Sets the lift motors.
 * @param power Motor power.
 */
void set(int power);
} // end namespace lift

#endif // LIFT_HPP
