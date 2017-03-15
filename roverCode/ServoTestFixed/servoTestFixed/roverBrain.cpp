#include "roverBrain.h"


roverBrain::roverBrain(Servo* leftServo, Servo* rightServo, Servo* sensorServo) {

  blipper = new blipperBrain(sensorServo);
  wheelDriver = new drivingBrain(leftServo, rightServo);
  
}

roverBrain::~roverBrain() {
  delete blipper;
  delete wheelDriver;
}

void roverBrain::driveToPole() {

  bool roverResult;
  
  driveByPole();
  orientToPole();
  #ifdef DEBUG
    Serial.print("Pole position: ");
    Serial.println(blipper->lastKnownPolePosition,10);
    Serial.print("Current reading: ");
    Serial.println(blipper->getUltrasonicRead(),10);
  #endif
  redefinePoleDistance();
  delay(100);
  roverResult = driveToPoleHeadOn();

  if (roverResult) {
    #ifdef DEBUG
      Serial.println("SUCCESS - DRIVETOPOLE");
    #endif
  } else {
    #ifdef DEBUG
      Serial.println("SUCCESS - DRIVETOPOLE");
    #endif
  }
  
  
  
}

void roverBrain::driveByPole() {
  double returnValue;

  blipper->rotateServo(175);
  delay(300);

  wheelDriver->driveForwards(90);
  returnValue = blipper->waitToSeePole();
  delay(1000);

  #ifdef DEBUG
    Serial.print("Pole Found: ");
    Serial.println(returnValue,10);
    Serial.println("SUCCESS - DRIVEBYPOLE");
  #endif

  wheelDriver->rotateDegrees(90);
  blipper->rotateServo(90);
  delay(250);
}

bool roverBrain::orientToPole() {
  int returnValue;
  
  blipper->rotateServo(90);
  delay(500);

  returnValue = blipper->findPolePosition();
  delay(100);
  
  #ifdef DEBUG
    Serial.print("Pole found at: ");
    Serial.println(returnValue);
  #endif

  

  if (returnValue != -1) {
    wheelDriver->rotateDegrees(returnValue - 90);
    delay(500);
  
    int returnValue = blipper->findPolePosition();
    
    #ifdef DEBUG
      Serial.print("New Pole found at: ");
      Serial.println(returnValue);
    #endif

    if (returnValue != 90) {
      #ifdef DEBUG
        Serial.println("Redoing orientation");
      #endif
      
      orientToPole();
      
    } else {
      #ifdef DEBUG
        Serial.println("SUCCESS - ORIENTTOPOLE");
      #endif
      return true;
    }
    
  } else {
    #ifdef DEBUG
      Serial.println("FAIL - ORIENTTOPOLE");
    #endif
    return false;
  }
}

void roverBrain::redefinePoleDistance() {

  blipper->lastKnownPolePosition = blipper->getUltrasonicRead();
  blipper->lastReadingValue = blipper->lastKnownPolePosition;
  
}

bool roverBrain::driveToPoleHeadOn() {

  bool success;
  bool findingPole = true;

  int poleFindingReturnValue;

  while (findingPole) {
    wheelDriver->driveForwards(90);
    delay(10);

    poleFindingReturnValue = blipper->driveTowardsPole();
  
    wheelDriver->driveStop();
  
    if (poleFindingReturnValue) {
      #ifdef DEBUG
        Serial.print("Found pole at distance: ");
        Serial.println(blipper->lastReadingValue,10);
      #endif
      success = true;
      findingPole = false;
    } else {
      #ifdef DEBUG
        Serial.print("Lost Pole at distance: ");
        Serial.println(blipper->lastReadingValue,10);
      #endif 
      
      delay(50);

      bool poleOrientationResult = orientToPole();

      if (!poleOrientationResult) {
        success = false;
        findingPole = false;
      }
    }
  }

  if (success) {
    #ifdef DEBUG
      Serial.println("SUCCESS - DRIVETOPOLEHEADON");
    #endif
    return true;
  } else {
    #ifdef DEBUG
      Serial.print("Failure: Last known pole position: ");
      Serial.println(blipper->lastKnownPolePosition,10);
      Serial.println("FAIL - DRIVETOPOLEHEADON");
    #endif
    return false;
  }
  
}

