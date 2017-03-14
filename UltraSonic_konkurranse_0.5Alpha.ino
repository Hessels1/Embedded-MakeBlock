#include "MeOrion.h"
 
MeDCMotor motor1(M1);
MeDCMotor motor2(M2);
MeUltrasonicSensor ultraSensor(PORT_3);
 
int baseSpeedMotor1= 200;
int baseSpeedMotor2 = -200;
 
int rightTurnMotor1 = -90;
int rightTurnMotor2 = -90;
int leftTurnMotor1 = 90;
int leftTurnMotor2 = 90;
 
double distance;
double currentDistanceRight;
double currentDistanceLeft;

void turnRight() {
  motor1.run(rightTurnMotor1*1.5);
  motor2.run(rightTurnMotor2*1.5);
  delay(330);
}

void turnLeft() {
  motor1.run(leftTurnMotor1*1.5);
  motor2.run(leftTurnMotor2*1.5);
  delay(330);
}

void backup() {
  Serial.println("RYGGER");
  motor1.run(-200);
  motor2.run(200);
  delay(150);
}

void checkRight() {
  int tempCalculation = 0;
  for(int i = 0; i < 10; i++) {
    motor1.run(rightTurnMotor1);
    motor2.run(rightTurnMotor2);
    delay(33);
    tempCalculation = tempCalculation + calculateDistance();
  }
  currentDistanceRight = tempCalculation/10;
  Serial.println("HØYRE: ");
  Serial.print(currentDistanceRight);
  resetLeft();
}
 
void checkLeft() {
  int tempCalculation = 0;
  for(int i = 0; i < 10; i++) {
     motor1.run(leftTurnMotor1);
     motor2.run(leftTurnMotor2);
    delay(33);
    tempCalculation = tempCalculation + calculateDistance();
  }
  currentDistanceLeft = tempCalculation/10;
  Serial.println("VENSTRE: ");
  Serial.print(currentDistanceLeft);
  resetRight();
}

void resetRight() {
  motor1.run(rightTurnMotor1);
  motor2.run(rightTurnMotor2);
  delay(330);
}

void resetLeft() {
  motor1.run(leftTurnMotor1);
  motor2.run(leftTurnMotor2);
  delay(330);
}
 
double calculateDistance() {
  return ultraSensor.distanceCm();
}
 
bool checkTurnDirection() {
  Serial.println("VELGER ");
  if(currentDistanceRight > currentDistanceLeft) {
    Serial.print("HØYRE");
    return true;
  }
  Serial.print("VENSTRE");
  return false;
}
 
void logDistance() {
  Serial.print("Distance : ");
  Serial.print(ultraSensor.distanceCm() );
  Serial.println(" cm");
}

void forward() {
  motor1.run(baseSpeedMotor1); /* value: between -255 and 255. */
  motor2.run(baseSpeedMotor2); /* value: between -255 and 255. */
  delay(50); 
}
 
void setup() {
  Serial.begin(9600);
}
 
void loop() {
  //logDistance();
  double x = calculateDistance();
  x = x + 0.5;
  int distance = (int)x;
  if(distance <= 21) {
      backup();
      checkLeft();
      checkRight();
      if(checkTurnDirection()) {
          turnRight();
      } else {
          turnLeft();
      } 
  }
  forward();
}
