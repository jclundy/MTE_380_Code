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

int SERVO_LEFT_GO_ms = 2000;
int SERVO_RIGHT_GO_ms = 1000;

int SERVO_LEFT_REVERSE_ms = 2000;
int SERVO_RIGHT_REVERSE_ms = 1000;

int SERVO_LEFT_SLOW_FORWARD_ms = 1800;
int SERVO_RIGHT_SLOW_FORWARD_ms = 1200;

int SERVO_LEFT_SLOW_REVERSE_ms = 1200;
int SERVO_RIGHT_SLOW_REVERSE_ms = 1800;

double trim = 0.5;

void TestDrivingTrim() {
  int incomingInt = 0;
  double incomingValue = 0;
  
  Serial.println("Input driving trim");
  
  while((!digitalRead(SWITCH_LEFT_PIN)) || (!digitalRead(SWITCH_RIGHT_PIN))){
  
  Print("Waiting for integer input 0-100...");
  
  while (Serial.available() <= 0)
  {
    if(digitalRead(SWITCH_LEFT_PIN) && digitalRead(SWITCH_RIGHT_PIN))
    {
      return;
    }
  }
  
  if (Serial.available() > 0) {
      incomingInt = Serial.parseInt();
      Serial.print("Incoming integer: ");
      Serial.println(incomingInt);
      incomingValue = incomingInt / 100.0;
      Serial.print("Double Value/Trim: ");
      Serial.println(incomingValue);

      trim = incomingValue;

      SERVO_LEFT_GO_ms = SERVO_LEFT_STOP_ms + (1000.0*trim);
      SERVO_RIGHT_GO_ms = SERVO_RIGHT_STOP_ms - (1000.0*(1-trim));

      SERVO_LEFT_SLOW_FORWARD_ms = SERVO_LEFT_STOP_ms + (200.0*trim);
      SERVO_RIGHT_SLOW_FORWARD_ms = SERVO_RIGHT_STOP_ms - (200.0*(1-trim));

      SERVO_LEFT_SLOW_REVERSE_ms = SERVO_RIGHT_SLOW_FORWARD_ms;
      SERVO_RIGHT_SLOW_REVERSE_ms = SERVO_LEFT_SLOW_FORWARD_ms;

      Serial.print("Left servo go: ");
      Serial.println(SERVO_LEFT_GO_ms);
      Serial.print("Right servo go: ");
      Serial.println(SERVO_RIGHT_GO_ms);

      Serial.print("Left servo slow: ");
      Serial.println(SERVO_LEFT_SLOW_FORWARD_ms);
      Serial.print("Right servo slow: ");
      Serial.println(SERVO_RIGHT_SLOW_FORWARD_ms);

      servoLeft.writeMicroseconds(SERVO_LEFT_SLOW_FORWARD_ms);
      servoRight.writeMicroseconds(SERVO_RIGHT_SLOW_FORWARD_ms);
    
      delay(2000);

      servoLeft.writeMicroseconds(SERVO_LEFT_STOP_ms);
      servoRight.writeMicroseconds(SERVO_RIGHT_STOP_ms);

    }
  }
  Serial.println("Exiting trim function");
}

/*void AdjustRelativeMotorSpeed()
{
  while((!digitalRead(SWITCH_LEFT_PIN)) || (!digitalRead(SWITCH_RIGHT_PIN)));  
  while((digitalRead(SWITCH_LEFT_PIN)) || (digitalRead(SWITCH_RIGHT_PIN)));
  while((!digitalRead(SWITCH_LEFT_PIN)) || (!digitalRead(SWITCH_RIGHT_PIN)))
  {
    Print("In speed control Loop");
    
    potVal = analogRead(POT_PIN);
  
    Serial.write("PotVal: ");
    Serial.println(potVal);

    // potentiometer value controls relative speed of left vs right
    // at 511, left MS == right MS
    trim = potVal /1023.0;
    
    SERVO_LEFT_GO_ms = SERVO_LEFT_STOP_ms + (200.0*(1+trim));
    SERVO_RIGHT_GO_ms = SERVO_RIGHT_STOP_ms - (200.0*(1-trim));
    
    Serial.write("trim: ");
    Serial.println(trim);
    Serial.write("left: ");
    Serial.println(SERVO_LEFT_GO_ms);
    Serial.write("right: ");
    Serial.println(SERVO_RIGHT_GO_ms);
    
    servoLeft.writeMicroseconds(SERVO_LEFT_GO_ms);
    servoRight.writeMicroseconds(SERVO_RIGHT_GO_ms);
  
    delay(100);
  }
  Print("out of loop");
}*/

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

void Reset()
{
  Print("Resetting");
  servoLeft.writeMicroseconds(SERVO_LEFT_STOP_ms);
  servoRight.writeMicroseconds(SERVO_RIGHT_STOP_ms);
  servoBridge.writeMicroseconds(SERVO_BRIDGE_UP);
  servoLatch.writeMicroseconds(SERVO_LATCH_LATCHED);
}

