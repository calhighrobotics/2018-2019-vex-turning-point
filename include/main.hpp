#ifndef MAIN_HPP
#define MAIN_HPP

#include <API.h>

/** The amount of time (ms) it takes to update the motors after setting them. */
constexpr unsigned long MOTOR_DELAY = 20;

// functions that PROS requires to be implemented
extern "C"
{
void autonomous();
void initializeIO();
void initialize();
void operatorControl();
} // end extern "C"

#endif // MAIN_HPP
