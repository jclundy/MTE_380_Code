#include <Servo.h>
#include "lift_params.h"

Servo servoLeft;
Servo servoRight;
Servo servoLatch;
Servo servoBridge;

int buttonVal =0;
double potVal = 0;
bool buttonPressed = false;

int height_switch = 0;
int left_switch = 0;
int right_switch = 0;

bool leftmotorON = false;
bool rightmotorON = false;

int motor_differential_slow = 100;
int motor_differential_fast = 500;

int SERVO_LEFT_GO_ms = 2000;
int SERVO_RIGHT_GO_ms = 1000;

int SERVO_LEFT_SLOW_ms = 1800;
int SERVO_RIGHT_SLOW_ms = 1200;

void AdjustRelativeMotorSpeed()
{
  int trim = 0;
  int temp = 0;
  int maxTrim = 500;

  while((!digitalRead(SWITCH_LEFT_PIN)) || (!digitalRead(SWITCH_RIGHT_PIN)))
  {
    potVal = analogRead(POT_PIN);
  
    Serial.write("PotVal: ");
    Serial.println(potVal);

    // potentiometer value controls relative speed of left vs right
    // at 511, left MS == right MS
    trim = potVal /1023.0;
    
    SERVO_LEFT_GO_ms = SERVO_LEFT_STOP_ms + (900*trim);
    SERVO_RIGHT_GO_ms = SERVO_RIGHT_STOP_ms - (900*(1-trim));
    
    Serial.write("trim: ");
    Serial.println(trim);
    Serial.write("left: ");
    Serial.println(SERVO_LEFT_GO_ms);
    Serial.write("right: ");
    Serial.println(SERVO_RIGHT_GO_ms);
    
    //servoLeft.writeMicroseconds(SERVO_LEFT_GO_ms);
    //servoRight.writeMicroseconds(SERVO_RIGHT_GO_ms);
  
    delay(100);
  }
  
}

double GetUltrasonicVal() {
  unsigned long t1;
  unsigned long t2;
  unsigned long pulseTimer;
  unsigned long pulse_width;
  double cm;

  delay(13); //Very necessary to capture accurate data over 2 meters!!!!

  digitalWrite(US_TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(US_TRIG_PIN, LOW);

  pulseTimer = 0;
    
  while ( digitalRead(US_ECHO_PIN) == 0 && pulseTimer < 50000 ) {
    pulseTimer++;
  }

  if (pulseTimer < 5000) {
    t1 = micros();
    while ( digitalRead(US_ECHO_PIN) == 1);
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

inline void Print(String msg){
  Serial.println(msg);
}

inline void Print(int val){
  Serial.println(val);
}

inline void Print(double val){
  Serial.println(val);
}

void setup() {
  
  // pin assignment for servos
  servoLeft.attach(SERVO_LEFT_PIN);
  servoRight.attach(SERVO_RIGHT_PIN);
  servoLatch.attach(LATCH_PIN);
  servoBridge.attach(BRIDGE_PIN);

  // Initialize drive servos stopped, positional servos in start position
  servoLeft.writeMicroseconds(SERVO_LEFT_STOP_ms);
  servoRight.writeMicroseconds(SERVO_RIGHT_STOP_ms);
  servoLatch.writeMicroseconds(SERVO_LATCH_LATCHED);
  servoBridge.writeMicroseconds(SERVO_BRIDGE_UP);

  pinMode(PUSH_BUTTON_PIN, INPUT);
  pinMode(SWITCH_LEFT_PIN, INPUT);
  pinMode(SWITCH_RIGHT_PIN, INPUT);
  pinMode(SWITCH_HEIGHT_PIN, INPUT);

  pinMode(US_TRIG_PIN,OUTPUT);
  pinMode(US_ECHO_PIN,INPUT);
  
  Serial.begin(9600);

  AdjustRelativeMotorSpeed();
}

void loop() 
{
  // Start Signal: use both limit switches 
  Print("Waiting for start..."); 
  while((!digitalRead(SWITCH_LEFT_PIN)) || (!digitalRead(SWITCH_RIGHT_PIN)));
  while((digitalRead(SWITCH_LEFT_PIN)) || (digitalRead(SWITCH_RIGHT_PIN)));

  servoLatch.writeMicroseconds(SERVO_LATCH_UNLATCHED);

  double wall_dist = GetUltrasonicVal();
  Print("wall_dist: ");
  Print(wall_dist);
  
  // While switches not pressed
  while (!digitalRead(SWITCH_RIGHT_PIN) || !digitalRead(SWITCH_LEFT_PIN)){

    // If neither pressed
    if (!digitalRead(SWITCH_RIGHT_PIN) && (!digitalRead(SWITCH_LEFT_PIN)))
    {
      servoLeft.writeMicroseconds(SERVO_LEFT_GO_ms);
      servoRight.writeMicroseconds(SERVO_RIGHT_GO_ms);
    }
    // If right pressed
    else if (digitalRead(SWITCH_RIGHT_PIN))
    {
      servoLeft.writeMicroseconds(SERVO_LEFT_GO_ms);
      servoRight.writeMicroseconds(SERVO_RIGHT_STOP_ms);
    }
    // Left pressed
    else
    {
      servoLeft.writeMicroseconds(SERVO_LEFT_STOP_ms);
      servoRight.writeMicroseconds(SERVO_RIGHT_GO_ms);
    }
  }
  servoLeft.writeMicroseconds(SERVO_LEFT_STOP_ms);
  servoRight.writeMicroseconds(SERVO_RIGHT_STOP_ms);

  while (!digitalRead(SWITCH_HEIGHT_PIN));
  
  Serial.println("Reached");
  delay(10);
}
