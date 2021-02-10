#define UP     A1
#define DOWN   A3
#define LEFT   A2
#define RIGHT  A5
#define CLICK  A4


void setup() {
  //Initialize analog pins as inputs
  pinMode(UP,INPUT);
  pinMode(DOWN,INPUT);
  pinMode(LEFT,INPUT);
  pinMode(RIGHT,INPUT);
  pinMode(CLICK,INPUT);
  
  //Pull analog pins high to enable reading of joystick movements
  digitalWrite(UP, HIGH);
  digitalWrite(DOWN, HIGH);
  digitalWrite(LEFT, HIGH);
  digitalWrite(RIGHT, HIGH);
  digitalWrite(CLICK, HIGH);
 
 //Initialize serial terminal connection
  Serial.begin(9600);
  Serial.println("Joystick Demo");

}



void loop() {
  
  //Scan analog pins. If pin reads low, print the corresponding joystick movement.
   if (digitalRead(UP) == 0) {
     Serial.println("Up");}
      
   if (digitalRead(DOWN) == 0) {
      Serial.println("Down");}
      
   if (digitalRead(LEFT) == 0) {
       Serial.println("Left");}
   
   if (digitalRead(RIGHT) == 0) {
       Serial.println("Right");}

   if (digitalRead(CLICK) == 0) {
       Serial.println("Click");}      
       delay(250);

}
