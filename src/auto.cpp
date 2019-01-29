#include "auto.hpp"
#include "capIntake.hpp"
#include "drive.hpp"
#include "main.hpp"
#include "lcd.hpp"
#include "lift.hpp"
#include "puncher.hpp"

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

/** Pauses the current task until the given one has completed. */
static void await(TaskHandle task)
{
    while (taskGetState(task) != TASK_DEAD) delay(MOTOR_DELAY);
}

/** Drive forward and launch the ball. */
static void driveLaunch()
{
    // unhinge cap intake from the puncher
    const TaskHandle deploy = capIntake::deploy();

    // drive up to toggle bottom flag
    drive::straightSync(750, /*decelerate*/ false);

    // back up within range of higher flags
    drive::straight(-150);

    // launch ball to flag after cap intake is deployed
    await(deploy);
    puncher::punchSync();
}

// declared in main.hpp
void autonomous()
{
    initMotors();
    lcd::init();
    drive::initEncoders();
    lift::enablePid();

    switch (autonState)
    {
        case NOTHING:
            // nothing except setup the cap intake
            capIntake::deploySync();
            break;
        case DRIVE_LAUNCH:
            driveLaunch();
            break;
        default:;
    }
}
