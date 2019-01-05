#include "auto.hpp"
#include "drive.hpp"
#include "main.hpp"
#include "lcd.hpp"
#include "lift.hpp"
#include "puncher.hpp"
#include <API.h>

using namespace auton;

const char* auton::autonNames[NUM_AUTONS][2]
{
    {"Nothing", ""}, {"Drive and Launch", ""}
};

/** Current auton program. */
static Auton autonState = DRIVE_LAUNCH;

Auton auton::getAuton()
{
    return autonState;
}

void auton::setAuton(Auton value)
{
    autonState = value;
}

/**
 * Drives the robot forward.
 * @param power Motor power.
 * @param ms Time delay in ms.
 */
static void driveForward(int power, unsigned long ms)
{
    drive::left(power);
    drive::right(power);
    delay(ms);
    drive::left(0);
    drive::right(0);
}

/** Launches the ball. */
static void launchBall()
{
    puncher::set(127);
    delay(3600);
    puncher::set(0);
}

/** Drive forward and launch the ball. */
static void driveLaunch()
{
    // drive up to flag
    driveForward(127, 300);

    // launch ball to flag
    launchBall();
}

// declared in main.hpp
void autonomous()
{
    initMotors();
    lcd::init();
    lift::init();

    switch (autonState)
    {
        case NOTHING:
            // nothing!
            break;
        case DRIVE_LAUNCH:
            driveLaunch();
            break;
        default:;
    }
}
