#include "testingAlgs2.h"

testingAlgorithms::testingAlgorithms() {

  
}


testingAlgorithms::~testingAlgorithms() {

  
}


void testingAlgorithms::testDrivingTrim(drivingBrain* wheelDriver) {

  
  int incomingInt;
  double incomingValue;

  if (Serial.available() > 0) {
      incomingInt = Serial.parseInt();
      incomingValue = incomingInt/1000.0;
      Serial.println(incomingValue,10000);
      wheelDriver->trimValue = incomingValue;
      wheelDriver->driveForwards(90);
      delay(3000);
      Serial.println("Stop");
      wheelDriver->driveStop();
    }
}

void testingAlgorithms::findRotationValue(drivingBrain* wheelDriver) {

  
  int incomingInt;

  if (Serial.available() > 0) {
      incomingInt = Serial.parseInt();
      wheelDriver->rotateAtSpeed(90);
      delay(incomingInt);
      wheelDriver->driveStop();
      delay(1000);
      wheelDriver->rotateAtSpeed(-90);
      delay(incomingInt);
      wheelDriver->driveStop();
    }
}

void testingAlgorithms::testRotationDegrees(drivingBrain* wheelDriver) {

  
  int incomingInt;

  if (Serial.available() > 0) {
      incomingInt = Serial.parseInt();
      wheelDriver->rotateDegrees(incomingInt);
      delay(1000);
      wheelDriver->rotateDegrees(-incomingInt);
    }
}

void testingAlgorithms::testDrivePower(drivingBrain* wheelDriver) {

  
  int incomingInt;

  if (Serial.available() > 0) {
      incomingInt = Serial.parseInt();
      wheelDriver->driveForwards(incomingInt);
      delay(6000);
      Serial.println("Stop");
      wheelDriver->driveStop();
    }
}

void testingAlgorithms::leftServoTestMicroseconds(drivingBrain* wheelDriver) {

int incomingValue;

if (Serial.available() > 0) {
    incomingValue = Serial.parseInt();
    Serial.println(incomingValue);
    wheelDriver->leftServo->writeMicroseconds(incomingValue);
  }
  
}

void testingAlgorithms::rightServoTestMicroseconds(drivingBrain* wheelDriver) {

int incomingValue;

if (Serial.available() > 0) {
    incomingValue = Serial.parseInt();
    Serial.println(incomingValue);
    wheelDriver->rightServo->writeMicroseconds(incomingValue);
  }
  
}

void testingAlgorithms::waitForInputToStart() {
  Serial.println("Type S to start to start driving by pole");
  while (Serial.available() <= 0);
  Serial.read();
}

void testingAlgorithms::testDriveByPole(blipperBrain* blipper, drivingBrain* wheelDriver) {

  double returnValue;

   Serial.println("Type S to start to start driving by pole");
   while (Serial.available() <= 0);
   Serial.read();
  
  Serial.println("Starting Test");
  
  blipper->rotateServo(175);
  
  delay(500);
  
  wheelDriver->driveForwards(90);
  
  returnValue = blipper->waitToSeePole();

  delay(1000);
  
  Serial.print("Pole Found: ");
  
  Serial.println(returnValue,10);
  
  wheelDriver->rotateDegrees(90);
  
  blipper->rotateServo(90);
  
  delay(500);
  
  Serial.print("Evaluated Pole Distance: ");
  
  double difference = blipper->getUltrasonicRead();
  
  Serial.println(difference, 10);

  Serial.print("Difference: ");

  difference = abs(difference - returnValue);

  Serial.println(difference,10);



    
}
 
  
  
void testingAlgorithms::getBlipperDriveByArray(blipperBrain* blipper, drivingBrain* wheelDriver) {

  int delayAmount;

  Serial.println("Type reading numbers to start");
  while (Serial.available() <= 0);
  delayAmount = Serial.parseInt();

  blipper->rotateServo(90);
  
  delay(500);
  
  wheelDriver->driveForwards(90);

  while(delayAmount > 0) {
    Serial.println(blipper->getUltrasonicRead(),10);
    delayAmount--;
  }

  wheelDriver->driveStop();

  
}

void testingAlgorithms::getBlipperRotateArray(blipperBrain* blipper, drivingBrain* wheelDriver) {

  int delayAmount;

  Serial.println("Type reading numbers to start");
  while (Serial.available() <= 0);
  delayAmount = Serial.parseInt();

  blipper->rotateServo(90);

  delay(500);
  
  for (int i = 0; i < delayAmount; i++) {
    blipper->rotateServo(130-i);
    Serial.println(blipper->getUltrasonicRead(),10);
    delay(20);
  }

  blipper->rotateServo(90);

  
}

