
#include <Servo.h>

Servo myservo;
int potPin1 = 0;
int val = 0;

void setup() 
{ 
  myservo.attach(3);
} 

void loop() 
{ 
  val = analogRead(potPin1);
  val = map(val,0 , 1023, 0, 360);
  myservo.write(val);
  delay(20);
} 
