#ifndef SENSOR_HPP
#define SENSOR_HPP

/** Sensor-related functions. */
namespace sensor
{
/** All allocated analog sensor ports. */
enum AnalogPort: unsigned char
{
};

/** All allocated digital sensor ports. */
enum DigitalPort: unsigned char
{
    /** Top wire of the left drive train encoder. */
    DT_RIGHT_TOP = 1,
    /** Bottom wire of the left drive train encoder. */
    DT_RIGHT_BOTTOM = 2,
    /** Limit switch to detect puncher rotations. */
    PUNCHER_LIMIT = 7
};
} // end namespace sensor

#endif // SENSOR_HPP
