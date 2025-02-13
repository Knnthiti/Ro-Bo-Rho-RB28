#include <espnow_ROBOT.h>

ESPNOW_ROBOT ROBOT;


uint8_t move[4] = { 0, 0, 0, 0 };

void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&move, incomingData, sizeof(move));
  // Serial.print("move ");
  //   for (int i = 0; i < 4; ++i) {
  //     Serial.print(Data.move[i]);
  //     Serial.print(" ");
  //   }
  // Serial.println(" ");
  Serial.write((uint8_t *)&move, sizeof(move));
  delay(20);
}

void setup() {
  ROBOT.Setup_receive_ESPNOW();
  Serial.begin(115200 ,SERIAL_8N1 ,44 ,43);
  // Register callback function
  esp_now_register_recv_cb(OnDataRecv);
}

void loop() {
  // put your main code here, to run repeatedly:

}
