  /*
*  This code is in the public domain.
*  (Do whatever you want with it.)
*  min-56 deg
*/

// Need the Servo library
#include <Servo.h>

#define MOTOR_PIN 6
#define CW_FULL_SPEED_uS 1300
#define CCW_FULL_SPEED_uS 1700
#define RESTING_uS 1525

#define UNWIND_SPEED 1510
#define CONTROLLED_LOWER_VALUE 1500
#define HOLD_VALUE 1600

#define INITIAL_WAIT 3000
#define RAMP_DRIVE_TIME 4000

Servo spoolMotor;

void setup()
{
  spoolMotor.attach(MOTOR_PIN);
  delay(10);
  spoolMotor.writeMicroseconds(RESTING_uS);
}


void loop()
{
  // 3 second delay before lowering - no torque
  spoolMotor.writeMicroseconds(RESTING_uS);
  delay(INITIAL_WAIT);
  
  
  //unspool for 4 seconds
  spoolMotor.writeMicroseconds(UNWIND_SPEED);
  delay(UNWIND_WAIT);
  
  spoolMotor.writeMicrseconds(HOLD_VALUE);
  delay()
  // first phase - driving onto the ramp
  // spool needs to unwind - drive at 
  
  spoolMotor.writeMicroseconds(val);
}

