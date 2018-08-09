#ifndef MOTOR_HPP
#define MOTOR_HPP

/** Motor-related functions. */
namespace motor
{
/** All allocated motor ports. */
enum Port: unsigned char
{
    /** Ball intake. */
    BALL_INTAKE = 1,
    /** Left front drive. */
    DRIVE_LF = 2,
    /** Left back drive. */
    DRIVE_LB = 3,
    /** Slip gear puncher. */
    PUNCHER_1 = 4,
    /** Slip gear puncher. */
    PUNCHER_2 = 5,
    /** Left lift motor. */
    LIFT_LEFT = 6,
    /** Right lift motor. */
    LIFT_RIGHT = 7,
    /** Right front drive. */
    DRIVE_RF = 8,
    /** Right back drive. */
    DRIVE_RB = 9,
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
