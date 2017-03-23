#include "roverBrain.h"


roverBrain::roverBrain(Servo* frontLeftServo, Servo* frontRightServo, Servo* backLeftServo, Servo* backRightServo) {

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
    roverResult = rotateUntilSeePole(poleRotationToleranceSize,-90,DEG_90_TURN_DELAY + 2000,true);
    getInitialWallDistance(-90);
  } else if (driveByPoleResult == 2) {
    roverResult = rotateUntilSeePole(poleRotationToleranceSize,90,DEG_90_TURN_DELAY + 2000,true);
    getInitialWallDistance(90);
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
  blipperReturnValue = blipper->waitToSeePoleDirection();

  if (blipperReturnValue != 0) {
    double delayAmountDouble = blipper->lastKnownPolePosition * POLEDRIVEDELAYSLOPE + POLEDRIVEDELAYB;
    int delayAmountInt = (int) delayAmountDouble;
    #ifdef DEBUG
      Serial.print("Turn Delay: ");
      Serial.println(delayAmountInt);
    #endif
      
    delay(delayAmountInt);
  }

  
  
  wheelDriver->driveStop();

  #ifdef DEBUG
    Serial.println("Finished driving by pole");
  #endif

  return blipperReturnValue;
 
}

void roverBrain::getInitialWallDistance(int rotateDirection) {
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
}

bool roverBrain::rotateUntilSeePole(double tolerance, int rotateDirection, int timeOutLength, bool is90DegTurn) {

  double readingValue = 999;
  int windowLength = 4;
  int numGoodReadings = 0;

  int startReadingTime = 50;

  int closeReadingDistance = 25;

  unsigned long startTime;
  unsigned long currentTime;

  bool searching = true;
  bool result;

  int motorPower;

  if (rotateDirection > 0) {
    motorPower = 30;
  } else {
    motorPower = -30;
  }

  #ifdef DEBUG
    if (readingValue < (blipper->lastKnownPolePosition + tolerance)) {
      Serial.print("Starting to rotate to pole CLOSE @D:");
    } else {
      Serial.print("Starting to rotate to pole @D:");
    }
    
    Serial.print(blipper->lastKnownPolePosition,1);
    Serial.print(" @TOL:");
    Serial.print(tolerance,1);
    Serial.print(" @TIM:");
    Serial.println(timeOutLength);
  #endif

  wheelDriver->rotateAtSpeed(motorPower);

  if (is90DegTurn) {
    #ifdef DEBUG
      Serial.println("rotating with a delay");
    #endif
    delay(DEG_90_TURN_DELAY);
  }

  startTime = millis();

  while (searching) {

    currentTime = millis();
    readingValue = blipper->getFrontUltrasonicRead();

    if (readingValue < (blipper->lastKnownPolePosition + tolerance)) {
        if (readingValue < (blipper->lastKnownPolePosition + tolerance)) {
        numGoodReadings++;
      } else {
        numGoodReadings = 0;
      }
    } else {
      if (abs(readingValue - blipper->lastKnownPolePosition) < tolerance) {
        numGoodReadings++;
      } else {
        numGoodReadings = 0;
      }
    }
    
    

    
    if (numGoodReadings >= windowLength) {

      delay(100);
      wheelDriver->driveStop();
      

      double readDistanceToPole = blipper->getFrontUltrasonicRead();
      
      #ifdef DEBUG
        Serial.print(millis());
        Serial.print("-ROTATE_Found pole from position: ");
        Serial.print(blipper->lastKnownPolePosition,1);
        Serial.print(" with current reading: ");
        Serial.println(readDistanceToPole,1);
      #endif

      if (abs(readDistanceToPole - blipper->lastKnownPolePosition) < 15) {
        blipper->lastKnownPolePosition = readDistanceToPole;
      }
      
      
      searching = false;
      result = true;
    }

    if ((currentTime - startTime) > (timeOutLength)) {

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
  int lastFindLostPoleDirection = 2;

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

      if (!findLostPole(lastFindLostPoleDirection)) {
        success = false;
        findingPole = false;
      } else {
        if (lastFindLostPoleDirection == 1) {
          lastFindLostPoleDirection = 2;
        } else {
          lastFindLostPoleDirection = 1;
        }
      }
      //Based on distance to wall estimate turn direction
    } else if (poleFindingReturnValue > 0) {
      #ifdef DEBUG
        Serial.print(millis());
        Serial.print("-DRIVE_TO_Lost wall at distance: ");
        Serial.print(blipper->lastKnownWallDistance,10);
        Serial.print("  Current Reading: ");
        Serial.println(blipper->getSideUltrasonicRead(),10);
      #endif 
      
      delay(50);

      bool poleOrientationResult; 

      poleOrientationResult = findLostPole(poleFindingReturnValue);

      if (!poleOrientationResult) {
        success = false;
        findingPole = false;
      } else {
        #ifdef DEBUG
          Serial.println("Refound pole, trying driving again");
        #endif
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

bool roverBrain::findLostPole(int initialDirection) {

  int timeOutDelay = 300;
  int directionModifier;
  int toleranceVal = 15;

  if (initialDirection == 1) {
    directionModifier = -1;
    #ifdef DEBUG
      Serial.println("Lost pole starting left");
    #endif
  } else {
    directionModifier = 1;
    #ifdef DEBUG
      Serial.println("Lost pole starting right");
    #endif
  }

  while (!rotateUntilSeePole(toleranceVal,directionModifier,timeOutDelay,false)) {
    directionModifier = directionModifier * -1;
    timeOutDelay = timeOutDelay + 300;
    toleranceVal += 5;
    
    if (directionModifier == 1) {
      timeOutDelay -= 100;
    } else {
      timeOutDelay += 100;
    }
    
    if (toleranceVal > 70) {
      return false;
    }

    
    delay(100);
  }
  #ifdef DEBUG
    Serial.println("Located Lost Pole");
  #endif
  return true;
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


