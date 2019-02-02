#include "ballIntake.hpp"
#include "motor.hpp"
#include <algorithm>

using namespace motor;

/** Motor power of the intake to set. */
static constexpr int POWER = -127;

void ballIntake::set(int direction)
{
    // clamp direction between -1 and 1 just to be safe
    direction = std::max(-1, std::min(1, direction));
    set(BALL_INTAKE, direction * POWER);
}

/** Parameters for the `ballIntake::load` functions. */
struct LoadTaskArgs
{
    unsigned long duration;
};

/**
 * TaskCode for loading the ball.
 * @param params A `malloc`'d pointer to a LoadTaskArgs object.
 */
static void loadTask(void* params)
{
    auto* args = static_cast<LoadTaskArgs*>(params);
    ballIntake::loadSync(args->duration);
    free(args);
}

TaskHandle ballIntake::load(unsigned long duration)
{
    auto* params = static_cast<LoadTaskArgs*>(malloc(
            sizeof(LoadTaskArgs)));
    params->duration = duration;

    return taskCreate(loadTask, TASK_DEFAULT_STACK_SIZE, params,
        TASK_PRIORITY_DEFAULT - 1);
}

void ballIntake::loadSync(unsigned long duration)
{
    set(1);
    delay(duration);
    set(0);
}
