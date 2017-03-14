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


  leftServo->writeMicroseconds(1000);
  rightServo->writeMicroseconds(2000);
}

