#ifndef CAPINTAKE_HPP
#define CAPINTAKE_HPP

#include <API.h>

/** Cap intake related functions. */
namespace capIntake
{
/**
 * Rotates the cap intake.
 * @param power Wrist motor direction. 1 is clockwise, -1 is counterclockwise.
 */
void rotate(int direction);

/**
 * Uses the puncher slip gear to unhinge a rubber band and deploy the cap
 * intake.
 * @returns A handle to the task responsible for deploying the cap intake.
 */
TaskHandle deploy();

/**
 * Uses the puncher slip gear to unhinge a rubber band and deploy the cap
 * intake.
 */
void deploySync();
} // end namespace capIntake

#endif // CAPINTAKE_HPP
