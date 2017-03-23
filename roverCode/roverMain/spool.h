#ifndef SPOOL_H
#define SPOOL_H

#include <Servo.h>
#include <Arduino.h>
//Spool states
#define SPOOL_UP 0
#define WAITING_FOR_LIFT_COM 1
#define DRIVING_FORWARD 2
#define DRIVING_DOWN_SLOPE 3
#define VERTICAL_LOWERING 4
#define TOUCHING_DOWN 5
#define FINISHED_LOWERING 6

//time windows (in milliseconds)
#define DRIVING_FORWARD_WINDOW 3000
#define DRIVING_DOWN_SLOPE_WINDOW 3000
#define VERTICAL_LOWERING_WINDOW 10000
#define TOUCHING_DOWN_WINDOW 1000
#define FINISHED_LOWERING_WINDOW 1000

// spool servo values
#define RESTING_uS 1525
#define UNSPOOL_SLOW_uS 1550
#define UNSPOOL_FAST_us 1575
#define TAKE_IN_FAST_uS 1400
#define TAKE_IN_SLOW_uS 1500

// drive motor power values
class spool {
public:
	spool(Servo* servo);
	~spool();

	// sends signal to servo to stop rotation
	void stopRotating();

	// unspools at moderate speed
	void unspool();

	// reverses with enough torque to hold itself from falling
	void takeInFast();

	// reverses at slow speed for loading the rope
	void takeInSlow();

private:
	Servo* motor;
};
#endif
