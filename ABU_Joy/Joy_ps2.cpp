#include "Joy_ps2.h"

void Joy::structToArray() {
  for (int i = 0; i < 4; ++i) move[i] = Str_PS2.move[i];
  for (int i = 0; i < 8; ++i) attack[i] = Str_PS2.attack[i];
  for (int i = 0; i < 2; ++i) seting[i] = Str_PS2.seting[i];
  for (int i = 0; i < 4; ++i) stickValues[i] = Str_PS2.stickValues[i];
}

void Joy ::Setup_PS2(uint8_t _clk, uint8_t _cmd, uint8_t _att, uint8_t _dat) {
  error = config_gamepad(_clk, _cmd, _att, _dat, true, true);
  if (error == 1) {
    Serial.println("No controller found, check wiring, see readme.txt to enable debug. Visit www.billporter.info for troubleshooting tips");
  } else if (error == 2) {
    Serial.println("Controller found but not accepting commands. See readme.txt to enable debug. Visit www.billporter.info for troubleshooting tips");
  } else if (error == 3) {
    Serial.println("Controller refusing to enter Pressures mode, may not support it.");
  }

  if (error == 0) {
    type = readType();
    switch (type) {
      case 0:
        Serial.println(" Unknown Controller type found ");
        break;
      case 1:
        Serial.println(" DualShock Controller found ");
        break;
      case 2:
        Serial.println(" GuitarHero Controller found ");
        break;
      case 3:
        Serial.println(" Wireless Sony DualShock Controller found ");
        break;
    }
  }
  delay(500);
}

byte Joy ::PS2_error() {
  return error;
}

byte Joy ::PS2_type() {
  return type;
}

void Joy::PS2_readValue() {
  if (type == 1) {
    read_gamepad(false, vibrate);
    Str_PS2.move[0] = Button(PSB_PAD_UP);
    Str_PS2.move[1] = Button(PSB_PAD_RIGHT);
    Str_PS2.move[2] = Button(PSB_PAD_DOWN);
    Str_PS2.move[3] = Button(PSB_PAD_LEFT);

    if (prevMove[0] == 1 && Str_PS2.move[0] == 0) state.xCount += 10;
    if (prevMove[2] == 1 && Str_PS2.move[2] == 0) state.xCount -= 10;
    if (prevMove[1] == 1 && Str_PS2.move[1] == 0) state.yCount -= 10;
    if (prevMove[3] == 1 && Str_PS2.move[3] == 0) state.yCount += 10;

    if (state.xCount > 500) {
      state.xCount = 500;
    } else if (state.xCount < -500) {
      state.xCount = -500;
    }

    if (state.yCount > 500) {
      state.yCount = 500;
    } else if (state.yCount < -500) {
      state.yCount = -500;
    }

    Str_PS2.attack[0] = Button(PSB_GREEN);
    Str_PS2.attack[1] = Button(PSB_RED);
    Str_PS2.attack[2] = Button(PSB_PINK);
    Str_PS2.attack[3] = Button(PSB_BLUE);

    if (Str_PS2.attack[0]) state.servo1 = min(state.servo1 + 1, 10);
    if (Str_PS2.attack[3]) state.servo1 = max(state.servo1 - 1, 0);
    if (Str_PS2.attack[1]) state.servo2 = min(state.servo2 + 1, 10);
    if (Str_PS2.attack[2]) state.servo2 = max(state.servo2 - 1, 0);

    // Toggle `start` status on/off with the START button
    Str_PS2.seting[0] = ButtonPressed(PSB_START);
    if (Str_PS2.seting[0] && !prevStartState) {
      state.start = !state.start;  // Toggle between on and off
    }
    prevStartState = Str_PS2.seting[0];

    // Cycle `mode` through 3 statuses with the SELECT button
    Str_PS2.seting[1] = ButtonPressed(PSB_SELECT);
    if (Str_PS2.seting[1] && !prevModeState) {
      state.mode = (state.mode + 1) % 2;  // Cycle through 0, 1
    }
    prevModeState = Str_PS2.seting[1];

    // state.stick[0] = map(Analog(PSS_LX), 255, 0, -100, 100);
    // state.stick[1] = map(Analog(PSS_LY), 255, 0, -100, 100);
    // state.stick[2] = map(Analog(PSS_RY), 255, 0, 100, -100);
    // state.stick[3] = map(Analog(PSS_RX), 255, 0, -100, 100);

    state.stick[0] = Analog(PSS_LX);
    state.stick[1] = Analog(PSS_LY);
    state.stick[2] = Analog(PSS_RY);
    state.stick[3] = Analog(PSS_RX);

    structToArray();
  }
}

