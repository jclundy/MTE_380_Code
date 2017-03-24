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
#define WAITING_FOR_LIFT_COM_MAX_WINDOW 15000
#define WAITING_FOR_LIFT_COM_MIN_WINDOW 1000

#define DRIVING_FORWARD_MAX_WINDOW 1500

#define DRIVING_DOWN_SLOPE_MAX_WINDOW 1000

#define VERTICAL_LOWERING_FAST_WINDOW 2500
#define VERTICAL_LOWERING_SLOW_WINDOW 750

#define TOUCHING_DOWN_MAX_WINDOW 1500

// spool servo values
#define RESTING_uS 1525
#define UNSPOOL_SLOW_uS 1550
#define UNSPOOL_FAST_us 1555

#define UNSPOOL_MAX_us 1600
#define TAKE_IN_FAST_uS 1400
#define TAKE_IN_SLOW_uS 1450

// drive motor power values
class spool {
public:
	spool(Servo* servo);
	~spool();

	// sends signal to servo to stop rotation
	void stopRotating();

	// unspools at moderate speed
	void unspool();

        void unspoolSlow(); 

	// reverses with enough torque to hold itself from falling
	void takeInFast();

	// reverses at slow speed for loading the rope
	void takeInSlow();

        // takes in a percentage between max speed and lowest speed
        void unspoolAtPower(int percentage);


private:
	Servo* motor;
};
#endif
