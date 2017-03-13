#include "drivingBrain.h"



drivingBrain::drivingBrain(Servo* inLeftServo, Servo* inRightServo)
{
  leftServo = inLeftServo;
  rightServo = inRightServo;

  trimValue = INITIAL_TRIM_VALUE;

  driveStop();
  
}

drivingBrain::~drivingBrain()
{
  delete leftServo;
  delete rightServo;
}

void drivingBrain::driveForwards(int power) {

  

  int leftServoMicroseconds = LEFT_STOP_SPEED + (LEFT_FULL_FORWARDS_SPEED - LEFT_STOP_SPEED) * (power / 100.0) * (1 - trimValue);
  int rightServoMicroseconds = RIGHT_STOP_SPEED + (RIGHT_FULL_FORWARDS_SPEED - RIGHT_STOP_SPEED) * (power / 100.0) * (1 + trimValue);

  
  leftServo->writeMicroseconds(leftServoMicroseconds);
  rightServo->writeMicroseconds(rightServoMicroseconds);
}

void drivingBrain::driveStop() {
  leftServo->writeMicroseconds(LEFT_STOP_SPEED);
  rightServo->writeMicroseconds(RIGHT_STOP_SPEED);
}

void drivingBrain::rotateAtSpeed(int power) {

  int leftServoMicroseconds = LEFT_STOP_SPEED - (LEFT_FULL_FORWARDS_SPEED - LEFT_STOP_SPEED) * (power / 100.0) * (1 - trimValue);
  int rightServoMicroseconds = RIGHT_STOP_SPEED + (RIGHT_FULL_FORWARDS_SPEED - RIGHT_STOP_SPEED) * (power / 100.0) * (1 + trimValue);

  
  leftServo->writeMicroseconds(leftServoMicroseconds);
  rightServo->writeMicroseconds(rightServoMicroseconds);

}

void drivingBrain::rotateDegrees(int inDegrees) {

  if (inDegrees > 0) {
    rotateAtSpeed(90);
  } else {
    rotateAtSpeed(-90);
    inDegrees = -inDegrees;
  }

  int delayAmount = (inDegrees / 90.0) * DEG_90_TURN_DELAY;
  
  delay(delayAmount);

  driveStop();
  
}



