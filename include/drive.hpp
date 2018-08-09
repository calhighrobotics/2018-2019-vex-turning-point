#ifndef DRIVE_HPP
#define DRIVE_HPP

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
} // end namespace drive

#endif // DRIVE_HPP
