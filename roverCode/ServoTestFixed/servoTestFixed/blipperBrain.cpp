#include "blipperBrain.h"



blipperBrain::blipperBrain(Servo* inputServo)
{
  mainServo = inputServo;

  pinMode(TRIG_PIN,OUTPUT);
  pinMode(ECHO_PIN,INPUT);

  lastReadingValue = 999;

  
}

blipperBrain::~blipperBrain()
{
  delete mainServo;
}

void blipperBrain::rotateServo(int pos) {
  mainServo->write(pos);
}

double blipperBrain::waitToSeePole() {

  double readingValue = 999;
  double tolerance = 10;
  int windowLength = 50;
  int ceilingValue = 100;
  int numGoodReadings = 0;


  bool searching = true;

  while (searching) {
    readingValue = getUltrasonicRead();

    if (readingValue < ceilingValue) {
  
      
      
      if (abs(readingValue - lastReadingValue) < tolerance) {
        numGoodReadings++;
      } else {
        numGoodReadings = 0;
      }
      if (numGoodReadings >= windowLength) {
        searching = false;
      }
    }

    lastReadingValue = readingValue;
    
  }

  lastKnownPolePosition = readingValue;
  return readingValue;
  
}



double blipperBrain::getUltrasonicRead() {

  unsigned long t1;
  unsigned long t2;
  unsigned long pulseTimer;
  unsigned long pulse_width;
  double cm;

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

  if (cm < 0.01) {
    cm = 999;
  }
    
  return cm;  
}

bool blipperBrain::driveTowardsPole() {

  double readingValue;
  double tolerance = 5;
  int windowLength = 3;
  int numBadReadings = 0;

  readingValue = lastKnownPolePosition;

  while (readingValue > 10) {
    readingValue = getUltrasonicRead();

    
    if (abs(readingValue - lastKnownPolePosition) > tolerance) {
      numBadReadings++;
    } else {
      numBadReadings = 0;
      lastKnownPolePosition = readingValue;
      lastReadingValue = readingValue;
    }
  
    if (numBadReadings >= windowLength) {
      //Serial.print("Lost pole at: ");
      //Serial.println(readingValue,10);
      return false;
    }
  }

  return true;
}

int blipperBrain::findPolePosition() {

  double readingValue = 999;
  double tolerance = 10;
  int windowLength = 10;
  int numGoodReadings = 0;

  unsigned int numReadings = 0;

  int servoPosition = 90;
  int degToSearch = 60;

  int lowerDegLimit = 90 - degToSearch;
  int upperDegLimit = 90 + degToSearch;


  bool searching = true;

  bool searchPhase1 = true;

  while (searching) {

    readingValue = getUltrasonicRead();

    if (abs(readingValue - lastKnownPolePosition) < tolerance) {
      numGoodReadings++;
    } else {
      numGoodReadings = 0;
    }
    if (numGoodReadings >= windowLength) {
      searching = false;
    }
    
    if (searchPhase1) {
      
      servoPosition--;
  
      if (servoPosition < lowerDegLimit) {
        searchPhase1 = false;
        rotateServo(90);
        servoPosition = 90;
        numReadings = 0;
        delay(500);
      }
    } else {
  
      servoPosition++;

      if (servoPosition > upperDegLimit) {
        rotateServo(90);
        delay(1000);
        return -1;
      }
    }

    rotateServo(servoPosition);
    numReadings++;
    delay(20);
      
  }


  lastReadingValue = readingValue;
  rotateServo(90);
  if (numReadings == windowLength) {
    return 90;
  } else {
    return servoPosition;
  }

  
  
  
}
