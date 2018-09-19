#include "drive.hpp"
#include "main.hpp"
#include "puncher.hpp"

/**
 * Drives the robot forward.
 * @param power Motor power.
 * @param ms Time delay in ms.
 */
static void driveForward(int power, unsigned long ms);

/**
 * Ball go kabooooom
 */
static void launchBall();

void autonomous()
{
    // drive up to flag
    driveForward(127, 300);

    // launch ball to flag
    launchBall();
}

void driveForward(int power, unsigned long ms)
{
    drive::left(power);
    drive::right(power);
    delay(ms);
    drive::left(0);
    drive::right(0);
}

void launchBall()
{
    puncher::set(-127);
    delay(1000);
    puncher::set(0);
}
