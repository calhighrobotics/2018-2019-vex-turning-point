#include "auto.hpp"
#include "ballIntake.hpp"
#include "capIntake.hpp"
#include "drive.hpp"
#include "main.hpp"
#include "lcd.hpp"
#include "lift.hpp"
#include "puncher.hpp"

using namespace auton;

/** Alliance color type. */
enum Color
{
    /** Red, left side. */
    RED, LEFT = RED,
    /** Blue, right side. */
    BLUE, RIGHT = BLUE
};

const char* auton::autonNames[NUM_AUTONS][2]
{
    {"Nothing", ""}, {"Test Program", ""}, {"Flags Close", ""},
    {"Flags Park Close", "Red"}, {"Flags Park Close", "Blue"}
};

/** Current auton program. */
static Auton autonState = FLAGS_CLOSE;

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

static void test()
{
    // test auton turn
    drive::turnSync(90, botRadius, 127);
}

/** Target flags from the front tile. */
static void flagsClose()
{
    // start in the top corner of the front tile so ball has the best chance of
    //  hitting

    // unhinge cap intake from the puncher
    const TaskHandle deploy = capIntake::deploy();

    // drive up to toggle bottom flag
    drive::straightSync(400, 127);
    // back up within range of higher flags
    drive::straight(-100);

    // put the ball in the puncher
    ballIntake::load();

    // launch the ball to the flag after the cap intake is deployed
    await(deploy);
    puncher::punchSync();
}

/** Target flags from front tile then drive onto the platform. */
static void flagsParkClose(Color color)
{
    flagsClose();
    // from previous tests, the robot will have its back wheels touching the
    //  starting tile by now

    // turn around so we're not hitting the platform/walls with the cap intake
    drive::turnSync(180, 0, 127);
    // go back to the starting tile
    drive::straightSync(150, 127);
    // arc around to be inline the platform
    if (color == LEFT) drive::turnSync(-90, 120, 127);
    else drive::turnSync(90, 120, 127);
    // drive straight into it
    drive::straightSync(350, 127);
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
        case TEST:
            test();
            break;
        case FLAGS_CLOSE:
            flagsClose();
            break;
        case FLAGS_PARK_CLOSE_RED:
            flagsParkClose(RED);
            break;
        case FLAGS_PARK_CLOSE_BLUE:
            flagsParkClose(BLUE);
            break;
        default:;
    }

    drive::deinitEncoders();
}
