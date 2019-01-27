#include "pid.hpp"
#include <algorithm>
#include <cmath>
#include <numeric>

void PID::init(float kP, float kI, float kD, int minOut, int maxOut)
{
    if (mutex) mutexTake(mutex, 0);

    // initialize or update fields
    this->minOut = minOut;
    this->maxOut = maxOut;
    // don't reset targetPos because that's handled by another function
    this->kP = kP;
    this->kI = kI;
    // don't reset integral because we don't want to have to re-integrate the
    //  offset, and will reclamp itself on the next update() call
    this->kD = kD;
    for (float& deriv : derivs) deriv = 0;
    // don't reset oldestDeriv because its index within derivs doesn't matter
    //  anymore
    // don't reset lastError because that would cause a derivative spike

    if (mutex) mutexGive(mutex);
    else mutex = mutexCreate();
}

void PID::setTargetPos(int pos)
{
    mutexTake(mutex, 0);
    if (pos != targetPos)
    {
        // new target position means previous (unscaled) derivs have to be reset
        for (float& deriv : derivs) deriv = 0;
    }
    targetPos = pos;
    mutexGive(mutex);
}

int PID::update(int value, int deltaTime)
{
    mutexTake(mutex, 0);

    const int error = targetPos - value;

    // proportional term
    const float p = kP * error;

    // integral term
    integral += kI * error * deltaTime;
    // clamp integral between minOut/maxOut to prevent windup
    integral = std::max(static_cast<float>(minOut),
            std::min(integral, static_cast<float>(maxOut)));
    const float i = integral;

    // derivative term
    const float deriv = (float) (error - lastError) / deltaTime;
    lastError = error;
    // replace oldest velocity with the newest one
    derivs[oldestDeriv++] = deriv;
    if (oldestDeriv >= maxDerivs) oldestDeriv = 0;
    // calculate rolling average of all the past derivatives
    const float d = kD *
        std::accumulate(derivs, &derivs[maxDerivs], 0) / maxDerivs;

    // sum P, I, and D terms, with tanh to smooth the curve
    const int pid = p + i + d;
    const int power = std::max(minOut, std::min(pid, maxOut));
    printf("enc=%d target=%d p=%.2f i=%2.f d=%.2f power=%d\n", value, targetPos,
        p, i, d, power);

    mutexGive(mutex);
    return power;
}