void testingAlgorithms::testDriveToPole(blipperBrain* blipper, drivingBrain* wheelDriver) {

  bool returnValue;

  unsigned int inputValue;
  double inputDistance;

 Serial.print("Initial Distance: ");
 Serial.println(blipper->getUltrasonicRead(),10);
 
 Serial.println("Type in pole distance to start driving * 100");
 while (Serial.available() <= 0);
 inputValue = Serial.parseInt();
 inputDistance = inputValue / 100.0;

 Serial.println(inputDistance,10);
  
  Serial.println("Starting Test");
  
  blipper->rotateServo(90);
  blipper->lastReadingValue = inputDistance;
  blipper->lastKnownPolePosition = inputDistance;
  
  delay(500);
  
  wheelDriver->driveForwards(90);
  delay(10);

  returnValue = blipper->driveTowardsPole();

  wheelDriver->driveStop();

  if (returnValue) {
    Serial.print("Found pole at distance: ");
    Serial.println(blipper->lastReadingValue,10);
  } else {
    Serial.print("Lost Pole at distance: ");
    Serial.println(blipper->lastReadingValue,10);
    delay(100);
    
  } 
}



void testingAlgorithms::testBlipperFindPolePosition(blipperBrain* blipper, drivingBrain* wheelDriver) {

  int returnValue;

  unsigned int inputValue;
  double inputDistance;

   Serial.print("Initial Distance: ");
   Serial.println(blipper->getUltrasonicRead(),10);
   
   Serial.println("Type in pole distance to search * 100");
   while (Serial.available() <= 0);
   inputValue = Serial.parseInt();
   inputDistance = inputValue / 100.0;

   Serial.println(inputDistance,10);
  
  Serial.println("Starting Test");

  blipper->rotateServo(90);
  blipper->lastReadingValue = inputDistance;
  blipper->lastKnownPolePosition = inputDistance;
  
  delay(500);

  returnValue = blipper->findPolePosition();

  Serial.print("Pole found at: ");
  Serial.println(returnValue);

  blipper->rotateServo(90);
  delay(100);

  if (returnValue != -1) {
    wheelDriver->rotateDegrees(returnValue - 90);
  
    delay(1000);
  
    returnValue = blipper->findPolePosition();
  
    Serial.print("New Pole found at: ");
    Serial.println(returnValue);
  }
  blipper->rotateServo(90);
}

void testingAlgorithms::testLocatePoleHeadOn(blipperBrain* blipper, drivingBrain* wheelDriver) {

  bool success;
  bool findingPole = true;

  int poleFindingReturnValue;

  unsigned int inputValue;
  double inputDistance;

  Serial.print("Initial Distance: ");
  Serial.println(blipper->getUltrasonicRead(),10);
   
  Serial.println("Type in pole distance to start locating * 100");
  while (Serial.available() <= 0);
  inputValue = Serial.parseInt();
  inputDistance = inputValue / 100.0;

  Serial.println(inputDistance,10);
  
  Serial.println("Starting Test");

  blipper->rotateServo(90);
  blipper->lastReadingValue = inputDistance;
  blipper->lastKnownPolePosition = inputDistance;
  
  delay(500);

  while (findingPole) {
    wheelDriver->driveForwards(90);
    delay(10);

    poleFindingReturnValue = blipper->driveTowardsPole();
  
    wheelDriver->driveStop();
  
    if (poleFindingReturnValue) {
      Serial.print("Found pole at distance: ");
      Serial.println(blipper->lastReadingValue,10);
      success = true;
      findingPole = false;
    } else {
      Serial.print("Lost Pole at distance: ");
      Serial.println(blipper->lastReadingValue,10);
      delay(100);
  
      poleFindingReturnValue = blipper->findPolePosition();

      Serial.print("New Pole position: ");
      Serial.println(poleFindingReturnValue);
  
      if (poleFindingReturnValue == -1) {
        success = false;
        findingPole = false;
      } else {
        blipper->rotateServo(90);
        wheelDriver->rotateDegrees(poleFindingReturnValue - 90);
        delay(100);
      }
    }
  }

  if (success) {
    Serial.println("SUCCESS");
  } else {
    Serial.print("FAILURE: last known pole position: ");
    Serial.println(blipper->lastReadingValue,10);
  }
}






