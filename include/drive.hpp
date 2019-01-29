#ifndef DRIVE_HPP
#define DRIVE_HPP

#include <API.h>

/** Drivetrain-related functions. */
namespace drive
{
/** Initializes the encoders. Should be called in `initialize()`. */
void initEncoders();

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

/**
 * Drives the robot forward/backward.
 * @param distance Distance to drive in 1/16in.
 * @param decelerate Whether to use a PID controller to decelerate when close to
 * the target. Pass in `false` if another drive function will be called
 * immediately after this one finishes. If `false` is passed in, the motors will
 * remain at 127 when the task finishes.
 * @param tolerance Distance tolerance in 1/16in.
 * @returns A handle for the task responsible for driving.
 */
TaskHandle straight(int distance, bool decelerate = true, int tolerance = 16);

/**
 * Drives the robot forward/backward.
 * @param distance Distance to drive in 1/16in.
 * @param decelerate Whether to use a PID controller to decelerate when close to
 * the target. Pass in `false` if another drive function will be called
 * immediately after this one finishes. If `false` is passed in, the motors will
 * remain at 127 when the task finishes.
 * @param tolerance Distance tolerance in 1/16in.
 */
void straightSync(int distance, bool decelerate = true, int tolerance = 16);

/**
 * @param angle Angle to turn in degrees. + is CW, - is CCW.
 * @param radius Turning radius relative to the center of the robot, in 1/16in.
 * @param outer Power (-127 to 127) of the outside drive motor. Pass in 0 or
 * leave blank to let a PID controller decide based on the distance needed, in
 * which case the drive train will slow to a stop once finished.
 * @param tolerance Distance tolerance in 1/16in.
 * @returns A handle for the task responsible for driving.
 */
TaskHandle turn(int angle, int radius, int outer = 0, int tolerance = 16);

/**
 * @param angle Angle to turn in degrees. + is CW, - is CCW.
 * @param radius Turning radius relative to the center of the robot, in 1/16in.
 * @param outer Power (-127 to 127) of the outside drive motor. Pass in 0 or
 * leave blank to let a PID controller decide based on the distance needed, in
 * which case the drive train will slow to a stop once finished.
 * @param tolerance Distance tolerance in 1/16in.
 */
void turnSync(int angle, int radius, int outer = 0, int tolerance = 16);
} // end namespace drive

#endif // DRIVE_HPP
