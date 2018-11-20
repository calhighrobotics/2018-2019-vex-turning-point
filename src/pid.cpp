#include "pid.hpp"
#include "main.hpp"
#include <cmath>

Velocity::Velocity(MotorGetter get): oldest{ 0 }, lastValue{ 0 }, get{ get } {}

void Velocity::update(int deltaTime)
{
    const int value = get();
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

TaskHandle PID::pidTask = nullptr;
std::vector<PID*> PID::pids;

void PID::initAll()
{
    pidTask = taskRunLoop(eventLoop, MOTOR_DELAY);
}

void PID::eventLoop()
{
    for (PID* pid : pids)
    {
        if (pid) pid->update(MOTOR_DELAY);
    }
}

PID::PID(float p, float i, float d, MotorGetter get, MotorSetter set)
    : uid{ pids.size() }, p{ p }, i{ i }, d{ d }, get{ get }, set{ set },
    velocity{ get }, targetMutex{ mutexCreate() }, targetPos{ 0 }
{
    pids.push_back(this);
}

PID::~PID()
{
    pids[uid] = nullptr;
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

void PID::update(int deltaTime)
{
    velocity.update(deltaTime);

    // determine which way we should go and by how much
    const int currentPos = velocity.getPos();
    mutexTake(targetMutex, 0);
    const int posError = targetPos - currentPos;
    mutexGive(targetMutex);

    // calculate power (clamped to the interval [-127, 127]) given encoder delta
    const int power = round(127 * tanh(p * posError));
    set(power);
}
