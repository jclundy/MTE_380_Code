#include "testingAlgorithms.h"



testingAlgorithms::testingAlgorithms()
{
  
}

testingAlgorithms::~testingAlgorithms()
{
  
}


void testingAlgorithms::testPopulateArray(blipperBrain* blipper) {

  blipper->populatePositionArray();

  for (int i = 0; i < NUM_READINGS; i++) {
     Serial.println(blipper->posReadings[i]);
  }
  
  
}

void testingAlgorithms::testFilterArray(blipperBrain* blipper) {

  blipper->populatePositionArray();

  for (int i = 0; i < NUM_READINGS; i++) {
     Serial.println(blipper->posReadings[i]);
  }

  Serial.println("Best Guess Value:");
  Serial.println(blipper->filterPositionArray());
  
  
}

void testingAlgorithms::testUltrasonicSensor(blipperBrain* blipper) {

  Serial.println("");
  
}

