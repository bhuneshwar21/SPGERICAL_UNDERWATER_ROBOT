#include <Servo.h>

Servo myservo[8];

// const int CONST_POS = 90;
const int PUMP_1 = 0;
const int PUMP_2 = 2;
const int PUMP_3 = 4;
const int PUMP_4 = 6;
const int SER_PAN_1 = 0;
const int SER_PAN_2 = 2;
const int SER_PAN_3 = 4;
const int SER_PAN_4 = 6;
const int SER_TILT_1 = 1;
const int SER_TILT_2 = 3;
const int SER_TILT_3 = 5;
const int SER_TILT_4 = 7;
int ballast[2] = {48, 49};
int pump[8] = {40, 41, 42, 43, 44, 45, 46, 47};
const int CONST_POS[8] = {100,95,105,100,90,85,110,100};
int ballastTime = 5000;
const byte CONST_P = 0x37;
byte c;
int valid = 0;

void setup()
{
  Serial.begin(9600);
  Serial.println("Hello World!");
  myservo[0].attach(2);
  myservo[1].attach(3);
  myservo[2].attach(4);
  myservo[3].attach(5);
  myservo[4].attach(6);
  myservo[5].attach(7);
  myservo[6].attach(10);
  myservo[7].attach(9);
  for(int i=0; i<8; i++)
  {
    servoInit(i);
  }
  pinMode(ballast[0], OUTPUT);
  pinMode(ballast[1], OUTPUT);
  pinMode(pump[0], OUTPUT);
  pinMode(pump[1], OUTPUT);
  pinMode(pump[2], OUTPUT);
  pinMode(pump[3], OUTPUT);
  pinMode(pump[4], OUTPUT);
  pinMode(pump[5], OUTPUT);
  pinMode(pump[6], OUTPUT);
  pinMode(pump[7], OUTPUT);
}

void loop()
{
    c = Serial.read();
    
    // f1 p1 t1 f2 p2 t2 f3 p3 t3 f4 p4 t4 b1 b2
    switch (c) {
    case 'w':
      //do something when var equals 1
      actuatorCmd(0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0);
      //actuatorCmd(1, 0, 0, 0, 0, 0, 0, 0, 0);
      valid = 1;
      break;
    case 's':
      //do something when var equals 2
      actuatorCmd(1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0);
      //actuatorCmd(0, 0, 0, 1, 0, 0, 1, 0, 0);
      valid = 1;
      break;
    case 'a':
      actuatorCmd(0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0);
      //actuatorCmd(1, 0, 0, 0, 30, 0, 1, 0, 0);
      valid = 1;
      break;
    case 'd':
      actuatorCmd(1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
      //actuatorCmd(1, 0, 0, 1, 0, 0, 0, -30, 0);
      valid = 1;
      break;
    case 'i':
      actuatorCmd(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0);
      valid = 1;
      break;
    case 'k':
      actuatorCmd(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1);
      valid = 1;
      break;
    case 'j':
      actuatorCmd(1, -40, 0, 1, -40, 0, 1, -40, 0, 1, -40, 0, 0, 0);
      valid = 1;
      break;
    case 'l':
      actuatorCmd(1, 40, 0, 1, 40, 0, 1, 40, 0, 1, 40, 0, 0, 0);
      valid = 1;
      break;
    case 'q':
      actuatorCmd(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
      valid = 1;
      break;
    default: 
      //actuatorCmd(0, 0, 0, 0, 0, 0, 0, 0, 0);
      valid = 0;
  }
  // Serial.flush();
  if (valid)
  {
    Serial.write(c);
    Serial.println('!');
  }
  
//  for(int i=0; i<6; i++)
//  {
//    // servoInit(i);
//    servoSweep(i);
//    delay(1000);
//  }
//  delay(2000);
//  pumpSweep(0);
//  delay(2000);
//  pumpSweep(1);
//  delay(2000);
//  pumpSweep(2);
//  delay(2000);
//  ballastSweep(ballastTime);
}

void servoInit(int servoId)
{
  myservo[servoId].write(CONST_POS[servoId]);
}

void servoActive(int servoId, int relPos)
{
  myservo[servoId].write(CONST_POS[servoId] + relPos);
}

void pumpActive(int pumpId, int state)
{
  if(state)
  {
   digitalWrite(pump[pumpId], HIGH);
   digitalWrite(pump[pumpId+1], LOW);
  }
  else
  {
   digitalWrite(pump[pumpId], LOW);
   digitalWrite(pump[pumpId+1], LOW);
  }
}

void ballastActive(int posi, int neg)
{
  if(posi==1 && neg==0)
  {
    digitalWrite(ballast[0], HIGH);
    digitalWrite(ballast[1], LOW);
  }
  else if(posi==0 && neg==1)
  {
    digitalWrite(ballast[0], LOW);
    digitalWrite(ballast[1], HIGH);
  }
  else
  {
    digitalWrite(ballast[0], LOW);
    digitalWrite(ballast[1], LOW);
  }
  delay(10);
}

void actuatorCmd(int f1, int p1, int t1, int f2, int p2, int t2, int f3, int p3, int t3, int f4, int p4, int t4, int b1, int b2)
{
  pumpActive(PUMP_1, f1);
  pumpActive(PUMP_2, f2);
  pumpActive(PUMP_3, f3);
  pumpActive(PUMP_4, f4);
  servoActive(SER_TILT_1, t1);
  servoActive(SER_TILT_2, t2);
  servoActive(SER_TILT_3, t3);
  servoActive(SER_TILT_4, t4);
  servoActive(SER_PAN_1, p1);
  servoActive(SER_PAN_2, p2);
  servoActive(SER_PAN_3, p3);
  servoActive(SER_PAN_4, p4);
  ballastActive(b1, b2);
  delay(10);
}
