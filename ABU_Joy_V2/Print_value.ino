void Serial_print() {
  // Serial.print("LX: ");    Serial.print(value_[0]);
  // Serial.print(" | LY: "); Serial.print(value_[1]);
  // Serial.print(" | RX: "); Serial.print(value_[2]);
  // Serial.print(" | RY: "); Serial.print(value_[3]);
  // Serial.print(" ||| ");

  Serial.print("LX: ");
  Serial.print(data.stickValue[0]);
  Serial.print(" | LY: ");
  Serial.print(data.stickValue[1]);
  Serial.print(" | RX: ");
  Serial.print(data.stickValue[2]);
  Serial.print(" | RY: ");
  Serial.print(data.stickValue[3]);
  Serial.print(" ||| ");

  Serial.print(data.moveBtnBit.move1);
  Serial.print(" | ");
  Serial.print(data.moveBtnBit.move2);
  Serial.print(" | ");
  Serial.print(data.moveBtnBit.move3);
  Serial.print(" | ");
  Serial.print(data.moveBtnBit.move4);
  Serial.print(" | ");
  Serial.print(data.moveBtnBit.set1);
  Serial.print(" | ");
  Serial.print(data.moveBtnBit.set2);
  Serial.print(" || ");
  Serial.print(data.attackBtnBit.attack1);
  Serial.print(" | ");
  Serial.print(data.attackBtnBit.attack2);
  Serial.print(" | ");
  Serial.print(data.attackBtnBit.attack3);
  Serial.print(" | ");
  Serial.print(data.attackBtnBit.attack4);
  Serial.println("");
}

void drawBarWithPixels(int x, int y, int8_t value) {
  int length = map(value, -100, 100, -50, 50);  // แปลงค่าเป็น -50 ถึง 50
  int midX = x + 50;                            // ตำแหน่งศูนย์กลาง

  // เส้นแกนกลาง
  for (int i = 0; i < 8; i++) {
    display.drawPixel(midX, y + i, SH110X_WHITE);
  }

  if (length < 0) {
    for (int i = 0; i < abs(length); i++) {
      for (int j = 2; j < 7; j++) {
        display.drawPixel(midX - i - 1, y + j, SH110X_WHITE);
      }
    }
  } else {
    for (int i = 0; i < length; i++) {
      for (int j = 2; j < 7; j++) {
        display.drawPixel(midX + i + 1, y + j, SH110X_WHITE);
      }
    }
  }
}

void OLED_print() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("Joystick:");

  display.print("LX:");
  drawBarWithPixels(30, 8, data.stickValue[0]);

  display.setCursor(0, 20);
  display.print("LY:");
  drawBarWithPixels(30, 20, data.stickValue[1]);

  display.setCursor(0, 32);
  display.print("RY:");
  drawBarWithPixels(30, 32, data.stickValue[3]);

  display.setCursor(0, 48);
  display.print("A1: ");
  display.print(data.attackBtnBit.attack1);
  display.setCursor(64, 48);
  display.print(" A2: ");
  display.print(data.attackBtnBit.attack2);

  display.setCursor(0, 56);
  display.print("A3: ");
  display.print(data.attackBtnBit.attack3);
  display.setCursor(64, 56);
  display.print(" A4: ");
  display.println(data.attackBtnBit.attack4);

  display.display();
}
