#ifndef PUNCHER_HPP
#define PUNCHER_HPP

/** Puncher-related functions. */
namespace puncher
{
/** Initializes the limit switch. Should be called in `initializeIO()`. */
void initLimit();

/**
 * Sets the puncher motor.
 * @param power Motor power.
 */
void set(int power);

/**
 * Launches a ball from a puncher. This function starts a new task so repeated
 * calls won't do anything.
 */
void launch();
} // end namespace puncher

#endif // PUNCHER_HPP
