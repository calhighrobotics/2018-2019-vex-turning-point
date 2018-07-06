#include "motor.hpp"
#include "main.hpp"
#include <API.h>
#include <algorithm>

using namespace motor;

/** Maximum rate of change of a motor's power. */
static constexpr int SLEW_RATE = 20;
/** Array to keep track of queued `motor::set`'s. */
static int requested[MAX_MOTOR_PORTS];
/** Internal mutex to facilitate `motor::set` calls. */
static Mutex mutex = nullptr;
/** Task handle for the motor manager. */
static TaskHandle loopTask = nullptr;

/**
 * Slew rate management function. The ignored `void*` parameter is required by
 * PROS.
 */
static void loop(void*);

void initMotors()
{
    mutex = mutexCreate();
    loopTask = taskCreate(loop, TASK_DEFAULT_STACK_SIZE, nullptr,
        TASK_PRIORITY_DEFAULT);
    if (!mutex || !loopTask)
    {
        // an error occured
        print("D:\n");
    }
}

void motor::lock()
{
    mutexTake(mutex, 0);
}

void motor::unlock()
{
    mutexGive(mutex);
}

void motor::set(Port port, int power)
{
    requested[port - 1] = power;
}

void loop(void*)
{
    unsigned long wakeTime = millis();
    while (true)
    {
        lock();

        // go through each requested motor power
        for (int i = 0; i < MAX_MOTOR_PORTS; ++i)
        {
            Port port = static_cast<Port>(i + 1);

            // calculate change in motor power, capped at SLEW_RATE
            int current = motorGet(port);
            int change = requested[i] - current;
            change = std::max(-SLEW_RATE, std::min(SLEW_RATE, change));

            // update the motor
            motorSet(port, current + change);
        }

        unlock();
        taskDelayUntil(&wakeTime, MOTOR_DELAY);
    }
}
