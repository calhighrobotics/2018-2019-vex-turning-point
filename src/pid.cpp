#include "pid.hpp"
#include "main.hpp"
#include <API.h>
#include <cmath>

void Velocity::update(int value, int deltaTime)
{
    addVel((float) (value - lastValue) / deltaTime);
    lastValue = value;
}

float Velocity::getVel() const
{
    // calculate rolling average
    float vel = 0;
    for (int i = 0; i < maxVelocities; ++i)
    {
        vel += velocities[i];
    }
    return vel / maxVelocities;
}

void Velocity::addVel(int vel)
{
    // replace oldest value with the newest one
    velocities[oldest++] = vel;
    if (oldest >= maxVelocities) oldest = 0;
}

PID::PID(float kP, float kI, float kD)
    : kP{ kP }, kI{ kI }, kD{ kD }, targetMutex{ nullptr }, targetPos{ 0 } {}

void PID::init()
{
    targetMutex = mutexCreate();
}

int PID::update(int value, int deltaTime)
{
    velocity.update(value, deltaTime);

    // determine which way we should go and by how much
    mutexTake(targetMutex, 0);
    const int target = targetPos;
    mutexGive(targetMutex);
    const float p = kP * (target - value);

    // power clamped to the interval [-127, 127]
    int power = round(127 * tanh(p));
    printf("value: %d, p: %.2f, power: %d\n", value, p, power);
    return power;
}

void PID::setTargetPos(int pos)
{
    if (!targetMutex) return;
    mutexTake(targetMutex, 0);
    targetPos = pos;
    mutexGive(targetMutex);
}
