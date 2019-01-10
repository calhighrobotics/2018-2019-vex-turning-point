#ifndef LIFT_HPP
#define LIFT_HPP

/** Lift-related functions. */
namespace lift
{
/** Initializes the lift encoders and PID task. */
void init();

/** Kills the lift PID task and deinitializes encoders. */
void kill();

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

/** Adds `inc` onto the lift's kP constant. */
void kP(float inc);

/** Gets the lift's kP constant. */
float kP();
} // end namespace lift

#endif // LIFT_HPP
