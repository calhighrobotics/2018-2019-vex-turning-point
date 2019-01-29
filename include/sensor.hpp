#ifndef SENSOR_HPP
#define SENSOR_HPP

/** Sensor-related functions. */
namespace sensor
{
/** All allocated digital sensor ports. */
enum DigitalPort: unsigned char
{
    /** Top wire of the left drive train encoder. */
    DT_LEFT_TOP = 1,
    /** Bottom wire of the left drive train encoder. */
    DT_LEFT_BOTTOM = 2,
    /** Top wire of the right lift encoder. */
    LIFT_RIGHT_TOP = 3,
    /** Bottom wire of the right lift encoder. */
    LIFT_RIGHT_BOTTOM = 4,
    /** Top wire of the right lift encoder. */
    LIFT_LEFT_TOP = 5,
    /** Bottom wire of the left lift encoder. */
    LIFT_LEFT_BOTTOM = 6
};
} // end namespace sensor

#endif // SENSOR_HPP
