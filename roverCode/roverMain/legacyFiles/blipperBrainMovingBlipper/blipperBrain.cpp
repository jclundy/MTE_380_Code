#include "blipperBrain.h"



blipperBrain::blipperBrain(Servo* inputServo)
{
  mainServo = inputServo;

  pinMode(TRIG_PIN,OUTPUT);
  pinMode(ECHO_PIN,INPUT);

  servoPos = mainServo->read();

  
}

blipperBrain::~blipperBrain()
{
  delete mainServo;
}

void blipperBrain::rotateServo(int pos) {

  
  Serial.print("servoPos ");
  Serial.print(servoPos);
  Serial.print("pos: ");
  Serial.print(pos);
  
  unsigned int rotateDelay = abs(pos-servoPos) * 1000 / SERVO_DEGREES_PER_SEC + 5;
  Serial.print("RD: ");
  Serial.println(rotateDelay);

  
  mainServo->write(pos);

  
  delay(rotateDelay);
  servoPos = pos;
}

void blipperBrain::populatePositionArray() {

  if (servoPos != 0) {
    mainServo->write(0);
    delay(1000);
  }

  int degreePerReading = 180 / NUM_READINGS;


  for (int i = 0; i < NUM_READINGS; i ++) {
    mainServo->write(i*degreePerReading);
    delay(30);
    
    posReadings[i] = getUltrasonicRead();
  }
}

int blipperBrain::filterPositionArray() {

  int verticalTol = 3;
  int lengthTol = 8;

  int* polePoints = new int[NUM_READINGS];
  int polePointsSize = 0;

  int desiredAngle = 90;
  
  

  bool isInTolerance;
  
  for (int i = 0; i < NUM_READINGS - lengthTol; i++) {

    isInTolerance = true;
    
    for (int j = 1; j < lengthTol; j++) {
      if (abs(posReadings[j+i]-posReadings[i]) > verticalTol) {
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

  Serial.println("PolePoints array");

  for (int i = 0; i < polePointsSize; i++) {
    Serial.println(polePoints[i]);
  }
  
  for (int i = 0; i < polePointsSize; i++) {

    if (abs(polePoints[i] - desiredAngle) < bestGuessValue) {
      bestGuessValue = abs(polePoints[i] - desiredAngle);
      bestGuessIndex = i;
    }
  }

  
  bestGuessValue = polePoints[bestGuessIndex];

  delete polePoints;

  Serial.println("BestGuessValue:");

  return bestGuessValue;
  
}

int blipperBrain::getPoleAngle() {

  populatePositionArray();
  return filterPositionArray();
  
  
}

int blipperBrain::getUltrasonicRead() {

  unsigned long t1;
  unsigned long t2;
  unsigned long pulseTimer;
  unsigned long pulse_width;
  int cm;

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
