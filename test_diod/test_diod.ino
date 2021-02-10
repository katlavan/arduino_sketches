#include "TM1637Display.h"
#define CLK 4
#define DIO 5
#define TEST_DELAY   2000

TM1637Display display(CLK, DIO);


//int led = 5;
//int button = A0;

void setup() {
//  pinMode(led, OUTPUT);
//  tm1637.init();
//  tm1637.set(BRIGHT_TYPICAL);
//  pinMode(button, INPUT_PULLUP);
  

}

void loop() {
//  if(digitalRead(button)==LOW){
    uint8_t data[] = { 0xff, 0xff, 0xff, 0xff };
    display.setBrightness(0x0f);
    display.setSegments(data);
  delay(TEST_DELAY);
    data[0] = display.encodeDigit(0);
  data[1] = display.encodeDigit(1);
  data[2] = display.encodeDigit(2);
  data[3] = display.encodeDigit(3);
   display.setSegments(data);
  delay(TEST_DELAY);
display.clear();
  display.setSegments(data+2, 2, 2);
  delay(TEST_DELAY);
//  tm1637.clearDisplay();
//  tm1637.display(3, TEST); 
//  }

}
