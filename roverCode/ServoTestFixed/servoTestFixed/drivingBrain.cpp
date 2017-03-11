#include "drivingBrain.h"



drivingBrain::drivingBrain(Servo* inLeftServo, Servo* inRightServo)
{
  leftServo = inLeftServo;
  rightServo = inRightServo;
  
}

drivingBrain::~drivingBrain()
{
  delete leftServo;
  delete rightServo;
}

void drivingBrain::driveForwards(int power) {

  int speedVal = 1500 + power * (2000 - 1500) / 100.0;

  leftServo->writeMicroseconds(speedVal);
  rightServo->writeMicroseconds(speedVal);
}

