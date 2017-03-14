#include "Servo.h"

Servo mainServo;

int buttonPin = 4;
int LEDPin = 13;
int servoPin = 11;

bool outputMode = false;

void setup() {

  mainServo.attach(servoPin);
  
  pinMode(buttonPin,INPUT);
  pinMode(LEDPin,OUTPUT);
  digitalWrite(LEDPin,LOW);
}

void loop() {
  int buttonState = digitalRead(buttonPin);

  if (buttonState == HIGH) {

    if (outputMode) {
      outputMode = false;  
      digitalWrite(LEDPin,LOW);
      mainServo.write(0);
    } else {
      outputMode = true;
      digitalWrite(LEDPin,HIGH);
      mainServo.write(180);
    }

    delay(1000);
    
  } 

  
}
