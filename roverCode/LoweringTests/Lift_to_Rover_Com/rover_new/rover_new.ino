#include <Servo.h>
#include "drivingBrain.h"
#include "spool.h"

// pin definitions
#define INPUT_PIN 4
#define OUTPUT_PIN 3
#define LEFT_MOTOR_PIN 11
#define RIGHT_MOTOR_PIN 10
#define SPOOL_PIN 6

#define DRIVE_TIME_MS 3000
#define LOWER_TIME_MS 6000

int isHigh = false;
int pinValue = LOW;

Servo servoL;
Servo servoR;
Servo spoolMotor;
drivingBrain* wheelDriver;
spool* spooler;

void setup() {
  pinMode(INPUT_PIN, INPUT);
  pinMode(OUTPUT_PIN, OUTPUT);
  digitalWrite(OUTPUT_PIN, HIGH);
  
  spoolMotor.attach(SPOOL_PIN);
  servoL.attach(LEFT_MOTOR_PIN);
  servoR.attach(RIGHT_MOTOR_PIN);
  wheelDriver = new drivingBrain(&servoL, &servoR);
  spooler = new spool(&spoolMotor);
}

void loop() {
// wait until rover recieves HIGH signal from lift
  while(pinValue == LOW) {
    pinValue = digitalRead(INPUT_PIN);
    delay(10);
  }
  
  // wait until rover recieves LOW signal from lift
  while(pinValue == HIGH) {
    pinValue = digitalRead(INPUT_PIN);
    delay(10);
  }
  // drive wheels forward
  wheelDriver->driveForwards(50);
  spooler->unspool();
  delay(DRIVE_TIME_MS);
  wheelDriver->driveStop();
  delay(LOWER_TIME_MS);
  spooler->stopRotating();
}
