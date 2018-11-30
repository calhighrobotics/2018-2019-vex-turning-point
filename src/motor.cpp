#include "motor.hpp"
#include "main.hpp"
#include <API.h>
#include <algorithm>

using namespace motor;

/** Maximum rate of change of a motor's power. */
static constexpr int SLEW_RATE = 20;
/** Keeps track of queued `motor::set()`'s. */
static int requested[MAX_MOTOR_PORTS] = {};
/** Keeps track of motor mutexes. */
static Mutex requestedMutexes[MAX_MOTOR_PORTS] = {};

/** Slew rate management function. */
static void slewRate()
{
    // go through each requested motor power
    for (int i = 0; i < MAX_MOTOR_PORTS; ++i)
    {
        const Port port = static_cast<Port>(i + 1);
        const int current = motorGet(port);

        // calculate change in motor power, capped at SLEW_RATE
        mutexTake(requestedMutexes[i], 0);
        const int req = requested[i];
        mutexGive(requestedMutexes[i]);
        int change = req - current;
        change = std::max(-SLEW_RATE, std::min(SLEW_RATE, change));

        // update the motor
        motorSet(port, current + change);
    }
}

// declared in main.hpp
void initMotors()
{
    for (int i = 0; i < MAX_MOTOR_PORTS; ++i)
    {
        requested[i] = 0;
        requestedMutexes[i] = mutexCreate();
    }
    taskRunLoop(slewRate, MOTOR_DELAY);
}

void motor::set(Port port, int power)
{
    // ports are 1-based, but arrays are 0-based
    int i = port - 1;
    if (!requestedMutexes[i]) return;
    mutexTake(requestedMutexes[i], 0);
    requested[i] = power;
    mutexGive(requestedMutexes[i]);
}
