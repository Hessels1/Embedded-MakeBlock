#include "MeOrion.h"
 
MeDCMotor motor1(M1);
MeDCMotor motor2(M2);
MeUltrasonicSensor ultraSensor(PORT_3);
 
int baseSpeedMoter1 = 100;
int baseSpeedMotor2 = -100;
 
int rightTurnMotor1 = -75;
int rightTurnMotor2 = -75;
int leftTurnMotor1 = 75;
int leftTurnMotor2 = 75;
 
double distance;
double currentDistanceRight;
double currentDistanceLeft;

void turnRight() {
  motor1.run(rightTurnMotor1);
  motor2.run(rightTurnMotor2);
  delay(1500);
}

void turnLeft() {
  motor1.run(leftTurnMotor1);
  motor2.run(leftTurnMotor2);
  delay(800);
}

void checkRight() {
  motor1.run(rightTurnMotor1);
  motor2.run(rightTurnMotor2);
  delay(1500);
  currentDistanceRight = calculateDistance();
  resetLeft();
}
 
void checkLeft() {
  motor1.run(leftTurnMotor1);
  motor2.run(leftTurnMotor2);
  delay(1500);
  currentDistanceLeft = calculateDistance();
  resetRight();
}

void resetRight() {
  motor1.run(rightTurnMotor1);
  motor2.run(rightTurnMotor2);
  delay(1500);
}

void resetLeft() {
  motor1.run(leftTurnMotor1);
  motor2.run(leftTurnMotor2);
  delay(1500);
}
 
double calculateDistance() {
  return ultraSensor.distanceCm();
}
 
bool checkTurnDirection() {
  if(currentDistanceRight < currentDistanceLeft) {
    return true;
  }
  return false;
}
 
void logDistance() {
  Serial.print("Distance : ");
  Serial.print(ultraSensor.distanceCm() );
  Serial.println(" cm");
  delay(100);
}

void forward() {
  motor1.run(baseSpeedMoter1); /* value: between -255 and 255. */
  motor2.run(baseSpeedMotor2); /* value: between -255 and 255. */
  delay(50); 
}
 
void setup() {
  Serial.begin(9600);
}
 
void loop() {
  logDistance();
  double x = calculateDistance();
  x = x + 0.5;
  int distance = (int)x;
  if(distance < 15) {
      checkLeft();
      checkRight();
      if(checkTurnDirection) {
          turnRight();
      } else {
          turnLeft();
      } 
  }
  forward();
}
