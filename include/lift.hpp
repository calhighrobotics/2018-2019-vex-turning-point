#ifndef LIFT_HPP
#define LIFT_HPP

/** Lift-related functions. */
namespace lift
{
/** Initializes the lift encoders and PID task. */
void enablePid();

/** Checks whether the PID task is on. */
bool isPidEnabled();

/** Kills the lift PID task and deinitializes encoders. */
void disablePid();

/**
 * Gets the current lift position.
 * @returns A value from 0 to 1 specifying current extension of the lift.
 */
float getCurrentPos();

/** Checks whether the lift is down. */
bool isDown();

/**
 * Gets the target lift position.
 * @returns A value from 0 to 1 specifying extension of the lift.
 */
float getTargetPos();

/**
 * Sets target lift position.
 * @param position A value from 0 to 1 specifying extension of the lift.
 */
void setTargetPos(float position);

/**
 * Sets the lift motors.
 * @param direction Lift direction. -1 is down, 1 is up.
 */
void set(int direction);
} // end namespace lift

#endif // LIFT_HPP
