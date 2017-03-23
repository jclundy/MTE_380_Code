#include <Servo.h>
#include "roverBrain.h"
#include "testingAlgs2.h"
#include "spool.h"

#define FRONT_LEFT_MOTOR_PIN 11
#define FRONT_RIGHT_MOTOR_PIN 10
#define BACK_LEFT_MOTOR_PIN 3
#define BACK_RIGHT_MOTOR_PIN 9
#define WALL_DIRECTION_PIN A1
#define SPOOL_UP_BUTTON_PIN A2
#define GO_AHEAD_PIN A3

#define SPOOL_PIN 6
#define MOTOR_POWER_LOWERING 25


roverBrain* rover;
spool* spooler;

unsigned long timerValue = 0;

void setup() {
#ifdef DEBUG
  Serial.begin(9600);
#endif

  //Servo pointers
  Servo* servoFL_p = new Servo();
  Servo* servoFR_p = new Servo();
  Servo* servoBL_p = new Servo();
  Servo* servoBR_p = new Servo();
  Servo* servoSpool = new Servo();

  pinMode(FRONT_LEFT_MOTOR_PIN,OUTPUT);
  pinMode(FRONT_RIGHT_MOTOR_PIN,OUTPUT);
  pinMode(BACK_LEFT_MOTOR_PIN,OUTPUT);
  pinMode(BACK_RIGHT_MOTOR_PIN,OUTPUT);
  pinMode(GO_AHEAD_PIN, INPUT);

  servoFL_p->attach(FRONT_LEFT_MOTOR_PIN);
  servoFR_p->attach(FRONT_RIGHT_MOTOR_PIN);
  servoBL_p->attach(BACK_LEFT_MOTOR_PIN);
  servoBR_p->attach(BACK_RIGHT_MOTOR_PIN);
  servoSpool->attach(SPOOL_PIN);
  rover = new roverBrain(servoFL_p, servoFR_p, servoBL_p, servoBR_p);
  spooler = new spool(servoSpool);
  spooler->stopRotating();
  
  

  //Set wall direction
  pinMode(WALL_DIRECTION_PIN,INPUT);
  int wallDirectionReadValue = digitalRead(WALL_DIRECTION_PIN);
  if (wallDirectionReadValue == HIGH) {
    //left
    rover->blipper->setWallSide(1);
  } else {
    //right
    rover->blipper->setWallSide(2);
  }

  #ifdef DEBUG
    Serial.println("Initalized");
  #endif

}

void loweringLoop(){
  int state = SPOOL_UP;
#ifdef DEBUG
  Serial.println("state: SPOOL_UP");
#endif
  while (!digitalRead(GO_AHEAD_PIN))
  {
    if (!digitalRead(SPOOL_UP_BUTTON_PIN))
     {
       spooler->takeInSlow();
     }
     else
     {
       spooler->stopRotating();
     }
  }
  
#ifdef DEBUG
  Serial.println("state: WAITING_FOR_LIFT_COM");
#endif
  //startTimer();
  //rover is waiting for communications line to go low
//  while (readTimer() < WAITING_FOR_LIFT_COM_MAX_WINDOW)
//  {
//    if(readTimer() > WAITING_FOR_LIFT_COM_MIN_WINDOW && digitalRead(GO_AHEAD_PIN)) {
//      break;
//    }
//  }
  //while (!digitalRead(GO_AHEAD_PIN))
  //delay(WAITING_FOR_LIFT_COM_MIN_WINDOW);
  
#ifdef DEBUG
  Serial.println("state: DRIVING_FORWARD");
#endif
  startTimer();
  spooler->unspoolSlow();
  rover->wheelDriver->driveForwards(MOTOR_POWER_LOWERING);
  while (readTimer() < DRIVING_FORWARD_MAX_WINDOW)
  {
#ifdef DEBUG
    Serial.println("DRIVING_FORWARD!!!!!");
#endif
  }
  
#ifdef DEBUG
  Serial.println("state: DRIVING_DOWN_SLOPE");
#endif
  startTimer();
  spooler->unspool();
  rover->wheelDriver->driveForwards(MOTOR_POWER_LOWERING);
  while (readTimer() < DRIVING_DOWN_SLOPE_MAX_WINDOW)
  {
#ifdef DEBUG
    Serial.println("DRIVING_DOWN_SLOPE!!!!!");
#endif
  }

#ifdef DEBUG
  Serial.println("state: VERTICAL_LOWERING");
#endif
  startTimer();
  spooler->unspool();
  rover->wheelDriver->driveForwards(MOTOR_POWER_LOWERING);
  while (readTimer() < VERTICAL_LOWERING_MAX_WINDOW)
  {
#ifdef DEBUG
    Serial.println("VERTICAL_LOWERING!!!!!");
#endif
  }

#ifdef DEBUG
  Serial.println("state: TOUCHING_DOWN");
#endif
  startTimer();
  spooler->unspool();
  rover->wheelDriver->driveForwards(MOTOR_POWER_LOWERING);
  while (readTimer() < TOUCHING_DOWN_MAX_WINDOW)
  {
#ifdef DEBUG
    Serial.println("TOUCHING_DOWN!!!!!");
#endif
  }
  spooler->stopRotating();
  rover->wheelDriver->driveStop();
}

void startTimer(){
  timerValue = millis();
}

unsigned long readTimer(){
  return millis() - timerValue;
}

void loop() {
  //rover->blipper->setWallSide(1);
  loweringLoop();
  delay(2000);
  rover->driveToPole();
}
