#include "testingAlgs2.h"

testingAlgorithms::testingAlgorithms() {

  
}


testingAlgorithms::~testingAlgorithms() {

  
}


void testingAlgorithms::testDrivingTrim(drivingBrain* wheelDriver) {

  
  int incomingInt;
  double incomingValue;
  Serial.println("Input driving trim, value from 0 to 1000, 1000 = 1.0");

  while (Serial.available() <= 0);

  if (Serial.available() > 0) {
      incomingInt = Serial.parseInt();
      incomingValue = incomingInt/1000.0;
      Serial.println(incomingValue,10000);
      wheelDriver->trimValue = incomingValue;
      wheelDriver->driveForwards(90);
      delay(6000);
      Serial.println("Stop");
      wheelDriver->driveStop();
    }
}

void testingAlgorithms::findRotationValue(drivingBrain* wheelDriver) {

  
  int incomingInt;

  if (Serial.available() > 0) {
      incomingInt = Serial.parseInt();
      wheelDriver->rotateAtSpeed(30);
      delay(incomingInt);
      wheelDriver->driveStop();
      delay(1000);
      wheelDriver->rotateAtSpeed(-30);
      delay(incomingInt);
      wheelDriver->driveStop();
    }
}

void testingAlgorithms::testRotationDegrees(drivingBrain* wheelDriver) {

  
  int incomingInt;

  if (Serial.available() > 0) {
      incomingInt = Serial.parseInt();
      wheelDriver->rotateAtSpeed(incomingInt);
      delay(1000);
      wheelDriver->driveStop();
    }
}

void testingAlgorithms::testDrivePower(drivingBrain* wheelDriver) {

  
  int incomingInt;

  if (Serial.available() > 0) {
      incomingInt = Serial.parseInt();
      wheelDriver->driveForwards(incomingInt);
      delay(3000);
      Serial.println("Stop");
      wheelDriver->driveStop();
    }
}

void testingAlgorithms::frontLeftServoTestMicroseconds(drivingBrain* wheelDriver) {

int incomingValue;

if (Serial.available() > 0) {
    incomingValue = Serial.parseInt();
    Serial.println(incomingValue);
    wheelDriver->frontLeftServo->writeMicroseconds(incomingValue);
  }
  
}

void testingAlgorithms::frontRightServoTestMicroseconds(drivingBrain* wheelDriver) {

int incomingValue;

if (Serial.available() > 0) {
    incomingValue = Serial.parseInt();
    Serial.println(incomingValue);
    wheelDriver->frontRightServo->writeMicroseconds(incomingValue);
  }
}

void testingAlgorithms::backLeftServoTestMicroseconds(drivingBrain* wheelDriver) {

int incomingValue;

if (Serial.available() > 0) {
    incomingValue = Serial.parseInt();
    Serial.println(incomingValue);
    wheelDriver->backLeftServo->writeMicroseconds(incomingValue);
  }
  
}

void testingAlgorithms::backRightServoTestMicroseconds(drivingBrain* wheelDriver) {

int incomingValue;

if (Serial.available() > 0) {
    incomingValue = Serial.parseInt();
    Serial.println(incomingValue);
    wheelDriver->backRightServo->writeMicroseconds(incomingValue);
  }
}



void testingAlgorithms::waitForInputToStart() {
  Serial.println("Type S to start to start driving by pole");
  while (Serial.available() <= 0);
  Serial.read();
}

void testingAlgorithms::waitForUltrasonicInputToStart(roverBrain* rover) {
  while (rover->blipper->getFrontUltrasonicRead() > 10);
}

void testingAlgorithms::testDriveByPole(blipperBrain* blipper, drivingBrain* wheelDriver) {

  double returnValue;

   Serial.println("Type S to start to start driving by pole");
   while (Serial.available() <= 0);
   Serial.read();
  
  Serial.println("Starting Test");
  
  
  delay(500);
  
  wheelDriver->driveForwards(90);
  
  returnValue = blipper->waitToSeePole();

  delay(1000);
  
  Serial.print("Pole Found: ");
  
  Serial.println(returnValue,10);
  
  wheelDriver->rotateDegrees(90);
  
  
  delay(500);
  
  Serial.print("Evaluated Pole Distance: ");
  
  double difference = blipper->getFrontUltrasonicRead();
  
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


  
  delay(500);
  
  wheelDriver->driveForwards(90);

  while(delayAmount > 0) {
    Serial.println(blipper->getFrontUltrasonicRead(),1);
    delayAmount--;
  }

  wheelDriver->driveStop();

  
}

