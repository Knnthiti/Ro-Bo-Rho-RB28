#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "Joy_ps2.h"

LiquidCrystal_I2C lcd(0x27, 16, 2);
ABU_Joy Joy;

byte error_PS = 1;
byte type_PS = 0;

#define PS2_DAT 19  // MISO 19
#define PS2_CMD 23  // MOSI 23
#define PS2_SEL 5   // SS   5
#define PS2_CLK 18  // SLK  18

// uint8_t broadAddress[6] = { 0x34, 0xB7, 0xDA, 0x52, 0xF3, 0xBC };  //08:D1:F9:E8:44:48
//                                                                    //34:B7:DA:52:F3:BC  esp32_s3_zero

// uint8_t broadAddress[6] = { 0xB4, 0x3A, 0x45, 0xAD, 0x5B, 0xF8 };  //ROBOT_2

uint8_t broadAddress[6] = { 0x34, 0xB7, 0xDA, 0x52, 0xF3, 0xBC };  //ROBOT_1

typedef struct __attribute__((packed)) {
  uint8_t Header[2] = { 'R', 'B' };

  union {
    uint8_t moveBtnByte;
    struct {
      uint8_t move1 : 1;  //m1
      uint8_t move2 : 1;  //m2
      uint8_t move3 : 1;  //m3
      uint8_t move4 : 1;  //m4
      uint8_t res1 : 2;
      uint8_t set1 : 1;  //s1
      uint8_t set2 : 1;  //s2
    } moveBtnBit;
  };

  union {
    uint8_t attackBtnByte;
    struct {
      uint8_t attack1 : 1;  //a1
      uint8_t attack2 : 1;  //a2
      uint8_t attack3 : 1;  //a3
      uint8_t attack4 : 1;  //a4
      uint8_t res1 : 4;
    } attackBtnBit;
  };

  int8_t stickValue[4];  //joyL_X,joyL_Y ,joyR_X,joyR_Y

} ControllerData;

ControllerData data;

void setup() {
  Serial.begin(115200);
  delay(150);

  lcd.begin();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Initializing...");

  Joy.Setup_Joy_ESPNOW(broadAddress);
  Joy.Setup_PS2(PS2_CLK, PS2_CMD, PS2_SEL, PS2_DAT);
}

void loop() {
  error_PS = Joy.PS2_error();
  type_PS = Joy.PS2_type();

  if (error_PS == 1) {
    Joy.Setup_PS2(PS2_CLK, PS2_CMD, PS2_SEL, PS2_DAT);
    return;
  }

  if (type_PS != 2) {
    Joy.set_PS2_0();
    Joy.PS2_readValue();
    Joy.print_PS2();
    lcd.clear();

    lcd.setCursor(0, 0);
    lcd.print("X:");
    lcd.print(Joy.Str_PS2.stickValues[1]);
    lcd.setCursor(5, 0);
    lcd.print(" Y:");
    lcd.print(Joy.Str_PS2.stickValues[0]);
    lcd.setCursor(10, 0);
    lcd.print(" Z:");
    lcd.print(Joy.Str_PS2.stickValues[3]);

    // data.moveBtnBit.move4 = 1;

    data.stickValue[0] = Joy.Str_PS2.stickValues[0];
    data.stickValue[1] = Joy.Str_PS2.stickValues[1];
    data.stickValue[2] = Joy.Str_PS2.stickValues[3];
    data.stickValue[3] = Joy.Str_PS2.stickValues[2];

    data.moveBtnBit.move1 = Joy.Str_PS2.attack[0];
    data.moveBtnBit.move2 = Joy.Str_PS2.attack[1];
    data.moveBtnBit.move3 = Joy.Str_PS2.attack[2];
    data.moveBtnBit.move4 = Joy.Str_PS2.attack[3];

    data.attackBtnBit.attack1 = Joy.Str_PS2.attack[4];
    data.attackBtnBit.attack2 = Joy.Str_PS2.attack[6];
    data.attackBtnBit.attack3 = Joy.Str_PS2.attack[5];
    data.attackBtnBit.attack4 = Joy.Str_PS2.attack[7];

    // Joy.Sendvalue_ESPNOW((uint8_t*)&Joy.Str_PS2, sizeof(Joy.Str_PS2));
    Joy.Sendvalue_ESPNOW((uint8_t*)&data, sizeof(data));
    delay(10);
  }
}
