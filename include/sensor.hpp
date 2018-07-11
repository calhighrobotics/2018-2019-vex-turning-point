#ifndef SENSOR_HPP
#define SENSOR_HPP

/** Sensor-related functions. */
namespace sensor
{
/** All allocated digital sensor ports. */
enum DigitalPort: unsigned char
{
    /** Limit switch to detect puncher rotations. */
    PUNCHER_LIMIT = 7
};

/** Initializes all the sensor ports. Should be called in `initializeIO()`. */
void init();
} // end namespace sensor

#endif // SENSOR_HPP
