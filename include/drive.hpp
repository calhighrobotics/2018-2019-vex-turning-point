#ifndef DRIVE_HPP
#define DRIVE_HPP

#include <API.h>

/** Drivetrain-related functions. */
namespace drive
{
/** Initializes the encoders. Should be called in `initialize()`. */
void initEncoders();

/** Disables the encoders. */
void deinitEncoders();

/**
 * Powers the left side of the drive train.
 * @param power Motor power.
 */
void left(int power);

/**
 * Powers the right side of the drive train.
 * @param power Motor power.
 */
void right(int power);

/** Stops the drive train. */
void stop();

/**
 * Drives the robot forward/backward.
 * @param distance Distance to drive in 1/16in.
 * @param power Constant power to be sent to the motors while driving. Pass in 0
 * or leave blank to let a PID controller decide based on the distance needed,
 * in which case the drive train will slow (instead of coast) to a stop once
 * finished.
 * @param tolerance Encoder tolerance in degrees.
 * @returns A handle for the task responsible for driving.
 */
TaskHandle straight(int distance, int power = 0, int tolerance = 15);

/**
 * Drives the robot forward/backward.
 * @param distance Distance to drive in 1/16in.
 * @param power Constant power to be sent to the motors while driving. Pass in 0
 * or leave blank to let a PID controller decide based on the distance needed,
 * in which case the drive train will slow (instead of coast) to a stop once
 * finished.
 * @param tolerance Encoder tolerance in degrees.
 */
void straightSync(int distance, int power = 0, int tolerance = 15);

/**
 * @param angle Angle to turn in degrees. + is CW, - is CCW.
 * @param radius Turning radius relative to the center of the robot, in 1/16in.
 * @param outer Constant power to be sent to the outside motor while driving.
 * Pass in 0 or leave blank to let a PID controller decide based on the distance
 * needed, in which case the drive train will slow (instead of coast) to a stop
 * once finished.
 * @param tolerance Encoder tolerance in degrees.
 * @returns A handle for the task responsible for driving.
 */
TaskHandle turn(int angle, int radius, int outer = 0, int tolerance = 15);

/**
 * @param angle Angle to turn in degrees. + is CW, - is CCW.
 * @param radius Turning radius relative to the center of the robot, in 1/16in.
 * @param outer Constant power to be sent to the outside motor while driving.
 * Pass in 0 or leave blank to let a PID controller decide based on the distance
 * needed, in which case the drive train will slow (instead of coast) to a stop
 * once finished.
 * @param tolerance Encoder tolerance in degrees.
 */
void turnSync(int angle, int radius, int outer = 0, int tolerance = 15);
} // end namespace drive

#endif // DRIVE_HPP
