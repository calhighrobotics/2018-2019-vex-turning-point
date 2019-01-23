#ifndef PID_HPP
#define PID_HPP

#include <API.h>

/** PID position controller. */
class PID
{
public:
    /**
     * Initializes the targetPos mutex var.
     * @param kP Proportional term coefficient.
     * @param kI Integral term coefficient.
     * @param kD Derivative term coefficient.
     * @param minOut Minimum output value.
     * @param maxOut Maximum output value.
     */
    void init(float kP, float kI, float kD, int minOut = -127,
        int maxOut = 127);

    /**
     * Sets the target position of the PID in encoder ticks. Protected by a
     * mutex.
     */
    void setTargetPos(int pos);

    /**
     * Updates the PID.
     * @param value Encoder value.
     * @param deltaTime Delta time in ms.
     * @returns The power at which to set the motors.
     */
    int update(int value, int deltaTime);

private:
    /** Minimum output value. */
    int minOut = 0;
    /** Maximum output value. */
    int maxOut = 0;

    /** Target position. */
    int targetPos = 0;
    /** Protects fields from concurrent modification from an outside thread. */
    Mutex mutex = nullptr;

    /** Proportional term coefficient. */
    float kP = 0;

    /** Integral term coefficient. */
    float kI = 0;
    /** Accumulates the integral of the error in tick-milliseconds. */
    float integral = 0;

    /** Derivative term coefficient. */
    float kD = 0;
    /** Maximum number of error derivatives to keep track of. */
    static constexpr int maxDerivs = 10;
    /** Tracks the last `maxDerivs` derivatives in ticks per millisecond. */
    float derivs[maxDerivs] = {0};
    /** Position of the oldest velocity value in the queue. */
    int oldestDeriv = 0;
    /** Previous error value. Used in differentiation. */
    int lastError = 0;
};

#endif // PID_HPP
