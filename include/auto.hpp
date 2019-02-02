#ifndef AUTO_HPP
#define AUTO_HPP

/** Auton-related functions. */
namespace auton
{
/** Autonomous programs. */
enum Auton
{
    NOTHING, TEST, FLAGS_CLOSE, FLAGS_PARK_CLOSE_RED, FLAGS_PARK_CLOSE_BLUE,
    FLAGS_FAR, CAPS_FAR_RED, CAPS_FAR_BLUE, NUM_AUTONS
};

/** Autonomous program names. The sublists correspond to each LCD line. */
extern const char* autonNames[NUM_AUTONS][2];

/** Gets the current auton state. */
Auton getAuton();

/** Sets the current auton state. */
void setAuton(Auton value);
} // end namespace auton

#endif // AUTO_HPP
