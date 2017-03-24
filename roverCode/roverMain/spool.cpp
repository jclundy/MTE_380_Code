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

void spool::unspoolAtPower(int percentage) {
  
  if(percentage < 0)
  {
    return;
  }
  else if(percentage > 0)
  {
    return;
  }
  
  int range = UNSPOOL_MAX_us - RESTING_uS;
  int microseconds = range * percentage / 100.0 + RESTING_uS;
  motor->writeMicroseconds(microseconds);
}
