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

bool prevButtonState = 0; // เก็บสถานะปุ่มก่อนหน้า
bool currButtonState = 0;

uint8_t broadAddress[6] = { 0x34, 0xB7, 0xDA, 0x52, 0xF3, 0xBC };  //08:D1:F9:E8:44:48
                                                                   //34:B7:DA:52:F3:BC  esp32_s3_zero

uint8_t move[4] = { 0, 0, 0, 0 };

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
    
  currButtonState = Joy.state.mode; // อ่านสถานะปุ่ม
    // ตรวจจับการกดปุ่มเพื่อเปลี่ยนโหมด
  if (prevButtonState == 0 && currButtonState == 1) {
    lcd.clear(); // ล้างหน้าจอ LCD
    lcd.setCursor(3, 0);
    lcd.print("Auto Mode");
    delay(1500); // หน่วงเวลาแสดงจอ LCD
  }else if(prevButtonState == 1 && currButtonState == 0){
    lcd.clear(); // ล้างหน้าจอ LCD
    lcd.setCursor(2, 0);
    lcd.print("Manual Mode");
    delay(1500); // หน่วงเวลาแสดงจอ LCD
  }
  prevButtonState = currButtonState; // อัปเดตสถานะปุ่ม

    if (Joy.state.mode == 0) {
      lcd.setCursor(0, 0);
      lcd.print("X:");
      lcd.print(Joy.state.stick[1]);
      lcd.setCursor(5, 0);
      lcd.print(" Y:");
      lcd.print(Joy.state.stick[0]);
      lcd.setCursor(10, 0);
      lcd.print(" Z:");
      lcd.print(Joy.state.stick[3]);
    } 
    // else if (Joy.state.mode == 1) {
    //   lcd.setCursor(0, 0);
    //   lcd.print("X:");
    //   lcd.print(Joy.state.xCount);
    //   lcd.print(" Y:");
    //   lcd.print(Joy.state.yCount);
    //   lcd.print(Joy.state.start ? " On" : " Off");
    // }

    // lcd.setCursor(0, 1);
    // lcd.print("SV1 :");
    // lcd.print(Joy.state.servo1);
    // lcd.print(" SV2 :");
    // lcd.print(Joy.state.servo2);

    move[0] = Joy.state.stick[0];
    move[1] = Joy.state.stick[1];
    move[2] = Joy.state.stick[2];
    move[3] = Joy.state.stick[3];

    Joy.Sendvalue_ESPNOW((uint8_t*)&move, sizeof(move));
    delay(10);

    // if(Joy.state.mode == 0){
    //   Joy.state.xCount = 0;
    //   Joy.state.yCount = 0;
    // }
  }
}
