#include "pid.hpp"
#include <algorithm>
#include <cmath>
#include <numeric>

void PID::init(float kP, float kI, float kD, int minOut, int maxOut)
{
    this->kP = kP;
    this->kI = kI;
    this->kD = kD;
    this->minOut = minOut;
    this->maxOut = maxOut;
    mutex = mutexCreate();
}

void PID::setTargetPos(int pos)
{
    mutexTake(mutex, 0);
    if (pos != targetPos)
    {
        // new target position means previous states have to be reset
        integral = 0;
        for (float& deriv : derivs) deriv = 0;
        lastError = 0;
    }
    targetPos = pos;
    mutexGive(mutex);
}

int PID::update(int value, int deltaTime)
{
    const int error = targetPos - value;

    // proportional term
    const float p = kP * error;

    // integral term
    integral += kI * error * deltaTime;
    // clamp integral between minOut/maxOut to prevent windup
    integral = std::max((float) minOut, std::min(integral, (float) maxOut));
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
    float scalar = tanh(p + i + d);
    // tanh's range is (-1, 1) so scale by minOut/maxOut power accordingly
    if (scalar > 0) scalar *= abs(maxOut);
    else if (scalar < 0) scalar *= abs(minOut);

    const int power = round(scalar);
    printf("value: %d, p: %.2f, power: %d\n", value, p, power);
    return power;
}
