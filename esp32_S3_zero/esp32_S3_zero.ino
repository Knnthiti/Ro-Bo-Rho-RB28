#include <espnow_ROBOT.h>
#include <HardwareSerial.h>

ESPNOW_ROBOT ROBOT;

struct ControllerData {
    uint8_t move[4];
    uint8_t attack[8];
    uint8_t seting[2];
    uint8_t stickValues[4];
} Str_PS2;

volatile bool newData = false;  // Flag for new data

void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&Str_PS2, incomingData, len);
  newData = true;
}

void setup() {
  Serial0.begin(115200, SERIAL_8N1, 44, 43);
  
  ROBOT.Setup_receive_ESPNOW();
  esp_now_register_recv_cb(OnDataRecv);
}

void loop() {
  if (newData) {
  Serial.print("move ");
  for (int i = 0; i < 4; ++i) {
    Serial.print(Str_PS2.move[i]);
    Serial.print(" ");
  }

  Serial.print(" attack ");
  for (int i = 0; i < 8; ++i) {
    Serial.print(Str_PS2.attack[i]);
    Serial.print(" ");
  }

  Serial.print(" seting ");
  for (int i = 0; i < 2; ++i) {
    Serial.print(Str_PS2.seting[i]);
    Serial.print(" ");
  }

  Serial.print(" stickValues ");
  for (int i = 0; i < 4; ++i) {
    Serial.print(Str_PS2.stickValues[i]);
    Serial.print(" ");
  }
  Serial.println(" ");

  // Serial_0.write((uint8_t *)&Str_PS2, sizeof(Str_PS2));
  Serial0.write((uint8_t *)&Str_PS2, sizeof(Str_PS2));
    newData = false;
  }
}
