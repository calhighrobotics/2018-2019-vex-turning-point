#ifndef MOTOR_HPP
#define MOTOR_HPP

/** Motor-related functions. */
namespace motor
{
/** All allocated motor ports. */
enum Port: unsigned char
{
    /** Left lift motor. */
    LIFT_LEFT = 1,
    /** Left front drive. */
    DRIVE_LF = 2,
    /** Left back drive. */
    DRIVE_LB = 3,
    /** Ball intake. */
    BALL_INTAKE = 6,
    /** Slip gear puncher. */
    PUNCHER = 7,
    /** Right front drive. */
    DRIVE_RF = 8,
    /** Right back drive. */
    DRIVE_RB = 9,
    /** Right lift motor. */
    LIFT_RIGHT = 10,
    /** Maximum amount of motor ports. */
    MAX_MOTOR_PORTS = 10
};

/**
 * Sets an internal lock to allow a series of calls to {@link set} to be made.
 */
void lock();

/**
 * Signals the motor management thread that the user is no longer trying to set
 * the motors.
 */
void unlock();

/**
 * Sets a motor to a given power. It's recommended to use this function rather
 * than motorSet.
 * @param port Port to be powered.
 * @param power Motor power.
 */
void set(Port port, int power);
} // end namespace motor

#endif // MOTOR_HPP
