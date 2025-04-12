#include <espnow_ROBOT.h>

ESPNOW_ROBOT ROBOT;

typedef struct __attribute__((packed)) {
  uint8_t Header[2];

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
 
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&data, incomingData, sizeof(data));
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
  Serial.println("");
}
 
void setup() {
  ROBOT.Setup_receive_ESPNOW();
  // Register callback function
  esp_now_register_recv_cb(OnDataRecv);
}
 
void loop() {
 
}