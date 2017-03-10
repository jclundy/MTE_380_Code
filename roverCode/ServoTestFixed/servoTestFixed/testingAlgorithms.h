
#include "blipperBrain.h"

class testingAlgorithms
{
public:
  testingAlgorithms();
  ~testingAlgorithms();


  void testPopulateArray(blipperBrain* blipper);
  void testFilterArray(blipperBrain* blipper);

  void testUltrasonicSensor(blipperBrain* blipper);





  static void blinkWait(unsigned int waitTime, unsigned int blinkTime) {

  int totalTime = 0;

  while (totalTime < waitTime) {
    digitalWrite(LED_BUILTIN,HIGH);
    delay(blinkTime/2);
    digitalWrite(LED_BUILTIN,LOW);
    delay(blinkTime/2);
    totalTime += blinkTime;
  }

  
}
 
  

private:

  
};


