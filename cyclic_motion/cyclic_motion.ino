#include <Servo.h>

Servo myservo[6];

const int CONST_POS = 90;
const int PUMP_1 = 0;
const int PUMP_2 = 1;
const int PUMP_3 = 2;
const int SER_PAN_1 = 0;
const int SER_PAN_2 = 2;
const int SER_PAN_3 = 4;
const int SER_TILT_1 = 1;
const int SER_TILT_2 = 3;
const int SER_TILT_3 = 5;
int ballast[2] = {46, 47};
int pump[3] = {49, 50, 51};
int ballastTime = 5000;
const byte CONST_P = 0x37;
byte c;
int valid = 0;
char cmds[] = {'w', 's', 'a', 'd', 'j', 'l', 'i', 'k', 'q'};
int i =0;

void setup()
{
//  Serial.begin(9600);
//  Serial.println("Hello World!");
//  Serial1.begin(9600);
//  Serial1.println("Hello World!");
  myservo[0].attach(2);
  myservo[1].attach(3);
  myservo[2].attach(4);
  myservo[3].attach(5);
  myservo[4].attach(6);
  myservo[5].attach(7);
  for(int i=0; i<6; i++)
  {
    servoInit(i);
  }
  pinMode(ballast[0], OUTPUT);
  pinMode(ballast[1], OUTPUT);
  pinMode(pump[0], OUTPUT);
  pinMode(pump[1], OUTPUT);
  pinMode(pump[2], OUTPUT);
}

void loop()
{
//    c = Serial.read();
    c=cmds[i];
    switch (c) {
    case 'w':
      //do something when var equals 1
      actuatorCmd(0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0);
      //actuatorCmd(1, 0, 0, 0, 0, 0, 0, 0, 0);
      valid = 1;
      break;
    case 's':
      //do something when var equals 2
      actuatorCmd(1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
      //actuatorCmd(0, 0, 0, 1, 0, 0, 1, 0, 0);
      valid = 1;
      break;
    case 'a':
      actuatorCmd(0, 0, 0, 1, 30, 0, 0, 0, 0, 0, 0);
      //actuatorCmd(1, 0, 0, 0, 30, 0, 1, 0, 0);
      valid = 1;
      break;
    case 'd':
      actuatorCmd(0, 0, 0, 0, 0, 0, 1, -30, 0, 0, 0);
      //actuatorCmd(1, 0, 0, 1, 0, 0, 0, -30, 0);
      valid = 1;
      break;
    case 'i':
      actuatorCmd(0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0);
      valid = 1;
      break;
    case 'k':
      actuatorCmd(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1);
      valid = 1;
      break;
    case 'j':
      actuatorCmd(1, 40, 0, 1, 40, 0, 1, 40, 0, 0, 0);
      valid = 1;
      break;
    case 'l':
      actuatorCmd(1, -40, 0, 1, -40, 0, 1, -40, 0, 0, 0);
      valid = 1;
      break;
    case 'q':
      actuatorCmd(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
      valid = 1;
      break;
    default: 
      //actuatorCmd(0, 0, 0, 0, 0, 0, 0, 0, 0);
      valid = 0;
  }
  // Serial.flush();
//  if (valid)
//  {
//    Serial.write(c);
//    Serial.println('!');
//  }
  
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
  delay(3000);
  if(i<=8)
    i = i+1;
  else
    i = 0;
}

void servoInit(int servoId)
{
  myservo[servoId].write(CONST_POS);
}

void servoActive(int servoId, int relPos)
{
  myservo[servoId].write(CONST_POS + relPos);
}

void pumpActive(int pumpId, int state)
{
  if(state)
   digitalWrite(pump[pumpId], HIGH);
  else
   digitalWrite(pump[pumpId], LOW);
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

void actuatorCmd(int f1, int p1, int t1, int f2, int p2, int t2, int f3, int p3, int t3, int b1, int b2)
{
  pumpActive(PUMP_1, f1);
  pumpActive(PUMP_2, f2);
  pumpActive(PUMP_3, f3);
  servoActive(SER_TILT_1, t1);
  servoActive(SER_TILT_2, t2);
  servoActive(SER_TILT_3, t3);
  servoActive(SER_PAN_1, p1);
  servoActive(SER_PAN_2, p2);
  servoActive(SER_PAN_3, p3);
  ballastActive(b1, b2);
  delay(10);
}
