#include "blipperBrain.h"
#include "drivingBrain.h"

//A class to store repeated tests
class testingAlgorithms {

  public:

  testingAlgorithms();
  ~testingAlgorithms();

  //Rotational Blipper Specific Test
  void testPopulationArray(blipperBrain* blipper);
  //Rotational Blipper Specific Test
  void testFilterArray(blipperBrain* blipper);

  //Linear blipper Test
  void testInitialPoleDetection(blipperBrain* blipper);
  



  //Waits for a serial input of 0 to 1000 and sets the trim to that value / 1000 (so 500 is 0.5) and then drives for 3 seconds at 90% power.
  //Use this to figure out what trim value your system needs to drive straight
  void testDrivingTrim(drivingBrain* driver);
  
  //Waits for a serial input from 0 to inf and rotates at 90% power then delays for the inputted value, and then rotates back.
  //Use this to figure out what value of delay your system needs to turn 90 degrees
  void findRotationValue(drivingBrain* driver);
  
  //Waits for a serial input of rotation from 0 to inf and rotates the robot to that degree and back
  //Use this to test if your robot will rotate to 30, 15, or whatever degree you use in your program, reliably.
  void testRotationDegrees(drivingBrain* driver);
  
  //Waits for a serial input of 0 to 100 for drive power, and then drives forwards for 6 seconds at that power. 
  //Use this to test how well your robot drives at different power levels
  void testDrivePower(drivingBrain* driver);

  //Waits for a serial input of 0 to inf for microseconds input (usually 0 to 2500) and will write that microseconds to the left motor.
  //use to find your stop, forwards and backwards values.
  void leftServoTestMicroseconds(drivingBrain* driver);

  //Waits for a serial input of 0 to inf for microseconds input (usually 0 to 2500) and will write that microseconds to the right motor.
  //use to find your stop, forwards and backwards values.
  void rightServoTestMicroseconds(drivingBrain* driver);

  
  

  
};

