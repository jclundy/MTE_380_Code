  /*
*  This code is in the public domain.
*  (Do whatever you want with it.)
*  min-56 deg
*/

// Need the Servo library
#include <Servo.h>

#define MOTOR_PIN 10
// This is our motor.
Servo myMotor;
// This is the final output
// written to the motor.
String incomingString;

#define RESTING ANGLE 95
#define CW_FULL_SPEED_uS 1300
#define CCW_FULL_SPEED_uS 1700
#define RESTING_uS 1525
// Set everything up  
void setup()
{
  // Put the motor to Arduino pin #9
  myMotor.attach(MOTOR_PIN);
  //wrist.attach(WRIST_PIN);
  delay(10);
  myMotor.writeMicroseconds(RESTING_uS);
  //delay(1000);
  // Required for I/O from Serial monitor
  Serial.begin(9600);
  // Print a startup message
  Serial.println("initializing");
}


void loop()
{
  // If there is incoming value
  if(Serial.available() > 0)
  {
    // read the value
    char ch = Serial.read();
  
    /*
    *  If ch isn't a newline
    *  (linefeed) character,
    *  we will add the character
    *  to the incomingString
    */
    if (ch != 10){
      // Print out the value received
      // so that we can see what is
      // happening
      Serial.print("I have received: ");
      Serial.print(ch, DEC);
      Serial.print('\n');
    
      // Add the character to
      // the incomingString
      incomingString += ch;
    }
    // received a newline (linefeed) character
    // this means we are done making a string
    else
    {
      // print the incoming string
      Serial.println("I am printing the entire string");
      Serial.println(incomingString);
    
      // Convert the string to an integer
      int val = incomingString.toInt();
    
      // print the integer
      Serial.println("Printing the value: ");
      Serial.println(val);
    
      /*
      *  We only want to write an integer between
      *  1300 and 1700 to the motor. 
      */
      if(val == 0) {
        myMotor.writeMicroseconds(RESTING_uS);
        Serial.println("servo stopped");
      }
      else if (val >= CW_FULL_SPEED_uS && val <= CCW_FULL_SPEED_uS)
     {
       // Print confirmation that the
       // value is between 1300 and 1700
       Serial.println("Value is between 1300 and 1700");
       // Write to Servo
       myMotor.writeMicroseconds(val);
     }
     
     // The value is not between 1300 and 1700.
     // We do not want write this value to
     // the motor.
     else
     {
       Serial.println("Value is NOT between 1300 and 1700");
       Serial.println("Error with the input");
     }    
      // Reset the value of the incomingString
      incomingString = "";
    }
  }
}

