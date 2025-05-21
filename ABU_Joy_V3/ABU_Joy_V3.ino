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

void setup() {
  SetupADC();

  Serial.begin(115200);
}


void loop() {
  ReadValue(data.stickValue);

  Serial.print("LX: ");
  Serial.print(data.stickValue[0]);
  Serial.print(" | LY: ");
  Serial.print(data.stickValue[1]);
  Serial.print(" | RX: ");
  Serial.print(data.stickValue[2]);
  Serial.print(" | RY: ");
  Serial.print(data.stickValue[3]);
  Serial.println(" ||| ");
}
