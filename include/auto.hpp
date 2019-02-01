#ifndef AUTO_HPP
#define AUTO_HPP

/** Auton-related functions. */
namespace auton
{
/** Autonomous programs. */
enum Auton
{
    NOTHING, DRIVE_LAUNCH, TEST_AUTON, NUM_AUTONS
};

/** Autonomous program names. The sublists correspond to each LCD line. */
extern const char* autonNames[NUM_AUTONS][2];

/** Gets the current auton state. */
Auton getAuton();

/** Sets the current auton state. */
void setAuton(Auton value);
} // end namespace auton

#endif // AUTO_HPP
