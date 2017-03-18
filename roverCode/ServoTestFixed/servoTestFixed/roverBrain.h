
#ifndef ROVER_BRAIN_H
#define ROVER_BRAIN_H


#include <Servo.h>
#include <Arduino.h>

#include "drivingBrain.h"
#include "blipperBrain.h"

//#define DEBUG



class roverBrain
{

  friend class testingAlgorithms;
public:
  roverBrain(Servo* leftServo, Servo* rightServo, Servo* inputServo);
  ~roverBrain();

  void driveToPole();

  void driveByPole();
  bool orientToPole();
  void redefinePoleDistance();
  bool driveToPoleHeadOn();

  drivingBrain* wheelDriver;
  blipperBrain* blipper;

private:

 
  

  
  
};

#endif


