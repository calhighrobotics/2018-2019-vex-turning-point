#ifndef AUTO_HPP
#define AUTO_HPP

/** Auton-related functions. */
namespace auton
{
/** Autonomous programs. */
enum Auton
{
    NOTHING, DRIVE_LAUNCH, NUM_AUTONS
};

/** Autonomous program names. The sublists correspond to each LCD line. */
extern const char* autonNames[NUM_AUTONS][2];

/** Gets the current auton state. */
Auton getAuton();

/** Sets the current auton state. */
void setAuton(Auton value);
}

#endif // AUTO_HPP
