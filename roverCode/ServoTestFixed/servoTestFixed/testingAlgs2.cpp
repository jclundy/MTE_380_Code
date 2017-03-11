#include "testingAlgs2.h"

testingAlgorithms::testingAlgorithms() {

  
}


testingAlgorithms::~testingAlgorithms() {

  
}

void testingAlgorithms::testPopulationArray(blipperBrain* blipper) {

  blipper->populatePositionArray();

  for (int i = 0; i < NUM_READINGS; i++) {
    Serial.println(blipper->posReadings[i]);
  }
  
}

void testingAlgorithms::testFilterArray(blipperBrain* blipper) {

  Serial.println("Starting test");
  testPopulationArray(blipper);

  Serial.println("Best guess value:");
  Serial.println(blipper->filterPositionArray());
  
}

