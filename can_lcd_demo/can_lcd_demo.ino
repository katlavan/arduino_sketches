#include <SoftwareSerial.h> //LCD screen connects via Software Serial to 
              //prevent display corruption

// Attach the serial display's RX line to digital pin 6 for connection 
//on the CAN-Bus shield

SoftwareSerial mySerial(3,6); // pin 6 = TX, pin 3 = RX (unused)


void setup()
{
  mySerial.begin(9600); // set up serial port for 9600 baud
  delay(500); // wait for display to boot up
}

void loop()
{
  mySerial.write(254); // move cursor to beginning of first line
  mySerial.write(128);

  mySerial.write("                "); // clear display
  mySerial.write("                ");

  mySerial.write(254); // move cursor to beginning of first line
  mySerial.write(128);
 
  mySerial.write("Hello, world!");

  while(1); // wait forever
}
