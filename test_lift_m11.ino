#include "Servo.h"

Servo servoLeft;
Servo servoRight;

int SERVO_LEFT_STOP=92;
int SERVO_RIGHT_STOP=92;

int button1IN = 8;
int switchLeft = 12;
int switchRight = 11;
int LEDpin = 7;

//int vcc = 2; 
//int trig = 2; 
//int echo = 3; 
//int gnd = 5; 

int servo1 = 5;
int servo2 = 6;
//int latchpin = 11;

int buttonVal =0;
bool buttonPressed = false;

//int switchVal = 0;
int left_switch = 0;
int right_switch = 0;
bool leftmotorON = false;
bool rightmotorON = false;

int SERVO_LEFT_GO = 102;
int SERVO_RIGHT_GO = 82;

void setup() {
  // pin assignment for servos
  servoLeft.attach(servo1);
  servoRight.attach(servo2);
  //servoLatch.attach(5);

// initialize stopped
  //servoLeft.write(SERVO_LEFT_STOP);
  //servoRight.write(SERVO_RIGHT_STOP);
  servoLeft.writeMicroseconds(1500);
  servoRight.writeMicroseconds(1500);

  //servoLatch.write(0);
    
  pinMode(button1IN, INPUT);
  pinMode(switchLeft, INPUT);
  pinMode(LEDpin, OUTPUT);

  digitalWrite(LEDpin, LOW);
  
  //Serial.begin(9600);

  //servoLatch.write(20);
}

void loop() {
  buttonVal = digitalRead(button1IN);
  left_switch = digitalRead(switchLeft);
  right_switch = digitalRead(switchRight);

  //Serial.println(switchVal);

  if(buttonVal == LOW)
   {
      digitalWrite(LEDpin, LOW);
   }
   else
   {
    digitalWrite(LEDpin, HIGH);
    }

 
// press once to start, once to stop
  if((buttonVal == LOW)&&(!buttonPressed))
  {
    buttonPressed = true;
    //digitalWrite(LEDpin, HIGH);

    if(rightmotorON || leftmotorON)
    {
      leftmotorON = false;
      rightmotorON = false;
      
      //servoLeft.write(SERVO_LEFT_STOP);
      //servoRight.write(SERVO_RIGHT_STOP);
      servoLeft.writeMicroseconds(2000);
      servoRight.writeMicroseconds(1200);
    }
    else
    {
      leftmotorON = true;
      rightmotorON = true;
      
      //servoLeft.write(SERVO_LEFT_GO);
      //servoRight.write(SERVO_RIGHT_GO);
      servoLeft.writeMicroseconds(2000);
      servoRight.writeMicroseconds(1000);
      }
  }
  else if ((buttonVal == HIGH)&&(buttonPressed))
  {
    buttonPressed = false;
    digitalWrite(LEDpin, LOW);
   }
   else if(leftmotorON || rightmotorON)
   {
    if(left_switch == HIGH)
    {
      leftmotorON = false;
      servoLeft.write(SERVO_LEFT_STOP);
      }
     
     if(right_switch == HIGH)
      {
        rightmotorON = false;
        servoRight.write(SERVO_RIGHT_STOP);
      }
      else{
        //digitalWrite(LEDpin, LOW);
        }
    }
}
