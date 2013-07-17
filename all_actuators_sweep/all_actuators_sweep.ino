#include <Servo.h>

Servo myservo[6];
int ballast[2] = {52, 53};
int pump[3] = {49, 50, 51};
int ballastTime = 5000;

void setup()
{
  Serial.begin(9600);
  myservo[0].attach(2);
  myservo[1].attach(3);
  myservo[2].attach(4);
  myservo[3].attach(5);
  myservo[4].attach(6);
  myservo[5].attach(7);
  pinMode(ballast[0], OUTPUT);
  pinMode(ballast[1], OUTPUT);
  pinMode(pump[0], OUTPUT);
  pinMode(pump[1], OUTPUT);
  pinMode(pump[2], OUTPUT);
}

void loop()
{
  
  for(int i=0; i<6; i++)
  {
    // servoInit(i);
    servoSweep(i);
    delay(1000);
  }
  delay(2000);
  pumpSweep(0);
  delay(2000);
  pumpSweep(1);
  delay(2000);
  pumpSweep(2);
  delay(2000);
  ballastSweep(ballastTime);
}

void servoInit(int servoId)
{
  int pos = 90;
  myservo[servoId].write(pos);
}

void servoSweep(int servoId)
{
  for(int pos=90; pos<130; pos++)
  {
    myservo[servoId].write(pos);
    delay(15);
  }
  for(int pos=130; pos>50; pos--)
  {
    myservo[servoId].write(pos);
    delay(15);
  }
  for(int pos=50; pos==90; pos++)
  {
    myservo[servoId].write(pos);
    delay(15);
  }
}

void pumpSweep(int pumpId)
{
  digitalWrite(pump[pumpId], HIGH);
  delay(3000);
  digitalWrite(pump[pumpId], LOW);
  delay(1000);
}

void ballastSweep(int bt)
{
  digitalWrite(ballast[0], LOW);
  digitalWrite(ballast[1], HIGH);
  delay(bt);
  digitalWrite(ballast[1], LOW);
  digitalWrite(ballast[0], HIGH);
  delay(bt);
}
