#ifndef MOTOR_HPP
#define MOTOR_HPP

/** Motor-related functions. */
namespace motor
{
/**
 * All allocated motor ports. Ports 4-7 go into the power expander,
 * corresponding to ports A-D.
 */
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
    /** Ball intake treads. */
    BALL_INTAKE = 5,
    /** Unused motor. */
    UNUSED = 6,
    /** Right lift motor. */
    LIFT_RIGHT = 7,
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
 * Sets a motor to a given power. Use this function rather than motorSet.
 * @param port Port to be powered.
 * @param power Motor power.
 */
void set(Port port, int power);
} // end namespace motor

#endif // MOTOR_HPP
