#include "roverBrain.h"


roverBrain::roverBrain(Servo* frontLeftServo, Servo* frontRightServo, Servo* backLeftServo, Servo* backRightServo, Servo* sensorServo) {

  blipper = new blipperBrain();
  wheelDriver = new drivingBrain(frontLeftServo, frontRightServo, backLeftServo, backRightServo);
  
}

roverBrain::~roverBrain() {
  delete blipper;
  delete wheelDriver;
}

bool roverBrain::driveToPole() {

  bool roverResult;
  int driveByPoleResult;
  int poleRotationToleranceSize = 15;
  
  driveByPoleResult = driveByPole();

  if (driveByPoleResult == 1) {
    roverResult = rotateUntilSeePole(poleRotationToleranceSize,-90);
  } else if (driveByPoleResult == 2) {
    roverResult = rotateUntilSeePole(poleRotationToleranceSize,90);
  }
  else {
    #ifdef DEBUG
      Serial.println("Succeeded- Found Pole at Front");
    #endif
    return true;
  }
  
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
      Serial.println("FAIL - DRIVETOPOLE");
    #endif
    return false;
  }
}

int roverBrain::driveByPole() {
  int blipperReturnValue;
  
  #ifdef DEBUG
    Serial.println("Starting Driving by pole");
  #endif

  wheelDriver->driveForwards(90);
  blipperReturnValue = blipper->waitToSeePole();

  double delayAmountDouble = blipper->lastKnownPolePosition * POLEDRIVEDELAYSLOPE + POLEDRIVEDELAYB;
  int delayAmountInt = (int) delayAmountDouble;
  #ifdef DEBUG
    Serial.print("Turn Delay: ");
    Serial.println(delayAmountInt);
  #endif
    
  delay(delayAmountInt);
  
  wheelDriver->driveStop();

  #ifdef DEBUG
    Serial.println("Finished driving by pole");
  #endif

  return blipperReturnValue;
 
}

bool roverBrain::rotateUntilSeePole(double tolerance, int rotateDirection) {

  double readingValue = 999;
  int windowLength = 8;
  int numGoodReadings = 0;

  int startReadingTime = 50;

  unsigned long startTime;

  bool searching = true;
  bool result;

  int motorPower;

  if (rotateDirection > 0) {
    motorPower = 30;
  } else {
    motorPower = -30;
  }

  #ifdef DEBUG
    Serial.println("Starting to rotate to pole");
  #endif

  wheelDriver->rotateAtSpeed(motorPower);

  

  startTime = millis();

  while (searching) {
  
    readingValue = blipper->getFrontUltrasonicRead();

    if (abs(readingValue - blipper->lastKnownPolePosition) < tolerance) {
      numGoodReadings++;
    } else {
      numGoodReadings = 0;
    }
    if (numGoodReadings >= windowLength) {

      wheelDriver->driveStop();
      delay(20);
      if (rotateDirection > 0) {
        blipper->lastKnownWallDistance = blipper->getRightUltrasonicRead();
        #ifdef DEBUG
          Serial.print("Wall on right at distance: ");
          Serial.println(blipper->lastKnownWallDistance,1);
        #endif
      } else {
        blipper->lastKnownWallDistance = blipper->getLeftUltrasonicRead();
        #ifdef DEBUG
          Serial.print("Wall on left at distance: ");
          Serial.println(blipper->lastKnownWallDistance,1);
        #endif
      }
      
      #ifdef DEBUG
        Serial.print(millis());
        Serial.print("-ROTATE_Found pole from position: ");
        Serial.print(blipper->lastKnownPolePosition,1);
        Serial.print(" with current reading: ");
        Serial.println(blipper->getFrontUltrasonicRead(),1);
      #endif
      searching = false;
      result = true;
    }

    if ((millis() - startTime) > (DEG_90_TURN_DELAY + 2000)) {

      #ifdef DEBUG
        Serial.println("FAIL - ROTATEUNTILPOLESEEN : for going too long overtime");
      #endif
      
      searching = false;
      result = false;
    }
    
  }

  wheelDriver->driveStop();

  return result;
}

bool roverBrain::driveToPoleHeadOn() {

  bool success;
  bool findingPole = true;

  int poleFindingReturnValue;

  #ifdef DEBUG
    Serial.print("Driving with wall on the: ");
    if (blipper->wallDirection == 1) {
      Serial.println("left");
    } else if (blipper->wallDirection == 2) {
      Serial.println("right");
    } else {
      Serial.println("Something went wrong!");
    }
  #endif

  while (findingPole) {
    wheelDriver->driveForwards(90);
    delay(10);

    poleFindingReturnValue = blipper->driveTowardsPole();
  
    wheelDriver->driveStop();
  
    if (poleFindingReturnValue == 0) {
      #ifdef DEBUG
        Serial.print(millis());
        Serial.print("-DRIVE_TO_lost pole from front sensor at a distance: ");
        Serial.print(blipper->lastKnownPolePosition,1);
        Serial.print(" current reading: ");
        Serial.println(blipper->getFrontUltrasonicRead(),1);
      #endif
      success = false;
      findingPole = false;
      //Based on distance to wall estimate turn direction
    } else if (poleFindingReturnValue > 0) {
      #ifdef DEBUG
        Serial.print(millis());
        Serial.print("-DRIVE_TO_Lost wall at distance: ");
        Serial.print(blipper->lastKnownPolePosition,10);
        Serial.print("  Current Reading: ");
        Serial.println(blipper->getFrontUltrasonicRead(),10);
      #endif 
      
      delay(50);

      bool poleOrientationResult; 

      if (poleFindingReturnValue == 1) {
        poleOrientationResult = rotateUntilSeePole(20,-90);
      } else {
        poleOrientationResult = rotateUntilSeePole(20,90);
      }

      if (!poleOrientationResult) {
        success = false;
        findingPole = false;
      }
    } else {
      #ifdef DEBUG
        Serial.println("Found Pole");
      #endif 
      success = true;
      findingPole = false;
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

void roverBrain::redefinePoleDistance() {
  #ifdef DEBUG
    Serial.print("Redefining pole distance from: ");
    Serial.print(blipper->lastKnownPolePosition,10);
  #endif
  blipper->lastKnownPolePosition = blipper->getFrontUltrasonicRead();
  blipper->lastFrontReadingValue = blipper->lastKnownPolePosition;

  #ifdef DEBUG
    Serial.print("  to: ");
    Serial.println(blipper->lastKnownPolePosition,10);
  #endif
  
}


