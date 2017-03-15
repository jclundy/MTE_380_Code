
#ifndef BLIPPER_BRAIN_H
#define BLIPPER_BRAIN_H


#define TRIG_PIN 7
#define ECHO_PIN 8
#define BLIPPER_SERVO_PIN 9 
#define NUM_READINGS 90
#define SERVO_DEGREES_PER_SEC 150

#include <Servo.h>
#include <Arduino.h>

class blipperBrain
{

  friend class testingAlgorithms;
  friend class roverBrain;
public:
  blipperBrain(Servo* inputServo);
  ~blipperBrain();

  double lastReadingValue;
  double lastKnownPolePosition;
  
  
  void rotateServo(int pos);
  
  double getUltrasonicRead();

  double waitToSeePole();
  bool driveTowardsPole();
  

  int findPolePosition();

private:
  Servo* mainServo;
  

  
  
};

#endif


