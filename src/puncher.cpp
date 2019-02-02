#include "puncher.hpp"
#include "motor.hpp"

/** Power to set the puncher at when launching. */
static constexpr int launchPower = 127;

void puncher::set(int direction)
{
    using namespace motor;
    set(PUNCHER, launchPower * direction);
}

/** TaskCode for firing the puncher. */
static void punchTask(void*)
{
    puncher::punchSync();
}

TaskHandle puncher::punch()
{
    return taskCreate(punchTask, TASK_DEFAULT_STACK_SIZE, nullptr,
        TASK_PRIORITY_HIGHEST - 1);
}

void puncher::punchSync()
{
    puncher::set(1);
    delay(4000);
    puncher::set(0);
}
