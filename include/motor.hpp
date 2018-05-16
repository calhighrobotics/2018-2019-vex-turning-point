#ifndef MOTOR_HPP
#define MOTOR_HPP

// the amount of time it takes to update the motors after calling motorSet
constexpr unsigned long MOTOR_DELAY = 20; // ms

// drive train
void driveLeft(int power);
void driveRight(int power);

#endif // MOTOR_HPP
