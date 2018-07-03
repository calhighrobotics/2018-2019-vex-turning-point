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
    /** Right front drive. */
    DRIVE_RF = 8,
    /** Right back drive. */
    DRIVE_RB = 9,
    /** Slip gear puncher. */
    PUNCHER = 10
};
} // end namespace motor

#endif // MOTOR_HPP
