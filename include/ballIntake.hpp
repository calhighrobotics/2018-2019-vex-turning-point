#ifndef BALLINTAKE_HPP
#define BALLINTAKE_HPP

#include <API.h>

/** Ball intake related functions. */
namespace ballIntake
{
/**
 * Powers the ball intake.
 * @param direction Intake direction. Positive is in, negative is out, zero is
 * off.
 */
void set(int direction);

/**
 * Loads the ball into the puncher.
 * @param duration Length of time to run the intake in ms. Leave blank if the
 * ball is currently just resting on the top.
 * @returns A handle for the task responsible for loading.
 */
TaskHandle load(unsigned long duration = 3000);

/**
 * Loads the ball into the puncher.
 * @param duration Length of time to run the intake in ms. Leave blank if the
 * ball is currently just resting on the top.
 */
void loadSync(unsigned long duration = 3000);
} // end namespace ballIntake

#endif // BALLINTAKE_HPP
