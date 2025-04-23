#include <espnow_ROBOT.h>

#define Joy_1

#ifdef Joy_1
uint8_t broadAddress[6] = { 0x34, 0xB7, 0xDA, 0x52, 0xF3, 0xBC };  //ROBOT_1
#else
uint8_t broadAddress[6] = { 0xB4, 0x3A, 0x45, 0xAD, 0x5D, 0xC4 };  //ROBOT_2
#endif

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

  OLED_Setup();
}

void loop() {
  // ReadValue(value_);
  ReadValue(data.stickValue);

  ReadButton();

  Serial_print();

  OLED_print();
  // OLED_Display();

  delay(10);

  joy.Sendvalue_ESPNOW((uint8_t*)&data, sizeof(data));
}