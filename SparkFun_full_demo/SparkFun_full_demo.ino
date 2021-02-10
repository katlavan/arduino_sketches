//Include necessary libraries for compilation
#include <SPI.h>
#include <SD.h>
#include <SoftwareSerial.h>
#include <Canbus.h>

//Initialize uSD pins
const int chipSelect = 9;


//Initialize lcd pins
SoftwareSerial lcd(3, 6);

//Initialize GPS pins
SoftwareSerial uart_gps(4,5);

// Define Joystick connection pins 
#define UP     A1
#define DOWN   A3
#define LEFT   A2
#define RIGHT  A5
#define CLICK  A4

//Define LED pins
#define LED2 8
#define LED3 7

//Define baud rates. GPS should be slower than serial to ensure valid sentences coming through
#define GPSRATE 4800
#define LCD_Rate 115200

//Create instance of TinyGPS
//    TinyGPS gps;

//Declare prototype for TinyGPS library functions
//    void getgps(TinyGPS &gps);

//Declare GPS variables
//float latitude;
//float longitude;
//int year;
//byte month;
//byte day;
//byte hour;
//byte minute;
//byte second;
//byte hundredths;
//float gps_speed;


//Declare SD File
File dataFile;

//Declare CAN variables for communication
char *EngineRPM;
char buffer[64];  //Data will be temporarily stored to this buffer before being written to the file

//Define LCD Positions
#define COMMAND 0xFE
#define CLEAR   0x01
#define LINE1  0x80
#define LINE2  0xC0


//********************************Setup Loop*********************************//
void setup() {
//Initialize Serial communication for debugging
 Serial.begin(9600);
Serial.println("ECU Demo");

//Begin LCD serial communication
//lcd.begin(9600);

//Begin GPS communcation
//uart_gps.begin(GPSRATE);

//Initialize pins as necessary
pinMode(chipSelect, OUTPUT);
pinMode(CLICK,INPUT);
pinMode(LED2, OUTPUT);
pinMode(LED3, OUTPUT);

//Pull analog pins high to enable reading of joystick movements
digitalWrite(CLICK, HIGH);

//Write LED pins low to turn them off by default
digitalWrite(LED2, LOW);
digitalWrite(LED3, LOW);

//Initialize CAN Controller 
if(Canbus.init(CANSPEED_500))  /* Initialize MCP2515 CAN controller at the specified speed */
{
//  clear_lcd();
//  lcd.print("CAN Init ok");
  Serial.println("CAN Init Ok");
  delay(1500);
} 
else
{
//  lcd.print("Can't init CAN");
  Serial.println("Can't init CAN");
  return;
} 

 //Check if uSD card initialized
if (!SD.begin(chipSelect)) {
  Serial.println("uSD card failed to initialize, or is not present");
//  clear_lcd();
//  lcd.print("uSD failed.");
  return;
}
else{
    Serial.println("uSD card initialized.");
//    clear_lcd();
//    lcd.print("uSD success!");
    delay(1500);
} 

//Print menu to LCD screen
//clear_lcd();
//lcd.print("Click to begin");
//lcd.write(COMMAND);
//lcd.write(LINE2);
//lcd.print("Logging Data");

while(digitalRead(CLICK)==HIGH)
{
   //Wait for user to click joystick to begin logging
}

delay(1000); 

}

//********************************Main Loop*********************************//
void loop(){

while(digitalRead(CLICK)==HIGH){
  
    digitalWrite(LED3, HIGH); //Turn on LED to indicate CAN Bus traffic
    
    Canbus.ecu_req(ENGINE_RPM,buffer); //Request engine RPM
    EngineRPM = buffer;
    Serial.print("Engine RPM: "); //Uncomment for Serial debugging
    Serial.println(buffer);
    delay(100);
   
    
    digitalWrite(LED3, LOW); //Turn off LED3
    delay(500);
    
  File  dataFile = SD.open("data.txt", FILE_WRITE); //Open uSD file to log data
    
    //If data file can't be opened, throw error.
    if (!dataFile){
      Serial.print("Error opening");
//        clear_lcd();
      
//      lcd.print("Error opening");
//      lcd.write(COMMAND);
//      lcd.write(LINE2);
//      lcd.print("data.txt");
      while(1);
      }
      
//      clear_lcd();
      Serial.print("Logging.Click");
      Serial.print(COMMAND);
      Serial.print(LINE2);
      Serial.print("to stop logging");
//      lcd.print("Logging.Click");
//      lcd.write(COMMAND);
//      lcd.write(LINE2);
//      lcd.print("to stop logging");
      
//      if(uart_gps.available())     // While there is data on the RX pin...
//         {
//           digitalWrite(LED2, HIGH); //Signal on D8 that GPS data received.
//           
//           //Print Latitude/Longitude to SD card
//           dataFile.print("Lat/Long: "); 
//           dataFile.print(latitude,5); 
//           dataFile.print(", "); 
//           dataFile.println(longitude,5);
//           
//            // Print data and time to SD card
//           dataFile.print("Date: "); dataFile.print(month, DEC); dataFile.print("/"); 
//           dataFile.print(day, DEC); dataFile.print("/"); dataFile.print(year);
//           dataFile.print("  Time: "); dataFile.print(hour, DEC); dataFile.print(":"); 
//           dataFile.print(minute, DEC); dataFile.print(":"); dataFile.print(second, DEC); 
//           dataFile.print("."); dataFile.println(hundredths, DEC);
//           
//            //Print GPS speed to SD card
//            dataFile.print("GPS Speed(kmph): ");
//            dataFile.println(gps_speed);
//            
//           digitalWrite(LED2, LOW); //Turn off D8 LED. 
//         }
//      
      dataFile.print("Engine RPM: "); 
      dataFile.println(EngineRPM);
      
      dataFile.println();
      dataFile.flush();
      dataFile.close();   //Close data logging file
    }
    Serial.print("Logging stopped.");
//    clear_lcd();
//    lcd.print("Logging stopped.");
    
    while(1); //Stop logging if joystick is clicked
    
  }
  
  //********************************LCD Functions*********************************//
//  void clear_lcd(void)
//  {
//    lcd.write(COMMAND);
//    lcd.write(CLEAR);
//  } 
//  
  //********************************GPS Functions*********************************//
//  void getgps(TinyGPS &gps)
//  {
//    // Receive GPS latitude/longitude
//    gps.f_get_position(&latitude, &longitude);
//   
//    //Call function to receive date and time from GPS
//    gps.crack_datetime(&year,&month,&day,&hour,&minute,&second,&hundredths);
//   
//    //Also collect gps_speed
//    gps_speed = gps.f_speed_kmph();
//  
//  }
