#ifndef PID_HPP
#define PID_HPP

#include <API.h>
#include <vector>

/** Gets the current position. */
using MotorGetter = int(*)();
/** Sets the motor power. */
using MotorSetter = void(*)(int);

/** Tracks the position and velocity of a side of the lift. */
class Velocity
{
public:
    /**
     * Creates a Velocity tracker object.
     * @param get Position getter.
     */
    Velocity(MotorGetter get);

    /**
     * Updates position and velocity tracking data.
     * @param deltaTime Time in milliseconds between last update.
     */
    void update(int deltaTime);

    /** Gets the last-recorded position. */
    int getPos() const;

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
    int oldest;
    /** Value of the last position. Used in differentiation. */
    int lastValue;
    /** Gets the current position. */
    MotorGetter get;
};

/** PID position controller. */
class PID
{
public:
    /** Initializes the event loop task. */
    static void initAll();

    /**
     * Creates a PID object.
     * @param kP Proportional term coefficient.
     * @param kI Integral term coefficient.
     * @param kD Derivative term coefficient.
     * @param get Position getter.
     * @param set Motor group setter.
     */
    PID(float kP, float kI, float kD, MotorGetter get, MotorSetter set);
    ~PID();

    /** Gets the current position of the PID in encoder ticks. */
    int getCurrentPos() const;

    /**
     * Sets the target position of the PID in encoder ticks. Protected by a
     * mutex.
     */
    void setTargetPos(int pos);

private:
    /** Manages the event loop task. */
    static TaskHandle pidTask;
    /** All registered PID objects. */
    static std::vector<PID*> pids;
    /** Event loop task. */
    static void eventLoop();

    /**
     * Updates the PID.
     * @param deltaTime Delta time in ms.
     */
    void update(int deltaTime);

    /** Unique id. Used in deregistering after destruction. */
    const size_t uid;
    /** Proportional term coefficient. */
    const float kP;
    /** Integral term coefficient. */
    const float kI;
    /** Derivative term coefficient. */
    const float kD;
    /** Position getter. */
    const MotorGetter get;
    /** Motor group setter. */
    const MotorSetter set;
    /** Velocity tracker. Used in derivative term. */
    Velocity velocity;
    /** Mutex for setting targetPos. */
    Mutex targetMutex;
    /** Target position. */
    int targetPos;
};

#endif // PID_HPP