void Joy::print_PS2() {
  prevStartState = Str_PS2.seting[1];
  for (int i = 0; i < 4; ++i) prevMove[i] = Str_PS2.move[i];
  Serial.print("xCount: ");
  Serial.print(state.xCount);
  Serial.print(" | yCount: ");
  Serial.print(state.yCount);
  Serial.print(" | servo1: ");
  Serial.print(state.servo1);
  Serial.print(" | servo2: ");
  Serial.print(state.servo2);
  Serial.print(" | start: ");
  Serial.print(state.start ? "On" : "Off");
  Serial.print(" | mode: ");
  Serial.print(state.mode);

  Serial.print(" LY: ");
  Serial.print(state.stick[0]);
  Serial.print(" ,LX: ");
  Serial.print(state.stick[1]);
  Serial.print(" ,RY: ");
  Serial.print(state.stick[2]);
  Serial.print(" ,RX: ");
  Serial.println(state.stick[3]);
}

void Joy::set_PS2_0() {
  for (int i = 0; i < 4; ++i) Str_PS2.move[i] = 0;
  for (int i = 0; i < 8; ++i) Str_PS2.attack[i] = 0;
  for (int i = 0; i < 2; ++i) Str_PS2.seting[i] = 0;
  for (int i = 0; i < 4; ++i) Str_PS2.stickValues[i] = 0;
  structToArray();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////class ABU_Joy ///////////////////////////////////////////////////////////
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success " : "Delivery Fail ");
}

void ABU_Joy ::Setup_Joy_ESPNOW(const uint8_t broadAddress[]) {
  // memcpy(&broadcastAddress, &broadAddress, sizeof(broadAddress));
  broadcastAddress[0] = broadAddress[0];
  broadcastAddress[1] = broadAddress[1];
  broadcastAddress[2] = broadAddress[2];
  broadcastAddress[3] = broadAddress[3];
  broadcastAddress[4] = broadAddress[4];
  broadcastAddress[5] = broadAddress[5];

  WiFi.mode(WIFI_STA);

  // Initilize ESP-NOW
  if (esp_now_init() != ESP_OK) {
#ifdef ESPNOW
    Serial.println("Error initializing ESP-NOW");
#endif
    return;
  }

  // Register the send callback
  esp_now_register_send_cb(OnDataSent);

  // Register peer
  memcpy(peerInfo.peer_addr, broadcastAddress, sizeof(broadcastAddress));
  peerInfo.channel = 0;
  peerInfo.encrypt = false;

  // Add peer
  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
#ifdef ESPNOW
    Serial.println("Failed to add peer");
#endif
    return;
  }
}

void ABU_Joy ::Sendvalue_ESPNOW(uint8_t *data, size_t len) {
  esp_err_t result = esp_now_send(broadcastAddress, data, len);

  if (result == ESP_OK) {
#ifdef ESPNOW
    Serial.println(" | Sending confirmed");
#endif
  } else {
#ifdef ESPNOW
    Serial.println(" | Sending error");
#endif
  }
  delay(10);  //COMMUNICATION
}

void ABU_Joy ::Joy_Sendvalue_ESPNOW() {
  esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *)&Str_PS2, sizeof(Str_PS2));

  if (result == ESP_OK) {
#ifdef ESPNOW
    Serial.println(" | Sending confirmed");
#endif
  } else {
#ifdef ESPNOW
    Serial.println(" | Sending error");
#endif
  }
  delay(10);  //COMMUNICATION
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////