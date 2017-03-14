#include "testingAlgs2.h"

testingAlgorithms::testingAlgorithms() {

  
}


testingAlgorithms::~testingAlgorithms() {

  
}

void testingAlgorithms::testPopulationArray(blipperBrain* blipper) {

  blipper->populatePositionArray();

  for (int i = 0; i < NUM_READINGS; i++) {
    Serial.println(blipper->posReadings[i]);
  }
  
}

void testingAlgorithms::testFilterArray(blipperBrain* blipper) {

  Serial.println("Starting test");
  testPopulationArray(blipper);

  Serial.println("Best guess value:");
  Serial.println(blipper->filterPositionArray());
  
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




