#ifndef AUTO_HPP
#define AUTO_HPP

/** Auton-related functions. */
namespace auton
{
/** Autonomous programs. */
enum Auton
{
    NOTHING, FLAGS_CLOSE, FLAGS_PARK_CLOSE_RED, FLAGS_PARK_CLOSE_BLUE,
    NUM_AUTONS
};

/** Autonomous program names. The sublists correspond to each LCD line. */
extern const char* autonNames[NUM_AUTONS][2];

/** Gets the current auton state. */
Auton getAuton();

/** Sets the current auton state. */
void setAuton(Auton value);
} // end namespace auton

#endif // AUTO_HPP
