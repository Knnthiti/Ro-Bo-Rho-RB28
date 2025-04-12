#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>

#include <driver/adc.h>

#include <espnow_ROBOT.h>

// OLED Display object
Adafruit_SH1106G display = Adafruit_SH1106G(128, 64, &Wire);

// uint8_t broadAddress[6] = { 0x34, 0xB7, 0xDA, 0x52, 0xF3, 0xBC };
uint8_t broadAddress[6] = { 0xF4, 0x65, 0x0B, 0x55, 0xD0, 0xCC };
ESPNOW_ROBOT joy(broadAddress);


typedef struct __attribute__((packed)) {
  uint8_t Header[2] = {68 ,56};

  union {
    uint8_t moveBtnByte;
    struct {
      uint8_t move1 : 1;
      uint8_t move2 : 1;
      uint8_t move3 : 1;
      uint8_t move4 : 1;
      uint8_t res1 : 2;
      uint8_t set1 : 1;
      uint8_t set2 : 1;
    } moveBtnBit;
  };

  union {
    uint8_t attackBtnByte;
    struct {
      uint8_t attack1 : 1;
      uint8_t attack2 : 1;
      uint8_t attack3 : 1;
      uint8_t attack4 : 1;
      uint8_t res1 : 4;
    } attackBtnBit;
  };

  int8_t stickValue[4];  //joyL_X,joyL_Y ,joyR_X,joyR_Y

} ControllerData;

ControllerData data;

// int16_t value_[4] = { 0 };

void setup() {
  //setup_ADC
  SetupADC();

  pinMode(15, INPUT_PULLUP);
  pinMode(14, INPUT_PULLUP);
  pinMode(27, INPUT_PULLUP);
  pinMode(26, INPUT_PULLUP);
  pinMode(25, INPUT_PULLUP);
  pinMode(18, INPUT_PULLUP);

  Serial.begin(115200);

  //Setup_espnow
  joy.Setup_send_ESPNOW();

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

void loop() {
  // ReadValue(value_);
  ReadValue(data.stickValue);

  data.moveBtnBit.move1 = digitalRead(15);
  data.moveBtnBit.move2 = digitalRead(14);
  data.moveBtnBit.move1 = digitalRead(27);
  data.moveBtnBit.move1 = digitalRead(26);

  data.moveBtnBit.set1 = digitalRead(25);
  data.moveBtnBit.set2 = digitalRead(18);

  Serial_print();
  OLED_print();

  delay(10);
  
  joy.Sendvalue_ESPNOW((uint8_t*)&data, sizeof(data));
}