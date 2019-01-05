#include "puncher.hpp"
#include "main.hpp"
#include "motor.hpp"
#include "sensor.hpp"
#include <API.h>

using namespace motor;
using namespace sensor;

/** Power to set the puncher at when launching. */
static constexpr int launchPower = 127;
/** Current task handle while launching. */
static TaskHandle handle = nullptr;

/** Task for going through the process of launching. */
static void launchTask(void*)
{
    // start puncher
    puncher::set(launchPower);
    // the limit switch may already be pressed so wait for it to pass that
    while (digitalRead(PUNCHER_LIMIT) == HIGH) taskDelay(MOTOR_DELAY);
    // wait until the slip gear completes a revolution
    while (digitalRead(PUNCHER_LIMIT) == LOW) taskDelay(MOTOR_DELAY);
    // stop puncher
    puncher::set(0);

    // this task is now completed
    handle = nullptr;
}

void puncher::initLimit()
{
    pinMode(PUNCHER_LIMIT, INPUT);
}

void puncher::set(int power)
{
    set(PUNCHER, -power);
}

void puncher::launch()
{
    // create the task if it doesn't exist
    if (!handle)
    {
        handle = taskCreate(launchTask, TASK_DEFAULT_STACK_SIZE, nullptr,
            TASK_PRIORITY_DEFAULT);
        return;
    }
}

