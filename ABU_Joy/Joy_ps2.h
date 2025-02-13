#ifndef Joy_ps2
#define Joy_ps2

#include <Arduino.h>
#include <PS2X_lib.h>

#ifdef CONFIG_IDF_TARGET_ESP32
#include <esp_now.h>
#include <WiFi.h>
class Joy : public PS2X {
public:
  boolean move[4];
  boolean attack[8];
  boolean seting[2];
  int8_t stickValues[4];

  boolean prevMove[4] = {0, 0, 0, 0};
  boolean prevStartState = false;
  boolean prevModeState = false;

  struct ControllerState {
    int16_t xCount;
    int16_t yCount;
    bool start;
    uint8_t mode;
    uint8_t servo1;
    uint8_t servo2;
    int16_t stick[4];
  } state;

  uint8_t error = 1;
  uint8_t type = 0;
  uint8_t vibrate = 0;

  struct ControllerData {
    boolean move[4];
    boolean attack[8];
    boolean seting[2];
    int8_t stickValues[4];
  } Str_PS2;

  Joy() {}

  void structToArray();
  void Setup_PS2(uint8_t _clk, uint8_t _cmd, uint8_t _att, uint8_t _dat);
  uint8_t PS2_error();
  uint8_t PS2_type();
  void set_PS2_0();
  void PS2_readValue();
  void print_PS2();
};

class ABU_Joy : public Joy {
public:
  esp_now_peer_info_t peerInfo;
  uint8_t broadcastAddress[6];

  void Setup_Joy_ESPNOW(const uint8_t broadAddress[]);
  void Sendvalue_ESPNOW(uint8_t *data, size_t len);
  void Joy_Sendvalue_ESPNOW();
};

#endif
#endif
