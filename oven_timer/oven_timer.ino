#include <LiquidCrystal.h>
#include <Servo.h>
#include <IRremote.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
Servo myservo;
int key;
int mode = 0;
String cmd;
unsigned long shutoff_time = 0;

// MODES:
//  0:  Startup; waiting for input
//  1:  Inputting the wait time
//  2:  Running, weaiting for turnoff

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  myservo.attach(9);
  IrReceiver.begin(7);
  myservo.write(0);
  lcd.setCursor(0, 0);
  lcd.print("Minutes until");
  lcd.setCursor(0, 1);
  lcd.print("shutdown? ");
}

void loop() {

  if (IrReceiver.decode()) {
    key = IrReceiver.decodedIRData.command;
    Serial.println(key);

    // STARTUP mode:
    if (mode == 0) {
      lcd.setCursor(0, 0);
      lcd.print("Minutes until");
      lcd.setCursor(0, 1);
      lcd.print("shutdown? ");
      // Check for a number:
      if (key == 22 or key == 12 or key == 24 or key == 94 or key == 8 or
          key == 28 or key == 90 or key == 66 or key == 82 or key == 74) {
        mode = 1;
      }
    }

    // INPUTTING mode:
    if (mode == 1) {
      if (key == 22) {
        cmd = cmd + "0";
      }
      if (key == 12) {
        cmd = cmd + "1";
      }
      if (key == 24) {
        cmd = cmd + "2";
      }
      if (key == 94) {
        cmd = cmd + "3";
      }
      if (key == 8) {
        cmd = cmd + "4";
      }
      if (key == 28) {
        cmd = cmd + "5";
      }
      if (key == 90) {
        cmd = cmd + "6";
      }
      if (key == 66) {
        cmd = cmd + "7";
      }
      if (key == 82) {
        cmd = cmd + "8";
      }
      if (key == 74) {
        cmd = cmd + "9";
      }
      if (key == 71) {
        shutoff_time = millis() + cmd.toInt() * 60 * 1000;
        cmd = "";
        key = 0;
        mode = 2;
      }
      else {
        lcd.setCursor(10, 1);
        lcd.print(cmd);
      }
    }

    // RUNNING MODE
    if (mode == 2) {
      if (key == 71) {
        mode = 0;
        key = 0;
      }
    }


    Serial.println(cmd);
    delay(200);
    IrReceiver.resume();
  }

  if (mode == 2) {
    if (millis() > shutoff_time) {
      myservo.write(180);
      lcd.setCursor(0,0);
      lcd.print("Oven shut down    ");
      lcd.setCursor(0, 1);
      lcd.print(((millis() - shutoff_time) / 1000));
      lcd.print(" s ago              ");
    }
    else {
      lcd.setCursor(0,0);
      lcd.print("Shutting down in");
      lcd.setCursor(0, 1);
      lcd.print(((shutoff_time - millis()) / 1000));
      lcd.print(" s                   ");
    }
  }
}
