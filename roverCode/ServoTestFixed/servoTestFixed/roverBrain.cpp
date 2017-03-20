#include "roverBrain.h"


roverBrain::roverBrain(Servo* frontLeftServo, Servo* frontRightServo, Servo* backLeftServo, Servo* backRightServo, Servo* sensorServo) {

  blipper = new blipperBrain(sensorServo);
  wheelDriver = new drivingBrain(frontLeftServo, frontRightServo, backLeftServo, backRightServo);
  
}

roverBrain::~roverBrain() {
  delete blipper;
  delete wheelDriver;
}

bool roverBrain::driveToPole() {

  bool roverResult;
  
  driveByPole();

  if (abs(blipper->getAccurateUltrasonicRead() - blipper->lastKnownPolePosition) < 15) {
    redefinePoleDistance();
  }

  //XXXChanging orientation
  //roverResult = orientToPole();
  roverResult = rotateUntilSeePole(20,90);
  

    
  #ifdef DEBUG
    Serial.print("Pole position: ");
    Serial.println(blipper->lastKnownPolePosition,10);
    Serial.print("Current reading: ");
    Serial.println(blipper->getUltrasonicRead(),10);
  #endif
  if (!roverResult) {
    #ifdef DEBUG
      Serial.println("FAIL - DRIVETOPOLE");
    #endif
    return false;
  }
  delay(100);
  roverResult = driveToPoleHeadOn();

  if (roverResult) {
    #ifdef DEBUG
      Serial.println("SUCCESS - DRIVETOPOLE");
    #endif
    return true;
  } else {
    #ifdef DEBUG
      Serial.println("SUCCESS - DRIVETOPOLE");
    #endif
    return false;
  }
  
  
  
}

bool roverBrain::rotateUntilSeePole(double tolerance, int rotateDirection) {

  double readingValue = 999;
  int windowLength = 5;
  int numGoodReadings = 0;

  unsigned long startTime;

  bool searching = true;
  bool result;

  int motorPower;

  if (rotateDirection > 0) {
    motorPower = 40;
  } else {
    motorPower = -40;
  }

  wheelDriver->rotateAtSpeed(motorPower);

  #ifdef DEBUG
    Serial.println("Starting to rotate to pole");
  #endif

  startTime = millis();

  while (searching) {
  
    readingValue = blipper->getUltrasonicRead();

    if (abs(readingValue - blipper->lastKnownPolePosition) < tolerance) {
      numGoodReadings++;
    } else {
      numGoodReadings = 0;
    }
    if (numGoodReadings >= windowLength) {
      searching = false;
      result = true;
    }

    if ((millis() - startTime) > (DEG_90_TURN_DELAY + 1000)) {
      searching = false;
      result = false;
    }
    
  }

  wheelDriver->driveStop();

  return result;
  
    

  
}

void roverBrain::driveByPole() {
  double returnValue;

  #ifdef LOOKRIGHT
    blipper->rotateServo(5);
  #endif
  #ifdef LOOKLEFT
    blipper->rotateServo(175);
  #endif
  delay(300);

  wheelDriver->driveForwards(90);
  returnValue = blipper->waitToSeePole();

  double delayAmountDouble = blipper->lastKnownPolePosition * POLEDRIVEDELAYSLOPE + POLEDRIVEDELAYB;
  int delayAmountInt = (int) delayAmountDouble;
  #ifdef DEBUG
    Serial.print("Delay: ");
    Serial.println(delayAmountInt);
  #endif
  delay(delayAmountInt);

  #ifdef DEBUG
    Serial.print("Pole Found: ");
    Serial.println(returnValue,10);
    Serial.println("SUCCESS - DRIVEBYPOLE");
  #endif

  blipper->rotateServo(90);
  wheelDriver->driveStop();

  #ifdef DEBUG
    Serial.println("Finished driving by pole");
  #endif
  
  delay(300);

  

//XXX Changed pole orientation
  /*
  #ifdef LOOKRIGHT
  wheelDriver->rotateDegrees(-90);
  #endif
  #ifdef LOOKLEFT
  wheelDriver->rotateDegrees(90);
  #endif
  delay(250);
  */
  
}

bool roverBrain::orientToPole() {
  int returnValue;
  
  blipper->rotateServo(90);
  delay(500);

  returnValue = blipper->findPolePosition(20);
  delay(100);
  
  #ifdef DEBUG
    Serial.print("Pole found at: ");
    Serial.println(returnValue);
  #endif

  

  if (returnValue != -1) {
    wheelDriver->rotateDegrees(returnValue - 90);
    delay(500);
  
    int returnValue = blipper->findPolePosition(20);
    
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
    blipper->findPolePosition(50);
  }
}

void roverBrain::redefinePoleDistance() {
  #ifdef DEBUG
    Serial.print("Redefining pole distance from: ");
    Serial.print(blipper->lastKnownPolePosition,10);
  #endif
  blipper->lastKnownPolePosition = blipper->getAccurateUltrasonicRead();
  blipper->lastReadingValue = blipper->lastKnownPolePosition;

  #ifdef DEBUG
    Serial.print("  to: ");
    Serial.println(blipper->lastKnownPolePosition,10);
  #endif
  
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
        Serial.print(blipper->lastReadingValue,10);
        Serial.print("  Current Reading: ");
        Serial.println(blipper->getUltrasonicRead(),10);
      #endif 
      
      delay(50);

      //bool poleOrientationResult = orientToPole(); XXXChanging Orientation
      bool poleOrientationResult = rotateUntilSeePole(20,90);

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

