
#include <Servo.h>
#include "roverBrain.h"
#include "testingAlgs2.h"

#define FRONT_LEFT_MOTOR_PIN 11
#define FRONT_RIGHT_MOTOR_PIN 10
#define BACK_LEFT_MOTOR_PIN 3
#define BACK_RIGHT_MOTOR_PIN 9
#define WALL_DIRECTION_PIN A0

roverBrain* rover;


void setup() {

  Serial.begin(9600);

  //Servo pointers
  Servo* servoFL_p = new Servo();
  Servo* servoFR_p = new Servo();
  Servo* servoBL_p = new Servo();
  Servo* servoBR_p = new Servo();

  pinMode(FRONT_LEFT_MOTOR_PIN,OUTPUT);
  pinMode(FRONT_RIGHT_MOTOR_PIN,OUTPUT);
  pinMode(BACK_LEFT_MOTOR_PIN,OUTPUT);
  pinMode(BACK_RIGHT_MOTOR_PIN,OUTPUT);

  servoFL_p->attach(FRONT_LEFT_MOTOR_PIN);
  servoFR_p->attach(FRONT_RIGHT_MOTOR_PIN);
  servoBL_p->attach(BACK_LEFT_MOTOR_PIN);
  servoBR_p->attach(BACK_RIGHT_MOTOR_PIN);

  rover = new roverBrain(servoFL_p, servoFR_p, servoBL_p, servoBR_p);

  //Set wall direction
  pinMode(WALL_DIRECTION_PIN,INPUT);
  int wallDirectionReadValue = digitalRead(WALL_DIRECTION_PIN);
  if (wallDirectionReadValue == HIGH) {
    rover->blipper->setWallSide(1);
  } else {
    rover->blipper->setWallSide(2);
  }

  #ifdef DEBUG
    Serial.println("Initalized");
  #endif

}


void loop() {


  testingAlgorithms* mainTest = new testingAlgorithms();
  //mainTest->frontLeftServoTestMicroseconds(rover->wheelDriver);
  //mainTest->testDrivingTrim(rover->wheelDriver);
  //mainTest->testDrivePower(rover->wheelDriver);
  //mainTest->testRotationDegrees(rover->wheelDriver);
  //mainTest->getBlipperDriveByArray(rover->blipper, rover->wheelDriver);
  //mainTest->getBlipperRotateArray(rover->blipper, rover->wheelDriver);
  //mainTest->testDriveByPole(blipper, wheelDriver);
  //mainTest->testDriveToPole(blipper, wheelDriver);
  //mainTest->testBlipperFindPolePosition(rover);
  //mainTest->testLocatePoleHeadOn(rover);


  //testingAlgorithms::waitForUltrasonicInputToStart(rover);
  Serial.println(rover->blipper->getFrontUltrasonicRead(),1);
  testingAlgorithms::waitForInputToStart();
  //rover->driveToPole();
  //rover->blipper->setWallSide(1);
  
  rover->blipper->lastKnownPolePosition = 67;
  rover->blipper->lastKnownWallDistance = 100;
  //rover->rotateUntilSeePole(15,-90,2000);
  rover->driveToPoleHeadOn();

  


}
