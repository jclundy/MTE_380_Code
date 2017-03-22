
#ifndef BLIPPER_BRAIN_H
#define BLIPPER_BRAIN_H


#define FRONT_TRIG_PIN 7
#define FRONT_ECHO_PIN 8
#define LEFT_TRIG_PIN 9
#define LEFT_ECHO_PIN 10
#define RIGHT_TRIG_PIN 11
#define RIGHT_ECHO_PIN 12

#define LOOKLEFT
#define LOOKRIGHT

#define DEBUG



#include <Servo.h>
#include <Arduino.h>

class blipperBrain
{

  friend class testingAlgorithms;
  friend class roverBrain;
public:
  blipperBrain();
  ~blipperBrain();

  double lastFrontReadingValue;
  double lastLeftReadingValue;
  double lastRightReadingValue;
  double lastKnownPolePosition;
  double lastKnownWallDistance;
  double currentFrontReadingValue;
  double currentLeftReadingValue;
  double currentRightReadingValue;
  int wallDirection;
  
  double getUltrasonicRead(int TRIG_PIN, int ECHO_PIN);
  double getFrontUltrasonicRead() { delay(15); return getUltrasonicRead(FRONT_TRIG_PIN,FRONT_ECHO_PIN); }
  double getLeftUltrasonicRead() { delay(15); return getUltrasonicRead(LEFT_TRIG_PIN,LEFT_ECHO_PIN); }
  double getRightUltrasonicRead() { delay(15); return getUltrasonicRead(RIGHT_TRIG_PIN,RIGHT_ECHO_PIN); }
  double getAllUltrasonicRead() {
    delay(15);
    currentFrontReadingValue = getUltrasonicRead(FRONT_TRIG_PIN,FRONT_ECHO_PIN);
    currentLeftReadingValue = getUltrasonicRead(LEFT_TRIG_PIN,LEFT_ECHO_PIN);
    currentRightReadingValue = getUltrasonicRead(RIGHT_TRIG_PIN,RIGHT_ECHO_PIN);
  }

  int waitToSeePole();
  int driveTowardsPole();

private:

  
};

#endif


