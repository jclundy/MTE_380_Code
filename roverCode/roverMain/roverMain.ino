
#include <Servo.h>
#include "roverBrain.h"
#include "testingAlgs2.h"

#define FRONT_LEFT_MOTOR_PIN 11
#define FRONT_RIGHT_MOTOR_PIN 10
#define BACK_LEFT_MOTOR_PIN 3
#define BACK_RIGHT_MOTOR_PIN 5
#define BLIPPER_SERVO_PIN 9

roverBrain* rover;


void setup() {

  Serial.begin(9600);

  //Servo pointers
  Servo* servoFL_p = new Servo();
  Servo* servoFR_p = new Servo();
  Servo* servoBL_p = new Servo();
  Servo* servoBR_p = new Servo();
  Servo* servoSensor_p = new Servo();

  servoFL_p->attach(FRONT_LEFT_MOTOR_PIN);
  servoFR_p->attach(FRONT_RIGHT_MOTOR_PIN);
  servoBL_p->attach(BACK_LEFT_MOTOR_PIN);
  servoBR_p->attach(BACK_RIGHT_MOTOR_PIN);

  servoSensor_p->attach(BLIPPER_SERVO_PIN);

  rover = new roverBrain(servoFL_p, servoFR_p, servoBL_p, servoBR_p, servoSensor_p);

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
  testingAlgorithms::waitForInputToStart();
  rover->driveToPole();
  //rover->driveByPole();
  //testingAlgorithms::rotateUntilSeePole(rover);


  /*
  for (int j = 0; j < 50; j += 5) {
    Serial.println(j);
    for (int i = 0; i < 50; i++) {
      Serial.println(rover->blipper->getUltrasonicRead(),1);
      delay(j);
    }
  }

  while(true);
  */



}