void testingAlgorithms::getBlipperRotateArray(blipperBrain* blipper, drivingBrain* wheelDriver) {

  int delayAmount;

  Serial.println("Type reading numbers to start");
  while (Serial.available() <= 0);
  delayAmount = Serial.parseInt();



  delay(500);
  
  for (int i = 0; i < delayAmount; i++) {
    Serial.println(blipper->getFrontUltrasonicRead(),1);
    delay(40);
  }



  
}

void testingAlgorithms::testDriveToPole(blipperBrain* blipper, drivingBrain* wheelDriver) {

  bool returnValue;

  unsigned int inputValue;
  double inputDistance;

 Serial.print("Initial Distance: ");
 Serial.println(blipper->getFrontUltrasonicRead(),10);
 
 Serial.println("Type in pole distance to start driving * 100");
 while (Serial.available() <= 0);
 inputValue = Serial.parseInt();
 inputDistance = inputValue / 100.0;

 Serial.println(inputDistance,10);
  
  Serial.println("Starting Test");
  

  blipper->lastFrontReadingValue = inputDistance;
  blipper->lastKnownPolePosition = inputDistance;
  
  delay(500);
  
  wheelDriver->driveForwards(90);
  delay(10);

  returnValue = blipper->driveTowardsPole();

  wheelDriver->driveStop();

  if (returnValue) {
    Serial.print("Found pole at distance: ");
    Serial.println(blipper->lastFrontReadingValue,10);
  } else {
    Serial.print("Lost Pole at distance: ");
    Serial.println(blipper->lastFrontReadingValue,10);
    delay(100);
    
  } 
}



void testingAlgorithms::testBlipperFindPolePosition(roverBrain* rover) {

  int returnValue;

  unsigned int inputValue;
  double inputDistance;

   Serial.print("Initial Distance: ");
   Serial.println(rover->blipper->getFrontUltrasonicRead(),10);
   
   Serial.println("Type in pole distance to search * 100");
   while (Serial.available() <= 0);
   inputValue = Serial.parseInt();
   inputDistance = inputValue / 100.0;

   Serial.println(inputDistance,10);
  
  Serial.println("Starting Test");


  rover->blipper->lastFrontReadingValue = inputDistance;
  rover->blipper->lastKnownPolePosition = inputDistance;
  
}

void testingAlgorithms::testLocatePoleHeadOn(roverBrain* rover) {

  bool success;
  bool findingPole = true;

  int poleFindingReturnValue;

  unsigned int inputValue;
  double inputDistance;

  Serial.print("Initial Distance: ");
  Serial.println(rover->blipper->getFrontUltrasonicRead(),10);
   
  Serial.println("Type in pole distance to start locating * 100");
  while (Serial.available() <= 0);
  inputValue = Serial.parseInt();
  inputDistance = inputValue / 100.0;

  Serial.println(inputDistance,10);
  
  Serial.println("Starting Test");

  rover->blipper->lastFrontReadingValue = inputDistance;
  rover->blipper->lastKnownPolePosition = inputDistance;
  
  delay(500);

  rover->driveToPoleHeadOn();
  
}

void testingAlgorithms::rotateUntilSeePole(roverBrain* rover) {

  bool success;

  int poleFindingReturnValue;

  unsigned int inputValue;
  double inputDistance;

  Serial.print("Initial Distance: ");
  Serial.println(rover->blipper->getFrontUltrasonicRead(),10);
   
  Serial.println("Type in pole distance to start rotating * 100");
  while (Serial.available() <= 0);
  inputValue = Serial.parseInt();
  inputDistance = inputValue / 100.0;

  Serial.println(inputDistance,10);

  rover->blipper->lastFrontReadingValue = inputDistance;
  rover->blipper->lastKnownPolePosition = inputDistance;
  
  delay(500);
  
  Serial.println("Starting Test");
  
  success = rover->rotateUntilSeePole(20,90,2000,true);

  if (success) {
    Serial.println("Success!");
  } else {
    Serial.println("Fail!");
    
  }
  
}





