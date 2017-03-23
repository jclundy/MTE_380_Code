#include "spool.h"

//#define RESTING_uS 1525
//#define UNSPOOL_SLOW_uS 1550;
//#define UNSPOOL_FAST_us 1575;
//#define TAKE_IN_FAST_uS 1400
//#define TAKE_IN_SLOW_uS 1500


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
	motor->writeMicroseconds(UNSPOOL_FAST_us);
}

void spool::unspoolSlow() {
  motor->writeMicroseconds(UNSPOOL_SLOW_uS);
}

// reverses with enough torque to hold itself from falling
void spool::takeInFast() {
	motor->writeMicroseconds(TAKE_IN_FAST_uS);
}

// reverses at slow speed for loading the rope
void spool::takeInSlow() {
	motor->writeMicroseconds(TAKE_IN_SLOW_uS);
}
