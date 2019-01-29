#ifndef PUNCHER_HPP
#define PUNCHER_HPP

#include <API.h>

/** Puncher-related functions. */
namespace puncher
{
/**
 * Sets the puncher motor.
 * @param direction Motor direction. 1 for launch, -1 for reverse.
 */
void set(int direction);

/**
 * Fires the puncher.
 * @returns A handle for the task responsible for launching.
 */
TaskHandle punch();

/** Fires the puncher using the current thread. */
void punchSync();
} // end namespace puncher

#endif // PUNCHER_HPP
