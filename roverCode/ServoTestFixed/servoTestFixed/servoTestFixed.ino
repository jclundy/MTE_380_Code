
#include <Servo.h>
#include "blipperBrain.h"
#include "testingAlgs2.h"
#include "drivingBrain.h"


#define LEFT_MOTOR_PIN 11
#define RIGHT_MOTOR_PIN 10
#define BLIPPER_SERVO_PIN 9


blipperBrain* blipper;
drivingBrain* wheelDriver;



void setup() {
  
  Serial.begin(9600);

  Servo* servoL_p = new Servo();
  Servo* servoR_p = new Servo();
  Servo* servoSensor_p = new Servo();
  
  servoL_p->attach(LEFT_MOTOR_PIN);
  servoR_p->attach(RIGHT_MOTOR_PIN);
  servoSensor_p->attach(BLIPPER_SERVO_PIN); 
  
  blipper = new blipperBrain(servoSensor_p);
  wheelDriver = new drivingBrain(servoL_p, servoR_p);
  Serial.println("Initalized");

}


void loop() {


  testingAlgorithms* mainTest = new testingAlgorithms();
  mainTest->rightServoTestMicroseconds(wheelDriver);

}
