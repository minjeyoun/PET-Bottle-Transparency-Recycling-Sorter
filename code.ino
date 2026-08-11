#include <SoftwareSerial.h>
#include <Adafruit_NeoPixel.h>
#include <Servo.h>
#include "HX711.h"
#include <LiquidCrystal_I2C.h>

#define LED 12

#define BT_RXD 7
#define BT_TXD 6
SoftwareSerial BTSerial(BT_TXD, BT_RXD);

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(1, LED, NEO_RGB + NEO_KHZ800);

int LightsensorPin = 8;
int IRsensorPin = 9;
int servoPin = 2;
bool power = false;
Servo Servo;
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Serial.begin(9600);                          // 시리얼 모니터
  BTSerial.begin(9600);                        // 핸드폰 모니터
  pixels.begin();
  pixels.show();                               //LED
  pinMode(LightsensorPin, INPUT);              //라이트 센서
  pinMode(IRsensorPin, INPUT);                 //IR 센서
  Servo.attach(servoPin);                      //서보모터
  lcd.init();
  lcd.backlight();
  lcd.clear();                                  //LCD
}

void loop() {
  
  int Light_S_P = digitalRead(LightsensorPin);
  int Ir_S_P = digitalRead(IRsensorPin);
  char State;

  if (BTSerial.available()) {
    State = BTSerial.read();
  }
  if (Serial.available()) {
    BTSerial.write(Serial.read());
  }
  if(State == 'T') power = true;
  else if(State == 'F') power = false;

  
  if (power) {                                           // power = true
    lcd.backlight();                                     // LCD ON
    
    if (Light_S_P == 0 && Ir_S_P == 1) {                 // 평소
      pixels.setPixelColor(0, 0, 0, 0);
      pixels.show();                                     // LED 꺼짐
      Servo.write(3);                                    // 서보 작동 x
      lcd.clear();                                       // LCD 작동 x
      
      delay(100);
    }

    else if (Light_S_P == 0 && Ir_S_P == 0) {            // 투명 페트병
      pixels.setPixelColor(0, 255, 0, 0);
      pixels.show();                                     // LED 초록
      Servo.write(90);                                   // 서보 작동 o
      lcd.clear();                                  
      lcd.print(" PASS ");
      lcd.setCursor(1, 1);
      lcd.print(" Transparent ");                        // LCD 
      BTSerial.println(" Great Job! ");                  // 블루투스로 전송
      delay(6000);
    }

    else if (Light_S_P == 1 && Ir_S_P == 0) {            // 유색 페트병
      pixels.setPixelColor(0, 0, 255, 0);
      pixels.show();                                     // LED 빨강
      Servo.write(0);                                    // 서보 작동 x
      lcd.clear();
      lcd.print(" Block ");
      lcd.setCursor(1, 1);
      lcd.print(" Colored ");                            // LCD
      BTSerial.println(" Refusal! ");                    // 블루투스로 전송
      delay(3000);
    }
  }
  else {                                                 // power = false
    pixels.setPixelColor(0, 0, 0, 0);                    // LED off
    pixels.show();   
    delay(3000);
    lcd.noBacklight();                                   // LCD off
  }
}
