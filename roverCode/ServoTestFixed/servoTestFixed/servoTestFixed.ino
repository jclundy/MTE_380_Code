
#include <Servo.h>
#include "blipperBrain.h"


#define LEFT_MOTOR_PIN 10
#define RIGHT_MOTOR_PIN 11
#define BLIPPER_SERVO_PIN 9

Servo servoL;
Servo servoR;
Servo servoBlipper; 
blipperBrain* blipper;




void blinkWait(unsigned int waitTime, unsigned int blinkTime) {

  int totalTime = 0;

  while (totalTime < waitTime) {
    digitalWrite(LED_BUILTIN,HIGH);
    delay(blinkTime/2);
    digitalWrite(LED_BUILTIN,LOW);
    delay(blinkTime/2);
    totalTime += blinkTime;
  }

  
}


void setup() {

  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
  servoL.attach(LEFT_MOTOR_PIN);
  servoR.attach(RIGHT_MOTOR_PIN);
  servoBlipper.attach(BLIPPER_SERVO_PIN); 

  Servo* servoSensor_p = (&servoBlipper);
  
  blipper = new blipperBrain(servoSensor_p);
  Serial.println("Initalized");

}


void getSerialInput() {

int incomingValue;

if (Serial.available() > 0) {
    incomingValue = Serial.parseInt();
    Serial.println(incomingValue);
    servoL.writeMicroseconds(incomingValue);
    servoR.writeMicroseconds(incomingValue);
  }

  blinkWait(200,100);
  
}

void loop() {


  Serial.println(blipper->getUltrasonicRead());

  


}
