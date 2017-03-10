#include "blipperBrain.h"



blipperBrain::blipperBrain(Servo* inputServo)
{
  mainServo = inputServo;

  pinMode(TRIG_PIN,OUTPUT);
  pinMode(ECHO_PIN,INPUT);

  
}

blipperBrain::~blipperBrain()
{
  delete mainServo;
}

void blipperBrain::rotateServo(int pos) {

  int rotateDelay = abs(pos-servoPos) * 1000 / SERVO_DEGREES_PER_SEC + 5;
  
  mainServo->write(pos);
  
  delay(rotateDelay);
  servoPos = pos;
}

void blipperBrain::populatePositionArray() {

  if (servoPos != 0) {
    rotateServo(0);
  }

  int degreePerReading = 180 / NUM_READINGS;

  for (int i = 0; i < NUM_READINGS; i ++) {
    rotateServo(i*degreePerReading);
    posReadings[i] = getUltrasonicRead();
  }
}

int blipperBrain::filterPositionArray() {

  float verticalTol = 10;
  int lengthTol = 5;

  int* polePoints = new int[NUM_READINGS/lengthTol];
  int polePointsSize = 0;

  int desiredAngle = 90;
  
  

  bool isInTolerance;
  
  for (int i = 0; i < NUM_READINGS - lengthTol; i++) {

    isInTolerance = true;
    
    for (int j = 1; j < lengthTol; j++) {
      if (abs(posReadings[j]-posReadings[i]) > verticalTol) {
        isInTolerance = false;
      }
    }

    if (isInTolerance) {
      polePoints[polePointsSize] = i + lengthTol/2;
      polePointsSize++;
    }
    
  }

  int bestGuessIndex = 0;
  int bestGuessValue = 180;
  
  for (int i = 0; i < polePointsSize; i++) {

    if (abs(polePoints[i] - desiredAngle) < bestGuessValue) {
      bestGuessValue = abs(polePoints[i] - desiredAngle);
      bestGuessIndex = i;
    }
  }

  
  

  delete polePoints;

  return bestGuessValue;
  
}

int blipperBrain::getPoleAngle() {

  populatePositionArray();
  return filterPositionArray();
  
  
}

float blipperBrain::getUltrasonicRead() {

  unsigned long t1;
  unsigned long t2;
  unsigned long pulseTimer;
  unsigned long pulse_width;
  float cm;

  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  pulseTimer = 0;

  
  while ( digitalRead(ECHO_PIN) == 0 && pulseTimer < 50000 ) {
    pulseTimer++;
  }

  if (pulseTimer < 5000) {
    t1 = micros();
  while ( digitalRead(ECHO_PIN) == 1);
  t2 = micros();
  pulse_width = t2 - t1;
  cm = pulse_width / 58.0;
  } else {
    cm = 999;
  }

  return cm;  
}
