  
#include <Canbus.h>
#include <defaults.h>
#include <global.h>
#include <mcp2515.h>
#include <mcp2515_defs.h>
#include <SPI.h>
#include <SD.h>

const int chipSelect = 9; 
//********************************Setup Loop*********************************//

void setup() {
  
  Serial.begin(9600); // For debug use
   while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
  
  Serial.println("CAN Read - Testing receival of CAN Bus message");  
  delay(1000);
  
  if(Canbus.init(CANSPEED_500))  //Initialise MCP2515 CAN controller at the specified speed
    Serial.println("CAN Init ok");
  else
    Serial.println("Can't init CAN");
  
  Serial.print("Initializing SD card...");
  pinMode(chipSelect, OUTPUT);

  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    return;
  }
  
  Serial.println("card initialized.");
}

//********************************Main Loop*********************************//

void loop(){
  String dataString = "";
  File dataFile = SD.open("datalog.txt", FILE_WRITE);
 
  tCAN message;
if (mcp2515_check_message()) 
  {
    if ((&message) && dataFile) {  
//      int timeStamp = millis();
//      dataFile.print(timeStamp);
//      dataFile.print(" ms");
//      dataFile.print(", ");
      dataFile.print("ID: ");
      dataFile.print(message.id);
      Serial.print("ID: ");
      Serial.print(message.id,HEX);
      dataFile.print(", ");
      dataFile.print(message.id, HEX);
      dataFile.print(", ");
      dataFile.print("Data length: ");
      dataFile.print(message.header.length,DEC);
      dataFile.print(" Msg: ");
     for(int i=0;i<message.header.length;i++) 
      { 
         dataFile.print(message.data[i],HEX);
         dataFile.print(" ");
      }
       dataFile.println(); //create a new row to read data more clearly
      dataFile.close();   //close file
  
     Serial.println("");
    } else
    {
      Serial.println("error opening datalog.txt");
    } 
             
           }

}
