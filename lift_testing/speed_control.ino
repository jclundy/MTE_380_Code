#include <Servo.h>

Servo servoLeft;
Servo servoRight;
Servo servoLatch;
Servo servoBridge;

int SERVO_LEFT_STOP=92;
int SERVO_RIGHT_STOP=92;

int button1IN = 13;
int switchLeft = 2;
int switchRight = 4;
int switchHeight = 12;

//int vcc = 2; 
//int trig = 8; 
//int echo = 7; 
//int gnd = 5; 

int servo1 = 11;
int servo2 = 10;
int latchpin = 9;
int bridgepin = 6;

int potpin = 2;

int buttonVal =0;
bool buttonPressed = false;

double trim = 0;

//int switchVal = 0;
int height_switch = 0;
int left_switch = 0;
int right_switch = 0;
bool leftmotorON = false;
bool rightmotorON = false;

int SERVO_LEFT_GO = 102;
int SERVO_RIGHT_GO = 82;

int potVal = 0;
bool motorsOFF = true;
int maxTrim = 500;
// max speed of left 1000 max speed of right 2000

void setup() {
  // pin assignment for servos
  servoLeft.attach(servo1);
  servoRight.attach(servo2);
  servoLatch.attach(latchpin);
  servoBridge.attach(bridgepin);

// initialize stopped
  //servoLeft.write(SERVO_LEFT_STOP);
  //servoRight.write(SERVO_RIGHT_STOP);
  servoLeft.writeMicroseconds(1500);
  servoRight.writeMicroseconds(1500);

  //servoLatch.write(0);
    
  pinMode(button1IN, INPUT);
  pinMode(switchLeft, INPUT);
  pinMode(switchRight, INPUT);
  pinMode(switchHeight, INPUT);
//  pinMode(LEDpin, OUTPUT);

  //digitalWrite(LEDpin, LOW);
  
  Serial.begin(9600);
}

void loop() {
  buttonVal = digitalRead(button1IN);
  potVal = analogRead(potpin);
  /*left_switch = digitalRead(switchLeft);
  right_switch = digitalRead(switchRight);
  height_switch = digitalRead(switchHeight);

  Serial.write("Button: ");
  Serial.println(buttonVal);

  Serial.write("Left Switch: ");
  Serial.println(left_switch);

  Serial.write("Right Switch: ");
  Serial.println(right_switch);

   Serial.write("Height Switch: ");
  Serial.println(height_switch);
   
  delay(1000);*/

  // Serial.println(potVal);

  int leftMS = 2000;
  int rightMS = 2000;
  int temp = 0;

  // Button Pressed
  if((buttonVal == HIGH) && !buttonPressed)
  {
    buttonPressed = true;
    
    if(motorsOFF)
    {
      motorsOFF = false;
      
      servoLeft.writeMicroseconds(leftMS);
      servoRight.writeMicroseconds(rightMS);
    }
    else
    {
      motorsOFF = true;
      servoLeft.writeMicroseconds(1500);
      servoRight.writeMicroseconds(1500);
    }  
  }
  // Button Released 
  else if((buttonVal == LOW) && buttonPressed)
  {
    buttonPressed = false; 
  }
  
  if(!motorsOFF)
  {
    // potentiometer value controls relative speed of left vs right
    // at 511, left MS == right MS
    trim = potVal /1023.0;
    
    leftMS = 1500 + (900*trim);
    rightMS = 1500 - (900*(1-trim));
    Serial.write("trim: ");
    Serial.println(trim);
    Serial.write("left: ");
    Serial.println(leftMS);
    Serial.write("right: ");
    Serial.println(rightMS);

    
    //leftMS = (potVal/1023.0)*2000;
    //rightMS = ((1023.0-potVal)/1023.0)*2000;
    servoLeft.writeMicroseconds(leftMS);
    servoRight.writeMicroseconds(rightMS);
  }

  delay(100);
}
