
#include <Servo.h>
#include "roverBrain.h"
#include "testingAlgs2.h"


#define LEFT_MOTOR_PIN 11
#define RIGHT_MOTOR_PIN 10
#define BLIPPER_SERVO_PIN 9

roverBrain* rover;


void setup() {
  
  Serial.begin(9600);

  Servo* servoL_p = new Servo();
  Servo* servoR_p = new Servo();
  Servo* servoSensor_p = new Servo();
  
  servoL_p->attach(LEFT_MOTOR_PIN);
  servoR_p->attach(RIGHT_MOTOR_PIN);
  servoSensor_p->attach(BLIPPER_SERVO_PIN); 
  
  rover = new roverBrain(servoL_p,servoR_p,servoSensor_p);
  Serial.println("Initalized");

}


void loop() {


  testingAlgorithms* mainTest = new testingAlgorithms();
  //mainTest->testDrivingTrim(wheelDriver);
  mainTest->findRotationValue(rover->wheelDriver);
  //mainTest->getBlipperDriveByArray(blipper, wheelDriver);
  //mainTest->getBlipperRotateArray(blipper, wheelDriver);
  //mainTest->testDriveByPole(blipper, wheelDriver);
  //mainTest->testDriveToPole(blipper, wheelDriver);
  //mainTest->testBlipperFindPolePosition(blipper, wheelDriver);
  //mainTest->testLocatePoleHeadOn(blipper, wheelDriver);

  
  //testingAlgorithms::waitForUltrasonicInputToStart(rover);
  //rover->driveToPole();

  
  

}
