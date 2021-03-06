#ifndef MAIN_HPP
#define MAIN_HPP

/** The amount of time (ms) it takes to update the motors after setting them. */
constexpr unsigned long MOTOR_DELAY = 20;

/** Horizontal distance between wheels in 1/16in. */
constexpr int botRadius = 120;

/**
 * Starts the motor management task. Required for {@link motor::set} to work.
 * Called after `initialize()`, like during the start of `autonomous()` or
 * `operatorControl()`. Implemented in `motor.cpp`.
 */
void initMotors();

// functions that PROS requires to be implemented
extern "C"
{
void autonomous();
void initializeIO();
void initialize();
void operatorControl();
} // end extern "C"

#endif // MAIN_HPP
