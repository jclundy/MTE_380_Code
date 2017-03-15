#ifndef SPOOL_H
#define SPOOL_H

#include <Servo.h>
#include <Arduino.h>

// spool servo values
#define RESTING_uS 1525
#define UNWIND_uS 1510
#define TAKE_IN_FAST_uS 1600
#define TAKE_IN_SLOW_uS 1560

class spool {
public:
	spool(Servo* motor);
	~spool();

	// sends signal to servo to stop rotation
	void stopRotating();

	// unspools at moderate speed
	void unspool();

	// reverses with enough torque to hold itself from falling
	void takeInFast();

	// reverses at slow speed for loading the rope
	void takeInSlow();

	Servo* motor;
};
#endif
