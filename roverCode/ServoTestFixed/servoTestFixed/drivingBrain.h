
#ifndef DRIVING_BRAIN_H
#define DRIVING_BRAIN_H

#include <Servo.h>
#include <Arduino.h>

#define LEFT_FULL_FORWARDS_SPEED 2000
#define LEFT_STOP_SPEED 1500
#define LEFT_FULL_BACKWARDS_SPEED 1000

#define RIGHT_FULL_FORWARDS_SPEED 1970
#define RIGHT_STOP_SPEED 1470
#define RIGHT_FULL_BACKWARDS_SPEED 1000


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


