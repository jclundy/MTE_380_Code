#include "spool.h"

spool::spool(Servo* servo) {
	motor = servo;
}

spool::~spool() {
	delete motor;
}

// sends signal to servo to stop rotation
void spool::stopRotating() {
	motor->writeMicroseconds(RESTING_uS);
}

// unspools at moderate speed
void spool::unspool() {
	motor->writeMicroseconds(UNWIND_uS);
}

// reverses with enough torque to hold itself from falling
void spool::takeInFast() {
	motor->writeMicroseconds(TAKE_IN_FAST_uS);
}

// reverses at slow speed for loading the rope
void spool::takeInSlow() {
	motor->writeMicroseconds(TAKE_IN_SLOW_uS);
}