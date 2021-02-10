#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,20,4);  
int led = 3;

void setup()
{
  lcd.init();                     
  lcd.backlight();// Включаем подсветку дисплея
  lcd.print("ALENA I LOVE YOU");
  lcd.setCursor(8, 1);
  lcd.print("LCD 2004");
  pinMode(led, OUTPUT);
}
void loop()
{
  // Устанавливаем курсор на вторую строку и нулевой символ.
  lcd.setCursor(0, 1);
  // Выводим на экран количество секунд с момента запуска ардуины
  lcd.print(millis()/1000);

  if(millis()/1000 % 2 == 0) {
     digitalWrite(led, HIGH);
  }

  if(millis()/1000 % 3 == 0) {
    digitalWrite(led, LOW);
    }
}
