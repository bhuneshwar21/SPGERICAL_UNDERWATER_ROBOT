#include <Servo.h>

Servo myservo[8];
int pos[8] = {100,95,105,100,90,85,110,100};
int pin[8] = {2,3,4,5,6,7,10,9};
byte c;
int off = 5;
int valid = 0;
void setup()
{
  Serial.begin(9600);
  Serial.println("Hello World!");
  for(int i=0; i<8; i++)
  {
    myservo[i].attach(pin[i]);
    myservo[i].write(pos[i]);
    delay(100);
  }
  pinMode(40, OUTPUT);
  pinMode(41, OUTPUT);
  pinMode(42, OUTPUT);
  pinMode(43, OUTPUT);
  pinMode(44, OUTPUT);
  pinMode(45, OUTPUT);
  pinMode(46, OUTPUT);
  pinMode(47, OUTPUT);
  pinMode(48, OUTPUT);
  pinMode(49, OUTPUT);
}

void loop()
{
  c = Serial.read();
  switch(c) {
    // servo 1 pan and tilt
    case 'q':
      pos[0] = pos[0] + off;
      myservo[0].write(pos[0]);
      valid = 1;
      break;
    case 'a':
      pos[0] = pos[0] - off;
      myservo[0].write(pos[0]);
      valid = 1;
      break;
    case 'w':
      pos[1] = pos[1] + off;
      myservo[1].write(pos[1]);
      valid = 1;
      break;
    case 's':
      pos[1] = pos[1] - off;
      myservo[1].write(pos[1]);
      valid = 1;
      break;
    // servo 2 pan and tilt
    case 'e':
      pos[2] = pos[2] + off;
      myservo[2].write(pos[2]);
      valid = 1;
      break;
    case 'd':
      pos[2] = pos[2] - off;
      myservo[2].write(pos[2]);
      valid = 1;
      break;
    case 'r':
      pos[3] = pos[3] + off;
      myservo[3].write(pos[3]);
      valid = 1;
      break;
    case 'f':
      pos[3] = pos[3] - off;
      myservo[3].write(pos[3]);
      valid = 1;
      break;
    // servo 3 pan and tilt
    case 't':
      pos[4] = pos[4] + off;
      myservo[4].write(pos[4]);
      valid = 1;
      break;
    case 'g':
      pos[4] = pos[4] - off;
      myservo[4].write(pos[4]);
      valid = 1;
      break;
    case 'y':
      pos[5] = pos[5] + off;
      myservo[5].write(pos[5]);
      valid = 1;
      break;
    case 'h':
      pos[5] = pos[5] - off;
      myservo[5].write(pos[5]);
      valid = 1;
      break;
    // servo 4 pan and tilt
    case 'u':
      pos[6] = pos[6] + off;
      myservo[6].write(pos[6]);
      valid = 1;
      break;
    case 'j':
      pos[6] = pos[6] - off;
      myservo[6].write(pos[6]);
      valid = 1;
      break;
    case 'i':
      pos[7] = pos[7] + off;
      myservo[7].write(pos[7]);
      valid = 1;
      break;
    case 'k':
      pos[7] = pos[7] - off;
      myservo[7].write(pos[7]);
      valid = 1;
      break;
    case 'x':
      digitalWrite(40, HIGH);
      digitalWrite(41, LOW);
      valid = 1;
      break;
    case 'c':
      digitalWrite(42, HIGH);
      digitalWrite(43, LOW);
      valid = 1;
      break;
    case 'v':
      digitalWrite(44, HIGH);
      digitalWrite(45, LOW);
      valid = 1;
      break;
    case 'b':
      digitalWrite(46, HIGH);
      digitalWrite(47, LOW);
      valid = 1;
      break;
    case 'X':
      digitalWrite(40, LOW);
      digitalWrite(41, LOW);
      valid = 1;
      break;
    case 'C':
      digitalWrite(41, LOW);
      digitalWrite(42, LOW);
      valid = 1;
      break;
    case 'V':
      digitalWrite(44, LOW);
      digitalWrite(45, LOW);
      valid = 1;
      break;
    case 'B':
      digitalWrite(46, LOW);
      digitalWrite(47, LOW);
      valid = 1;
      break;
    case 'n':
      digitalWrite(48, HIGH);
      digitalWrite(49, LOW);
      valid = 1;
      break;
    case 'm':
      digitalWrite(49, HIGH);
      digitalWrite(48, LOW);
      valid = 1;
      break;
    case 'N':
      digitalWrite(48, LOW);
      digitalWrite(49, LOW);
      valid = 1;
      break;
    case 'M':
      digitalWrite(49, LOW);
      digitalWrite(48, LOW);
      valid = 1;
      break;
    case 'z':
      Serial.println("Final position are:");
      for(int i=0; i<8; i++)
        Serial.println(pos[i]);
      return;
    default:    
      valid = 0;
      
  } 
  if (valid)
  {
    Serial.write(c);
    Serial.println('!');
  }
}
