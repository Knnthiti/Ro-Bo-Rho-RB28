#include <Adafruit_SH110X.h>
#include <Adafruit_GFX.h>
#include <Wire.h>

Adafruit_SH1106G display = Adafruit_SH1106G(128, 64, &Wire);

char Movement_Rad_buffer[8];

void Movement_Y_Axis_Starting_Point(int x_axis, int y_axis, int8_t value) {
  display.drawRect(x_axis, y_axis - 18 , 7, 37, SH110X_WHITE);
  for (uint8_t i = 0; i < 7; i++) {
    display.drawPixel(x_axis + i, y_axis, SH110X_WHITE);
  }
}

void Movement_Y_Axis_Parameters(int x_axis, int y_axis, int8_t value) {
  int Bar_Length = map(value, 100, -100, -18, 18);
  if (Bar_Length > 0) {
    display.fillRect(x_axis, y_axis, 5, Bar_Length, SH110X_WHITE);
  } else {
    display.fillRect(x_axis, y_axis + Bar_Length, 5, abs(Bar_Length), SH110X_WHITE);
  }
}

void Movement_X_Axis_Parameters(int x_axis, int y_axis, int8_t value) {
  int Bar_Length = map(value, 100, -100, -22, 22);
  if (Bar_Length > 0) {
    display.fillRect(x_axis, y_axis, Bar_Length, 5, SH110X_WHITE);
  } else {
    display.fillRect(x_axis + Bar_Length, y_axis, abs(Bar_Length), 5, SH110X_WHITE);
  }
}

void Movement_X_Axis_Starting_Point(int x_axis, int y_axis, int8_t value) {
  display.drawRect(x_axis - 22, y_axis, 45, 7, SH110X_WHITE);
  for (uint8_t i = 0; i < 7; i++) {
    display.drawPixel(x_axis, y_axis + i, SH110X_WHITE);
  }
}

void Button_Active_Display(String Button) {
  if (Button == "A1") {
    display.fillRect(18, 46, 3, 3, SH110X_WHITE);
  } else if (Button == "A2") {
    display.fillRect(18, 59, 3, 3, SH110X_WHITE);
  } else if (Button == "A3") {
    display.fillRect(50, 46, 3, 3, SH110X_WHITE);
  } else if (Button == "A4") {
    display.fillRect(50, 59, 3, 3, SH110X_WHITE);
  } else if (Button == "M1") {
    display.fillRect(82, 46, 3, 3, SH110X_WHITE);
  } else if (Button == "M2") {
    display.fillRect(82, 59, 3, 3, SH110X_WHITE);
  } else if (Button == "M3") {
    display.fillRect(114, 46, 3, 3, SH110X_WHITE);
  } else if (Button == "M4") {
    display.fillRect(114, 59, 3, 3, SH110X_WHITE);
  }
}

void Button_Deactive_Display(String Button) {
  if (Button == "A1") {
    display.fillRect(18, 46, 3, 3, SH110X_BLACK);
  } else if (Button == "A2") {
    display.fillRect(18, 59, 3, 3, SH110X_BLACK);
  } else if (Button == "A3") {
    display.fillRect(50, 46, 3, 3, SH110X_BLACK);
  } else if (Button == "A4") {
    display.fillRect(50, 59, 3, 3, SH110X_BLACK);
  } else if (Button == "M1") {
    display.fillRect(82, 46, 3, 3, SH110X_BLACK);
  } else if (Button == "M2") {
    display.fillRect(82, 59, 3, 3, SH110X_BLACK);
  } else if (Button == "M3") {
    display.fillRect(114, 46, 3, 3, SH110X_BLACK);
  } else if (Button == "M4") {
    display.fillRect(114, 59, 3, 3, SH110X_BLACK);
  }
}

void OLED_Setup() {
  if (!display.begin(0x3C, true)) {
    Serial.println("OLED not found");
    while (1)
      ;
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SH110X_WHITE);
  display.setCursor(0, 0);
  display.println("OLED Ready...");
  display.display();
  delay(1000);
}

void OLED_Display() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SH110X_WHITE);
  display.setCursor(0, 0);
  display.println("LX :");
  Movement_Y_Axis_Starting_Point(32, 18, SH110X_WHITE);

  display.setCursor(0, 14);
  display.println("COMM");
  display.drawRect(8, 26, 8, 8, SH110X_WHITE);
  if(status_ESPNOW_Sent == 1){
    display.fillRect(10, 28, 4, 4, SH110X_WHITE);
  }

  display.setCursor(50, 0);
  display.println("LY :");
  Movement_X_Axis_Starting_Point(100, 0, SH110X_WHITE);

  display.setCursor(50, 14);
  display.println("RY :");
  Movement_X_Axis_Starting_Point(100, 14, SH110X_WHITE);

  display.setCursor(50, 28);
  display.println("RX :");
  /////////////////////////////////////////////////////////////////////////
  // Movement_X_Axis_Starting_Point(100, 28, SH110X_WHITE);

  display.setCursor(90, 28);
  sprintf(Movement_Rad_buffer, "%d", _Degree);
  display.println(Movement_Rad_buffer);
  ////////////////////////////////////////////////////////////////////////

  display.setCursor(0, 44);
  display.println("A1");
  display.drawRect(16, 44, 7, 7, SH110X_WHITE);

  display.setCursor(0, 57);
  display.println("A2");
  display.drawRect(16, 57, 7, 7, SH110X_WHITE);

  display.setCursor(32, 44);
  display.println("A3");
  display.drawRect(48, 44, 7, 7, SH110X_WHITE);

  display.setCursor(32, 57);
  display.println("A4");
  display.drawRect(48, 57, 7, 7, SH110X_WHITE);

  display.setCursor(64, 44);
  display.println("M1");
  display.drawRect(80, 44, 7, 7, SH110X_WHITE);

  display.setCursor(64, 57);
  display.println("S1");
  display.drawRect(80, 57, 7, 7, SH110X_WHITE);

  display.setCursor(96, 44);
  display.println("M3");
  display.drawRect(112, 44, 7, 7, SH110X_WHITE);

  display.setCursor(96, 57);
  display.println("M4");
  display.drawRect(112, 57, 7, 7, SH110X_WHITE);

  if(data.moveBtnBit.move1 == 1){
    Button_Active_Display("M1");
  }
  if(data.moveBtnBit.set1 == 1){
    Button_Active_Display("M2");
  }
  if(data.moveBtnBit.move3 == 1){
    Button_Active_Display("M3");
  }
  if(data.moveBtnBit.move4 == 1){
    Button_Active_Display("M4");
  }

  if(data.attackBtnBit.attack1 == 1){
    Button_Active_Display("A1");
  }
  if(data.attackBtnBit.attack2 == 1){
    Button_Active_Display("A2");
  }
  if(data.attackBtnBit.attack3 == 1){
    Button_Active_Display("A3");
  }
  if(data.attackBtnBit.attack4 == 1){
    Button_Active_Display("A4");
  }
  

  Movement_Y_Axis_Parameters(33, 18  ,data.stickValue[0]);
  Movement_X_Axis_Parameters(100, 1  ,data.stickValue[1]);
  Movement_X_Axis_Parameters(100, 15 ,data.stickValue[3]);

  // Movement_X_Axis_Parameters(100, 29 ,data.stickValue[2]);
  display.display();
}