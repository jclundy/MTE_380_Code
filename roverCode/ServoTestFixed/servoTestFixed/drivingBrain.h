
#ifndef DRIVING_BRAIN_H
#define DRIVING_BRAIN_H

#include <Servo.h>
#include <Arduino.h>

//Make sure to change these values for your servo!
#define LEFT_FULL_FORWARDS_SPEED 970
#define LEFT_STOP_SPEED 1470
#define LEFT_FULL_BACKWARDS_SPEED 1970

#define RIGHT_FULL_FORWARDS_SPEED 2000
#define RIGHT_STOP_SPEED 1500
#define RIGHT_FULL_BACKWARDS_SPEED 1000

//Once you know your 90 degree delay just put it here
#define DEG_90_TURN_DELAY 1000

//Once you know your trim value just put it here
#define INITIAL_TRIM_VALUE 0.65

//A class to control the driving of the robot
class drivingBrain
{

  friend class testingAlgorithms;
  friend class roverBrain;
public:
  drivingBrain(Servo* leftServo, Servo* rightServo);
  ~drivingBrain();

  //Drive forwards at this specified power
  void driveForwards(int power);
  //Stop the robot
  void driveStop();
  //Rotate at this specified power
  void rotateAtSpeed(int power);
  //Turn this many degrees
  void rotateDegrees(int numDegrees);

  //Editable trim value
  double trimValue;



private:
  Servo* leftServo;
  Servo* rightServo;
  
};

#endif


