#ifndef PID_HPP
#define PID_HPP

#include "mutexVar.hpp"
#include <API.h>

/** Tracks the position and velocity of a side of the lift. */
class Velocity
{
public:
    /**
     * Updates position and velocity tracking data.
     * @param value Encoder value.
     * @param deltaTime Time in milliseconds between last update.
     */
    void update(int value, int deltaTime);

    /** Gets the velocity in ticks per millisecond. */
    float getVel() const;

private:
    /** Maximum number of velocities to keep track of. */
    static constexpr int maxVelocities = 10;

    /** Adds another velocity value to the rolling average. */
    void addVel(int vel);

    /** Tracks the last `maxVelocities` to calculate the rolling average. */
    float velocities[maxVelocities] = {0};
    /** Position of the oldest velocity value in the queue. */
    int oldest = 0;
    /** Value of the last position. Used in differentiation. */
    int lastValue = 0;
};

/** PID position controller. */
class PID
{
public:
    /** Initializes the targetPos mutex var. */
    void init(float kP, float kI, float kD);

    /**
     * Updates the PID.
     * @param value Encoder value.
     * @param deltaTime Delta time in ms.
     * @returns The power at which to set the motors.
     */
    int update(int value, int deltaTime);

    /**
     * Sets the target position of the PID in encoder ticks. Protected by a
     * mutex.
     */
    void setTargetPos(int pos);

private:
    /** Proportional term coefficient. */
    float kP = 0;
    /** Integral term coefficient. */
    float kI = 0;
    /** Derivative term coefficient. */
    float kD = 0;

    /** Velocity tracker. Used in derivative term. */
    Velocity velocity;
    /** Target position. */
    MutexVar<int> targetPos = 0;
};

#endif // PID_HPP
