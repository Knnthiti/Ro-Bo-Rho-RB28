#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>

// OLED Display object
Adafruit_SH1106G display = Adafruit_SH1106G(128, 64, &Wire);

#include <espnow_ROBOT.h>

uint8_t broadAddress[6] = { 0x34, 0xB7, 0xDA, 0x52, 0xF3, 0xBC }; //ROBOT_1
// uint8_t broadAddress[6] = { 0xB4, 0x3A, 0x45, 0xAD, 0x5D, 0xC4 }; //ROBOT_2

ESPNOW_ROBOT joy(broadAddress);


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

int16_t value_[4] = { 0 };

void setup() {
  //setup_ADC
  SetupADC();

  //Setup_GPIO
  SetupGPIO_PULLUP();

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

  data.moveBtnBit.move1 = gpio_get_level((gpio_num_t)GPIO_NUM_15); //digitalRead(15);
  data.moveBtnBit.move2 = gpio_get_level((gpio_num_t)GPIO_NUM_13); //digitalRead(13);
  data.moveBtnBit.move3 = gpio_get_level((gpio_num_t)GPIO_NUM_12); //digitalRead(12);
  data.moveBtnBit.move4 = gpio_get_level((gpio_num_t)GPIO_NUM_14); //digitalRead(14);

  data.moveBtnBit.set1 = gpio_get_level((gpio_num_t)GPIO_NUM_2);   //digitalRead(2);
  data.moveBtnBit.set2 = gpio_get_level((gpio_num_t)GPIO_NUM_4);   //digitalRead(4);

  Serial_print();
  OLED_print();

  // drawControllerDisplay();

  delay(10);

  joy.Sendvalue_ESPNOW((uint8_t*)&data, sizeof(data));
}