void PrintSpeeds()
{
  Serial.print("Left servo go: ");
      Serial.println(SERVO_LEFT_GO_ms);
      Serial.print("Right servo go: ");
      Serial.println(SERVO_RIGHT_GO_ms);

      Serial.print("Left servo reverse: ");
      Serial.println(SERVO_LEFT_REVERSE_ms);
      Serial.print("Right servo reverse: ");
      Serial.println(SERVO_RIGHT_REVERSE_ms);

      Serial.print("Left servo slow: ");
      Serial.println(SERVO_LEFT_SLOW_FORWARD_ms);
      Serial.print("Right servo slow: ");
      Serial.println(SERVO_RIGHT_SLOW_FORWARD_ms);
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

  // AdjustRelativeMotorSpeed();
  TestDrivingTrim();

  SERVO_LEFT_GO_ms = SERVO_LEFT_STOP_ms + (1000.0*trim);
  SERVO_RIGHT_GO_ms = SERVO_RIGHT_STOP_ms - (1000.0*(1-trim));

  SERVO_LEFT_SLOW_FORWARD_ms = SERVO_LEFT_STOP_ms + (200.0*trim);
  SERVO_RIGHT_SLOW_FORWARD_ms = SERVO_RIGHT_STOP_ms - (200.0*(1-trim));

  SERVO_LEFT_SLOW_REVERSE_ms = SERVO_RIGHT_SLOW_FORWARD_ms;
  SERVO_RIGHT_SLOW_REVERSE_ms = SERVO_LEFT_SLOW_FORWARD_ms;

  SERVO_LEFT_REVERSE_ms = SERVO_RIGHT_GO_ms;
  SERVO_RIGHT_REVERSE_ms = SERVO_LEFT_GO_ms;
  
  PrintSpeeds();
}

void loop() 
{
  Reset();
  
  // Start Signal: use both limit switches 
  Print("Waiting for start..."); 
  while((!digitalRead(SWITCH_LEFT_PIN)) || (!digitalRead(SWITCH_RIGHT_PIN)));
  while((digitalRead(SWITCH_LEFT_PIN)) || (digitalRead(SWITCH_RIGHT_PIN)));

  Print("Unlatching...");
  servoLatch.writeMicroseconds(SERVO_LATCH_UNLATCHED);
  Print("Unlatched");

  double wall_dist = GetUltrasonicVal();
  Print("wall_dist: ");
  Print(wall_dist);

  Print("Entering full speed loop.");

  // Go full speed until 20 cm out
  while(wall_dist > 25)
  {
    wall_dist = GetUltrasonicVal();
    Print("Wall_dist: ");
    Print(wall_dist);
    
    // drive straight 
    servoLeft.writeMicroseconds(SERVO_LEFT_GO_ms);
    servoRight.writeMicroseconds(SERVO_RIGHT_GO_ms);

    delay(50);
  }

  Print("-------------Slowing---------------");
  // While switches not pressed
  while (!digitalRead(SWITCH_RIGHT_PIN) || !digitalRead(SWITCH_LEFT_PIN)){

    // If neither pressed
    if (!digitalRead(SWITCH_RIGHT_PIN) && (!digitalRead(SWITCH_LEFT_PIN)))
    {
      servoLeft.writeMicroseconds(SERVO_LEFT_SLOW_FORWARD_ms);
      servoRight.writeMicroseconds(SERVO_RIGHT_SLOW_FORWARD_ms);
    }
    // If right pressed
    else if (digitalRead(SWITCH_RIGHT_PIN))
    {
      servoLeft.writeMicroseconds(SERVO_LEFT_GO_ms);
      servoRight.writeMicroseconds(SERVO_RIGHT_REVERSE_ms);
    }
    // Left pressed
    else
    {
      servoLeft.writeMicroseconds(SERVO_LEFT_REVERSE_ms);
      servoRight.writeMicroseconds(SERVO_RIGHT_GO_ms);
    }
  }
  servoLeft.writeMicroseconds(SERVO_LEFT_STOP_ms);
  servoRight.writeMicroseconds(SERVO_RIGHT_STOP_ms);

  Print("Waiting for height switch...");
  while (!digitalRead(SWITCH_HEIGHT_PIN));
  Print("Height switch pressed. Lowering Bridge...");

  servoBridge.writeMicroseconds(SERVO_BRIDGE_DOWN);
  Print("Bridge Lowered");
  
  delay(1000);
  
  Print("Writing to communication pin...");
  digitalWrite(COMMUNICATION_PIN,HIGH);

  Print("Latch servo back to latched position...");
  servoLatch.writeMicroseconds(SERVO_LATCH_LATCHED);
  
  Print("Waiting for height switch to be unpressed...");
  while (digitalRead(SWITCH_HEIGHT_PIN));
  Print("Height switch unpressed.");
  
  delay(10);
}
