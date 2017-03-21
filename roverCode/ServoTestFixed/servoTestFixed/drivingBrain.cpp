#include "drivingBrain.h"



drivingBrain::drivingBrain(Servo* inFrontLeftServo, Servo* inFrontRightServo, Servo* inBackLeftServo, Servo* inBackRightServo)
{
  frontLeftServo = inFrontLeftServo;
  frontRightServo = inFrontRightServo;

  backLeftServo = inBackLeftServo;
  backRightServo = inBackRightServo;

  trimValue = INITIAL_TRIM_VALUE;

  driveStop();
  
}

drivingBrain::~drivingBrain()
{
  delete frontLeftServo;
  delete frontRightServo;
  delete backLeftServo;
  delete backRightServo;
}

void drivingBrain::driveForwards(int power) {
  
  int frontLeftServoMicroseconds = FRONT_LEFT_STOP_SPEED + (FRONT_LEFT_FULL_FORWARDS_SPEED - FRONT_LEFT_STOP_SPEED) * (power / 100.0) * (1 - trimValue);
  int frontRightServoMicroseconds = FRONT_RIGHT_STOP_SPEED + (FRONT_RIGHT_FULL_FORWARDS_SPEED - FRONT_RIGHT_STOP_SPEED) * (power / 100.0) * (1 + trimValue);
  int backLeftServoMicroseconds = BACK_LEFT_STOP_SPEED + (BACK_LEFT_FULL_FORWARDS_SPEED - BACK_LEFT_STOP_SPEED) * (power / 100.0) * (1 - trimValue);
  int backRightServoMicroseconds = BACK_RIGHT_STOP_SPEED + (BACK_RIGHT_FULL_FORWARDS_SPEED - BACK_RIGHT_STOP_SPEED) * (power / 100.0) * (1 + trimValue);

  
  frontLeftServo->writeMicroseconds(frontLeftServoMicroseconds);
  frontRightServo->writeMicroseconds(frontRightServoMicroseconds);
  backLeftServo->writeMicroseconds(backLeftServoMicroseconds);
  backRightServo->writeMicroseconds(backRightServoMicroseconds);
}

void drivingBrain::driveStop() {
  frontLeftServo->writeMicroseconds(FRONT_LEFT_STOP_SPEED);
  frontRightServo->writeMicroseconds(FRONT_RIGHT_STOP_SPEED);
  backLeftServo->writeMicroseconds(BACK_LEFT_STOP_SPEED);
  backRightServo->writeMicroseconds(BACK_RIGHT_STOP_SPEED);
}

void drivingBrain::rotateAtSpeed(int power) {

<<<<<<< HEAD
  int leftServoMicroseconds = LEFT_STOP_SPEED - (LEFT_FULL_FORWARDS_SPEED - LEFT_STOP_SPEED) * (power / 100.0);
  int rightServoMicroseconds = RIGHT_STOP_SPEED + (RIGHT_FULL_FORWARDS_SPEED - RIGHT_STOP_SPEED) * (power / 100.0);
=======
  int frontLeftServoMicroseconds = FRONT_LEFT_STOP_SPEED + (FRONT_LEFT_FULL_FORWARDS_SPEED - FRONT_LEFT_STOP_SPEED) * (power / 100.0);
  int frontRightServoMicroseconds = FRONT_RIGHT_STOP_SPEED + (FRONT_RIGHT_STOP_SPEED - FRONT_RIGHT_FULL_FORWARDS_SPEED) * (power / 100.0);
  int backLeftServoMicroseconds = BACK_LEFT_STOP_SPEED + (BACK_LEFT_FULL_FORWARDS_SPEED - BACK_LEFT_STOP_SPEED) * (power / 100.0);
  int backRightServoMicroseconds = BACK_RIGHT_STOP_SPEED + (BACK_RIGHT_STOP_SPEED - BACK_RIGHT_FULL_FORWARDS_SPEED) * (power / 100.0);
>>>>>>> origin/master

  
  frontLeftServo->writeMicroseconds(frontLeftServoMicroseconds);
  frontRightServo->writeMicroseconds(frontRightServoMicroseconds);
  backLeftServo->writeMicroseconds(backLeftServoMicroseconds);
  backRightServo->writeMicroseconds(backRightServoMicroseconds);

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



