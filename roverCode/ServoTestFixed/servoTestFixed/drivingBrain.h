
#ifndef DRIVING_BRAIN_H
#define DRIVING_BRAIN_H

#include <Servo.h>
#include <Arduino.h>

#define LEFT_FULL_FORWARDS_SPEED 2000
#define RIGHT_FULL_FORWARDS_SPEED 2000

class drivingBrain
{

  friend class testingAlgorithms;
public:
  drivingBrain(Servo* leftServo, Servo* rightServo);
  ~drivingBrain();

  void driveForwards(int power);
  void driveBackwards(int power);
  void rotateLeftAtSpeed(int power);
  void rotateRightAtSpeed(int power);
  void rotateDegrees(int numDegrees);


private:
  Servo* leftServo;
  Servo* rightServo;
  
};

#endif


