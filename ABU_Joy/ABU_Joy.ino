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

uint8_t broadAddress[6] = { 0x34, 0xB7, 0xDA, 0x52, 0xF3, 0xBC };  //08:D1:F9:E8:44:48
                                                                   //34:B7:DA:52:F3:BC  esp32_s3_zero

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

    Joy.Sendvalue_ESPNOW((uint8_t*)&Joy.Str_PS2, sizeof(Joy.Str_PS2));
    // delay(10);
  }
}
