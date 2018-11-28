#include "pid.hpp"
#include "main.hpp"
#include <cmath>

void Velocity::update(int value, int deltaTime)
{
    addVel((float) (value - lastValue) / deltaTime);
    lastValue = value;
}

int Velocity::getPos() const
{
    return lastValue;
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

PID::PID(float kP, float kI, float kD, MotorGetter get, MotorSetter set)
    : kP{ kP }, kI{ kI }, kD{ kD }, get{ get }, set{ set },
    targetMutex{ nullptr }, targetPos{ 0 } {}

void PID::init()
{
    targetMutex = mutexCreate();
}

void PID::update(int deltaTime)
{
    velocity.update(get(), deltaTime);

    // determine which way we should go and by how much
    const int currentPos = velocity.getPos();
    mutexTake(targetMutex, 0);
    const int posError = targetPos - currentPos;
    mutexGive(targetMutex);

    // calculate power (clamped to the interval [-127, 127]) given encoder delta
    const int power = round(127 * tanh(kP * posError));
    set(power);
}

int PID::getCurrentPos() const
{
    return get();
}

void PID::setTargetPos(int pos)
{
    mutexTake(targetMutex, 0);
    targetPos = pos;
    mutexGive(targetMutex);
}
