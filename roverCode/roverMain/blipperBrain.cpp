#include "blipperBrain.h"



blipperBrain::blipperBrain()
{

  pinMode(FRONT_TRIG_PIN, OUTPUT);
  pinMode(FRONT_ECHO_PIN, INPUT);
  pinMode(LEFT_TRIG_PIN, OUTPUT);
  pinMode(LEFT_ECHO_PIN, INPUT);
  pinMode(RIGHT_TRIG_PIN, OUTPUT);
  pinMode(RIGHT_ECHO_PIN, INPUT);

  lastFrontReadingValue = 999;
  lastLeftReadingValue = 999;
  lastRightReadingValue = 999;

  lastKnownPolePosition = 999;
  lastKnownWallDistance = 999;
}

blipperBrain::blipperBrain(int inputWallDirection)
{

  pinMode(FRONT_TRIG_PIN, OUTPUT);
  pinMode(FRONT_ECHO_PIN, INPUT);
  pinMode(LEFT_TRIG_PIN, OUTPUT);
  pinMode(LEFT_ECHO_PIN, INPUT);
  pinMode(RIGHT_TRIG_PIN, OUTPUT);
  pinMode(RIGHT_ECHO_PIN, INPUT);

  lastFrontReadingValue = 999;
  lastLeftReadingValue = 999;
  lastRightReadingValue = 999;

  lastKnownPolePosition = 999;
  lastKnownWallDistance = 999;

  setWallSide(inputWallDirection);


}

blipperBrain::~blipperBrain()
{
}

int blipperBrain::waitToSeePole() {
  
  double tolerance = 5;
  int windowLength = 10;
  double leftCeilingValue;
  double rightCeilingValue;
  int numLeftGoodReadings = 0;
  int numRightGoodReadings = 0;
  int result = 0;

  leftCeilingValue = getLeftUltrasonicRead() - 50;
  rightCeilingValue = getRightUltrasonicRead() - 100;

  if (rightCeilingValue < 80) {
    rightCeilingValue = 80;
  }

  #ifdef DEBUG
    Serial.print("Left wall distance: ");
    Serial.print(leftCeilingValue, 1);
    Serial.print(" Right wall distance: ");
    Serial.println(rightCeilingValue, 1);
  #endif

  bool searching = true;

  while (searching) {
    delay(20);
    getAllUltrasonicRead();
    Serial.println(currentRightReadingValue,1);

    if (currentLeftReadingValue < leftCeilingValue) {
      if (abs(currentLeftReadingValue - lastLeftReadingValue) < tolerance) {
        numLeftGoodReadings++;
      } else {
        numLeftGoodReadings = 0;
      }
      if (numLeftGoodReadings >= windowLength) {
        #ifdef DEBUG
          Serial.println("Found pole on left");
        #endif
        lastKnownPolePosition = currentLeftReadingValue;
        result = 1;
        searching = false;
      }
    }

    if (currentRightReadingValue < rightCeilingValue) {
      if (abs(currentRightReadingValue - lastRightReadingValue) < tolerance) {
        numRightGoodReadings++;
      } else {
        numRightGoodReadings = 0;
      }
      if (numRightGoodReadings >= windowLength) {
        #ifdef DEBUG
          Serial.println("Found pole on right");
        #endif
        lastKnownPolePosition = currentRightReadingValue;
        result = 2;
        searching = false;
      }
    }

    if (currentFrontReadingValue < 5) {
      #ifdef DEBUG
        Serial.println("Hit wall on front");
      #endif
      lastKnownPolePosition = currentFrontReadingValue;
      result = 0;
      searching = false;
    }

    lastLeftReadingValue = currentLeftReadingValue;
    lastRightReadingValue = currentRightReadingValue;

  }

  
  wallDirection = result;
  return result;

}

