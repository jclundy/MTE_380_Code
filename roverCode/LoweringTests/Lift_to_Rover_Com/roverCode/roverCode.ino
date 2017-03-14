#include <Servo.h>
#include "drivingBrain.h"

#define INPUT_PIN 4
#define OUTPUT_PIN 3
#define LEFT_MOTOR_PIN 10
#define RIGHT_MOTOR_PIN 11

int isHigh = false;
int pinValue = HIGH;

Servo servoL;
Servo servoR;
drivingBrain* wheelDriver;

void setup() {
  pinMode(INPUT_PIN, INPUT);
  pinMode(OUTPUT_PIN, OUTPUT);
  digitalWrite(OUTPUT_PIN, HIGH);
  
  //servoL.attach(LEFT_MOTOR_PIN);
  //servoR.attach(RIGHT_MOTOR_PIN);
  //wheelDriver = new drivingBrain(&servoL, &servoR);
}

void loop() {
  // wait until rover recieves signal from lift
//  while(pinValue == HIGH) {
//    pinValue = digitalRead(INPUT_PIN);
//    delay(10);
//  }
//  
pinValue = !digitalRead(INPUT_PIN);
//if(pinValue == LOW) {
//  digitalWrite(OUTPUT_PIN, HIGH);
//} else {
//  digitalWrite(OUTPUT_PIN, LOW);
//}
  digitalWrite(OUTPUT_PIN, pinValue);
  delay(10);
  
  // drive wheels forward
}
