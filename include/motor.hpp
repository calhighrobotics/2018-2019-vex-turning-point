#ifndef MOTOR_HPP
#define MOTOR_HPP

/** Motor-related functions. */
namespace motor
{
/** All allocated motor ports. */
enum Port: unsigned char
{
    /** Cap intake wrist. */
    WRIST = 1,
    /** Right front drive. */
    DRIVE_RF = 2,
    /** Right back drive. */
    DRIVE_RB = 3,
    /** Left lift motor. */
    LIFT_LEFT = 4,
    /** Cap intake pitch servo. */
    CAP_PITCH = 5,
    /** Right lift motor. */
    LIFT_RIGHT = 6,
    /** Ball intake treads. */
    BALL_INTAKE = 7,
    /** Left front drive. */
    DRIVE_LF = 8,
    /** Left back drive. */
    DRIVE_LB = 9,
    /** Slip gear puncher. */
    PUNCHER = 10,
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
