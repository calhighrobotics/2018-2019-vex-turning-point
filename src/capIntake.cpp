#include "capIntake.hpp"
#include "motor.hpp"
#include "puncher.hpp"

using namespace motor;

/** Wrist rotation power. */
static constexpr int wristPower = 70;

void capIntake::rotate(int direction)
{
    set(WRIST, wristPower * direction);
}

static void deployTask(void*)
{
    capIntake::deploySync();
}

TaskHandle capIntake::deploy()
{
    return taskCreate(deployTask, TASK_DEFAULT_STACK_SIZE, nullptr,
        TASK_PRIORITY_DEFAULT - 1);
}

void capIntake::deploySync()
{
    puncher::set(-1);
    delay(400);
    puncher::set(0);
}
