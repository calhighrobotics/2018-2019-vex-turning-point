#ifndef PID_HPP
#define PID_HPP

#include <API.h>
#include <vector>

/** Tracks the position and velocity of a side of the lift. */
class Velocity
{
public:
    /**
     * Creates a Velocity tracker object.
     * @param get Position getter.
     */
    Velocity(PID::Getter get);

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
    float velocities[maxVelocities];
    /** Position of the oldest velocity value in the queue. */
    int oldest;
    /** Value of the last position. Used in differentiation. */
    int lastValue;
    /** Gets the current position. */
    PID::Getter get;
};

/** PID position controller. */
class PID
{
public:
    /** Gets the current position. */
    using Getter = int(*)();
    /** Sets the motor power. */
    using Setter = void(*)(int);

    /** Initializes the event loop task. */
    static void initAll();

    /**
     * Creates a PID object.
     * @param p Proportional term.
     * @param i Integral term.
     * @param d Derivative term.
     * @param get Position getter.
     * @param set Motor group setter.
     */
    PID(float p, float i, float d, Getter get, Setter set);
    ~PID();

    /** Sets the target position of the PID. Protected by a mutex. */
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
    /** Proportional term. */
    const float p;
    /** Integral term. */
    const float i;
    /** Derivative term. */
    const float d;
    /** Position getter. */
    const Getter get;
    /** Motor group setter. */
    const Setter set;
    /** Velocity tracker. Used in derivative term. */
    Velocity velocity;
    /** Mutex for setting targetPos. */
    Mutex targetMutex;
    /** Target position. */
    int targetPos;
};

#endif // PID_HPP
