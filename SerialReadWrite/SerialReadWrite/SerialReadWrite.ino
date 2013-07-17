#include <Serial.h>

void setup()  
{
 // Open serial communications and wait for port to open:
  Serial.begin(9600);
   while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
  Serial.println("Hello World!");
}

void loop() // run over and over
{
  if (Serial.available())
  {
    Serial.write(Serial.read());
    Serial.println('!');
  }  
}
