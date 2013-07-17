#include <Servo.h>
#include <PID_v1.h>

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
byte c,mode='a';
int valid = 0;

int i=1;
double HeadSP = 0,tempHeadSP,Input,Output;


double aggKp=4, aggKi=0.2,aggKd=1;
double consKp=1, consKi=0.05, consKd=0.25;

PID imuPID(&Input,&Output,&HeadSP,consKp,consKi,consKd,REVERSE);
Servo imuServo[2];

void setup()
{
  Serial.begin(19200);
  delay(3000);
  Serial3.begin(19200);
  imuServo[0].attach(3);
  imuServo[1].attach(4);
  imuPID.SetMode(AUTOMATIC);
  Serial.println("PD Control of STARFISH");
  Serial.println("Obtaining Set Point");
  delay(3000);
  
  for(int j=1;j <=40;j++){
  tempHeadSP = Serial3.read();
  HeadSP = tempHeadSP + HeadSP;
  i=j;
  }
  HeadSP = HeadSP/i;
 Serial.print("SP:"),Serial.println(HeadSP);
}

void loop(){
  
//  if(Serial.read()=='#'){
//    mode = Serial.read();
//    if(mode == 'm'){
//      imuPID.SetMode(MANUAL);
//    }
//    if(mode == 'a'){
//      imuPID.SetMode(AUTOMATIC);
//    }
//  }
  
  if(mode == 'm'){
//    Serial.println("hello");
  c= Serial.read();
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
    case '#':
      mode = 'a';
      imuPID.SetMode(AUTOMATIC);
      break;
    default: 
      //actuatorCmd(0, 0, 0, 0, 0, 0, 0, 0, 0);
      valid = 0;
  }
  }
  
  
  if(mode == 'a'){
  if(Serial3.available()>0){
    if(Serial.read() == '#'){
      imuPID.SetMode(MANUAL);
      mode = 'm';
    }
  Input = Serial3.read();
  }
  double gap = abs(HeadSP - Input);
  if (gap<30)
  {
    imuPID.SetTunings(consKp, consKi, consKd);
  }
  else
  {
     imuPID.SetTunings(aggKp, aggKi, aggKd);
  }
  imuPID.Compute();
  imuServo[0].write(50*Output);
  imuServo[1].write(50*Output);
  digitalWrite(pump[1],HIGH);
  digitalWrite(pump[2],HIGH);
  
  
Serial.println(Output);
  }

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



