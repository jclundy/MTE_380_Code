
#ifndef ROVER_BRAIN_H
#define ROVER_BRAIN_H


#include <Servo.h>
#include <Arduino.h>

#include "drivingBrain.h"
#include "blipperBrain.h"

#define POLEDRIVEDELAYSLOPE 0
#define POLEDRIVEDELAYB 1400



class roverBrain
{

  friend class testingAlgorithms;
public:
  roverBrain(Servo* frontLeftServo, Servo* frontRightServo, Servo* backLeftServo, Servo* backRightServo, Servo* inputServo);
  ~roverBrain();

  bool driveToPole();

  int driveByPole();
  void redefinePoleDistance();
  bool driveToPoleHeadOn();

  bool rotateUntilSeePole(double tolerance, int rotateDirection);

  drivingBrain* wheelDriver;
  blipperBrain* blipper;

private:

 
  

  
  
};

#endif


