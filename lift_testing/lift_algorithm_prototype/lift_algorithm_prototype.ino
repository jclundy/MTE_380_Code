#include <Servo.h>

#define DEBUG

Servo servoLeft;
Servo servoRight;
Servo servoLatch; // 2400 is max value (rotating to raise the lift) 600 is lowest value (rotating to lock the lift)
Servo servoBridge; // 2400 is max value (raised bridge) 600 is lowest value (lowered bridge)

// Positional servo values
const int SERVO_LATCH_LATCHED = 600;
const int SERVO_LATCH_UNLATCHED = 2400;
const int SERVO_BRIDGE_DOWN = 600;
const int SERVO_BRIDGE_UP = 2400;

// Servo stop values
const int SERVO_LEFT_STOP=92;
const int SERVO_RIGHT_STOP=92;
const int SERVO_LEFT_STOP_ms=1500;
const int SERVO_RIGHT_STOP_ms=1500;

// Servo.write values
/*
const int SERVO_LEFT_FORWARD = 102;
const int SERVO_RIGHT_FORWARD = 82;
const int SERVO_LEFT_REVERSE = 82;
const int SERVO_RIGHT_REVERSE = 102;
*/

const int PUSH_BUTTON_PIN = 13;

const int SWITCH_LEFT_PIN = 2;
const int SWITCH_RIGHT_PIN = 4;
const int SWITCH_HEIGHT_PIN = 12;


const int COMMUNICATION_PIN = 3; 

// Ultrasonic 
int vcc = 2; 
const int trig = 7; 
const int echo = 8; 
int gnd = 5; 

const int SERVO_RIGHT_PIN = 11;
const int SERVO_LEFT_PIN  = 10;
const int LATCH_PIN = 9;
const int BRIDGE_PIN = 6;

const int POT_PIN = 2;

int buttonVal =0;
bool buttonPressed = false;

int height_switch = 0;
int left_switch = 0;
int right_switch = 0;
bool leftmotorON = false;
bool rightmotorON = false;

void setup() {
  
// pin assignment for servos
  servoLeft.attach(SERVO_LEFT_PIN);
  servoRight.attach(SERVO_RIGHT_PIN);
  servoLatch.attach(LATCH_PIN);
  servoBridge.attach(BRIDGE_PIN);

// Initialize drive servos stopped
  servoLeft.writeMicroseconds(SERVO_LEFT_STOP_ms);
  servoRight.writeMicroseconds(SERVO_RIGHT_STOP_ms);

 
  servoLatch.writeMicroseconds(SERVO_LATCH_LATCHED);
  servoBridge.writeMicroseconds(SERVO_BRIDGE_UP);
    
  pinMode(PUSH_BUTTON_PIN, INPUT);
  pinMode(SWITCH_LEFT_PIN, INPUT);
  pinMode(SWITCH_RIGHT_PIN, INPUT);
  pinMode(SWITCH_HEIGHT_PIN, INPUT);

  //PinModes for Ultrasonic
  pinMode(trig,OUTPUT);
  pinMode(echo,INPUT);
  
  Serial.begin(9600);
}


void getSerialInputToServo() {

  int incomingInt;

  Serial.println("Input a Microseconds value: ");
  while (Serial.available() <= 0);
  incomingInt = Serial.parseInt();
  Serial.println(incomingInt);

  //Change this servo to whatever you want and recompile
  servoBridge.writeMicroseconds(incomingInt);
}

void printButtonValues() {
  buttonVal = digitalRead(PUSH_BUTTON_PIN);
  left_switch = digitalRead(SWITCH_LEFT_PIN);
  right_switch = digitalRead(SWITCH_RIGHT_PIN);
  height_switch = digitalRead(SWITCH_HEIGHT_PIN);

  Serial.write("Button: ");
  Serial.println(buttonVal);

  Serial.write("Left Switch: ");
  Serial.println(left_switch);

  Serial.write("Right Switch: ");
  Serial.println(right_switch);

   Serial.write("Height Switch: ");
  Serial.println(height_switch);
}

// Returns the distance read by the ultrasonic sensor (cm)
double getUltrasonicRead() {
  unsigned long t1;
  unsigned long t2;
  unsigned long pulseTimer;
  unsigned long pulse_width;
  double cm;

  delay(13); //Very necessary to capture accurate data over 2 meters!!!!

  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  pulseTimer = 0;
    
  while ( digitalRead(echo) == 0 && pulseTimer < 50000 ) {
    pulseTimer++;
  }

  if (pulseTimer < 5000) {
    t1 = micros();
    while ( digitalRead(echo) == 1);
    t2 = micros();
    pulse_width = t2 - t1;
    cm = pulse_width / 58.0;
  } else {
    cm = 999;
    Serial.println("Timeout");
  }

  if (cm < 0.01) {
    cm = 999;
  }
    
  return cm;
}

/*
void debugPrintln(String str) {
  #ifdef DBG
  Serial.println(str);
  #endif
}

void debugPrintValue(String valueName, int value) {
  #ifdef DBG
  Serial.print(valueName);
  Serial.print(" : ");
  Serial.println(value);
  #endif
}

void resetLift(){
  debugPrintln("Resetting Lift");
  servoLeft.write(SERVO_LEFT_STOP);
  servoRight.write(SERVO_RIGHT_STOP);
  servoBridge.writeMicroseconds(SERVO_BRIDGE_UP);
  servoLatch.writeMicroseconds(SERVO_LATCH_LATCHED);
}
*/

void loop() {

  // Adjust relative speed? Y/N

  // write test 
  resetLift();

  // debugPrintln("waiting for press and release of both switches");
  //Wait for both right and left switch press and release
  while (!readButton(SWITCH_RIGHT_PIN) || !readButton(SWITCH_LEFT_PIN)){}
  while (readButton(SWITCH_RIGHT_PIN) || readButton(SWITCH_LEFT_PIN)){}
  // debugPrintln("LIFT_ALGORITM_START");
  servoLatch.writeMicroseconds(SERVO_LATCH_UNLATCHED);
  
  // debugPrintln("driving");
  //waiting for both switches to be pressed (up against wall)
  while (!readButton(SWITCH_RIGHT_PIN) || !readButton(SWITCH_LEFT_PIN)){
    if (!readButton(SWITCH_RIGHT_PIN) && !readButton(SWITCH_LEFT_PIN))
    {
      servoLeft.write(SERVO_LEFT_FORWARD);
      servoRight.write(SERVO_RIGHT_FORWARD);
    }
    else if (readButton(SWITCH_RIGHT_PIN))
    {
      servoLeft.write(SERVO_LEFT_FORWARD);
      servoRight.write(SERVO_RIGHT_STOP);
    }
    else
    {
      servoLeft.write(SERVO_LEFT_STOP);
      servoRight.write(SERVO_RIGHT_FORWARD);
    }
  }
  servoLeft.write(SERVO_LEFT_STOP);
  servoRight.write(SERVO_RIGHT_STOP);
  // debugPrintln("~~BOTH SWITCHES PRESSED~~");

  // debugPrintln("waiting for height limit swich...");  
  while (!readButton(SWITCH_HEIGHT_PIN)){}
  // debugPrintln("height reached");

  
  servoBridge.writeMicroseconds(SERVO_BRIDGE_DOWN);
  // debugPrintln("bridge lowering");
  delay(1000);

  digitalWrite(COMMUNICATION_PIN,HIGH);
  servoLatch.writeMicroseconds(SERVO_LATCH_LATCHED);
  
  debugPrintln("waiting for manual lift reset");
  while (readButton(SWITCH_HEIGHT_PIN)){}

}