int blipperBrain::waitToSeePoleDirection() {
  
  double tolerance = 5;
  int windowLength = 6;
  double sideCeilingValue;
  int numSideGoodReadings = 0;
  int result = 0;
  double currentSideReadingValue = 999;
  double lastSideReadingValue = 999;


  getSideUltrasonicRead();
  getSideUltrasonicRead();
  getSideUltrasonicRead();
  delay(25);
  sideCeilingValue = getSideUltrasonicRead() - 40;

  #ifdef DEBUG
    Serial.print("Side wall ceiling value initial: ");
    Serial.println(sideCeilingValue+40, 1);
  #endif
  
  if (sideCeilingValue < 90) {
    sideCeilingValue = 90;
  }

  #ifdef DEBUG
    Serial.print("Side wall ceiling value: ");
    Serial.println(sideCeilingValue, 1);
  #endif

  bool searching = true;

  while (searching) {

    delay(25);
    currentSideReadingValue = getUltrasonicRead(side_trig_pin, side_echo_pin);
    currentFrontReadingValue = getUltrasonicRead(FRONT_TRIG_PIN,FRONT_ECHO_PIN);
    Serial.println(currentSideReadingValue,1);

    if (currentSideReadingValue < sideCeilingValue) {
      if (abs(currentSideReadingValue - lastSideReadingValue) < tolerance) {
        numSideGoodReadings++;
      } else {
        numSideGoodReadings = 0;
      }
      if (numSideGoodReadings >= windowLength) {
        #ifdef DEBUG
          Serial.println("Found pole on side");
        #endif
        lastKnownPolePosition = currentSideReadingValue;
        result = wallDirection;
        searching = false;
      }
    }
    
    if (currentFrontReadingValue < 5) {
      #ifdef DEBUG
        Serial.println("Hit wall on front");
      #endif
      lastKnownPolePosition = currentFrontReadingValue;
      result = 0;
      searching = false;
    }

    lastSideReadingValue = currentSideReadingValue;

  }

  return result;

}



double blipperBrain::getUltrasonicRead(int TRIG_PIN, int ECHO_PIN) {

  unsigned long t1;
  unsigned long t2;
  unsigned long pulseTimer;
  unsigned long pulse_width;
  double cm;

  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  pulseTimer = 0;

  while ( digitalRead(ECHO_PIN) == 0 && pulseTimer < 50000 ) {
    pulseTimer++;
  }

  if (pulseTimer < 50000) {
    t1 = micros();
    while ( digitalRead(ECHO_PIN) == 1);
    t2 = micros();
    pulse_width = t2 - t1;
    cm = pulse_width / 58.0;
  } else {
    cm = 999;
  }

  if (cm < 0.01) {
    cm = 999;
  }
  return cm;
}

int blipperBrain::driveTowardsPole() {

  double frontReadingValue;
  double sideReadingValue;
  double lastSideReadingValue = 999;
  double poleTolerance = 10;
  double wallTolerance = 10;
  int windowLength = 3;
  int closeWindowLength = 3;
  int numFrontBadReadings = 0;
  int numSideBadReadings = 0;
  int numCloseReadings = 0;
  int sideTrigPin;
  int sideEchoPin;

  int returnResult = 0;

  bool searching = true;

  if (wallDirection == 1) {
    sideTrigPin = LEFT_TRIG_PIN;
    sideEchoPin = LEFT_ECHO_PIN;
  } else {
    sideTrigPin = RIGHT_TRIG_PIN;
    sideEchoPin = RIGHT_ECHO_PIN;
  }

  frontReadingValue = lastKnownPolePosition;

  while (searching) {
    frontReadingValue = getFrontUltrasonicRead();
    sideReadingValue = getUltrasonicRead(sideTrigPin,sideEchoPin);
    
    if (abs(frontReadingValue - lastKnownPolePosition) > poleTolerance) {
      if (abs(frontReadingValue - lastFrontReadingValue) <= poleTolerance) {
        numFrontBadReadings++;
      }
    } else {
      numFrontBadReadings = 0;
      lastKnownPolePosition = frontReadingValue;
    }

    if (abs(sideReadingValue - lastKnownWallDistance) > wallTolerance) {
      if (abs(sideReadingValue - lastSideReadingValue) <= wallTolerance) {
        numSideBadReadings++;
      }
    } else {
      numSideBadReadings = 0;
    }

    if (numFrontBadReadings >= windowLength) {
      searching = false;
    }
    
    if (numSideBadReadings >= windowLength) {
      if (sideReadingValue > lastKnownWallDistance) {
        if (wallDirection == 1) {
          returnResult = 1;
        } else {
          returnResult = 2;
        }
      } else {
        if (wallDirection == 1) {
          returnResult = 2;
        } else {
          returnResult = 1;
        }
      }
    }

    if (frontReadingValue < 7) {
      numCloseReadings++;
    }

    if (numCloseReadings >= closeWindowLength) {
      returnResult = -1;
      searching = false;
    }

    lastFrontReadingValue = frontReadingValue;
    lastSideReadingValue = sideReadingValue;
  }

  return returnResult;
}

void blipperBrain::setWallSide(int inWallSide) { 
    #ifdef DEBUG
      Serial.print("Setting wall to: ");
      if (inWallSide == 1) {
        Serial.println("left");
      } else {
        Serial.println("right");
      }
  
    #endif
    
    wallDirection = inWallSide;
    if (inWallSide == 1) {
      side_trig_pin = LEFT_TRIG_PIN;
      side_echo_pin = LEFT_ECHO_PIN;
    } else {
      side_trig_pin = RIGHT_TRIG_PIN;
      side_echo_pin = RIGHT_ECHO_PIN;
    }
  }
