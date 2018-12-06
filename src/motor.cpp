#include "motor.hpp"
#include "main.hpp"
#include "mutexVar.hpp"
#include <API.h>
#include <algorithm>

using namespace motor;

/** Maximum rate of change of a motor's power. */
static constexpr int SLEW_RATE = 20;
/** Keeps track of queued `motor::set()`'s. */
static MutexVar<int> requested[MAX_MOTOR_PORTS] = {};

/** Slew rate management function. */
static void slewRate()
{
    puts("slew rate");
    // go through each requested motor power
    for (int i = 0; i < MAX_MOTOR_PORTS; ++i)
    {
        printf("slew rate port %d\n", i + 1);
        const Port port = static_cast<Port>(i + 1);
        const int current = motorGet(port);

        // calculate change in motor power, capped at SLEW_RATE
        int change = requested[i] - current;
        change = std::max(-SLEW_RATE, std::min(SLEW_RATE, change));

        // update the motor
        motorSet(port, current + change);
        printf("slew rate port %d done\n", i + 1);
    }
    puts("slew rate done");
}

// declared in main.hpp
void initMotors()
{
    for (int i = 0; i < MAX_MOTOR_PORTS; ++i)
    {
        requested[i].init();
    }
    taskRunLoop(slewRate, MOTOR_DELAY);
}

void motor::set(Port port, int power)
{
    // ports are 1-based, but arrays are 0-based
    requested[port - 1] = power;
}
