#include <LiquidCrystal.h>
#include <Servo.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
Servo myservo;

void setup() {
  lcd.begin(16,2);
  myservo.attach(9);
}

void loop() {
  lcd.setCursor(0,0);
  lcd.print("Hello BIEN 010!");
  lcd.setCursor(0,1);
  lcd.print(millis()/1000);
//  myservo.write(0);
//  delay(1000);
//  myservo.write(180);
//  delay(1000);
}
