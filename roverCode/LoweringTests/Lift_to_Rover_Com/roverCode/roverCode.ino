#include <Servo.h>
#define INPUT_PIN A0
#define OUTPUT_PIN A1

int isHigh = false;
int pinValue = HIGH;

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
