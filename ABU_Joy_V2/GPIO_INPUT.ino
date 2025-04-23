#include "driver/gpio.h"

void SetupGPIO_PULLUP() {
  gpio_config_t io_conf = {};
  io_conf.intr_type = GPIO_INTR_DISABLE;
  io_conf.mode = GPIO_MODE_INPUT;

  // รวมหลายพินไว้ใน pin_bit_mask
  io_conf.pin_bit_mask = (1ULL << GPIO_NUM_15) | 
  (1ULL << GPIO_NUM_13) | 
  (1ULL << GPIO_NUM_12) |
  (1ULL << GPIO_NUM_14) | //Joy_1
  (1ULL << GPIO_NUM_19) | //Joy_2
  (1ULL << GPIO_NUM_2) | 
  (1ULL << GPIO_NUM_4) | 
  (1ULL << GPIO_NUM_27) | 
  (1ULL << GPIO_NUM_26) | 
  (1ULL << GPIO_NUM_25) | 
  (1ULL << GPIO_NUM_18);

  io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
  io_conf.pull_up_en = GPIO_PULLUP_ENABLE;

  gpio_config(&io_conf);
}

uint8_t toggleState[2];
uint8_t lastButtonState[2] = { 1, 1 };
long lastDebounceTime[2];  // ใช้ unsigned long ปลอดภัยกว่า

uint8_t reading[2];

#define debounceDelay 100

void ReadButton() {
  // อ่านค่าจากปุ่มที่ใช้ toggle
  reading[0] = gpio_get_level((gpio_num_t)GPIO_NUM_2);   // move1 toggle
  reading[1] = gpio_get_level((gpio_num_t)GPIO_NUM_18);  // attack1 toggle

  // อ่านค่าจากปุ่มกดตรง ๆ (ไม่ toggle)
  // data.moveBtnBit.move1 = gpio_get_level((gpio_num_t)GPIO_NUM_2);
  data.moveBtnBit.move2 = !gpio_get_level((gpio_num_t)GPIO_NUM_4);
  data.moveBtnBit.move3 = !gpio_get_level((gpio_num_t)GPIO_NUM_19);
#ifdef Joy_1
  data.moveBtnBit.move3 = !gpio_get_level((gpio_num_t)GPIO_NUM_14);;  //Joy_1
#else
  data.moveBtnBit.move3 = !gpio_get_level((gpio_num_t)GPIO_NUM_19);;  //Joy_2
#endif
  data.moveBtnBit.move4 = !gpio_get_level((gpio_num_t)GPIO_NUM_12);
  data.moveBtnBit.set1 = !gpio_get_level((gpio_num_t)GPIO_NUM_13);
  data.moveBtnBit.set2 = !gpio_get_level((gpio_num_t)GPIO_NUM_15);

  // data.attackBtnBit.attack1 = gpio_get_level((gpio_num_t)GPIO_NUM_18);
  data.attackBtnBit.attack2 = !gpio_get_level((gpio_num_t)GPIO_NUM_27);
  data.attackBtnBit.attack3 = !gpio_get_level((gpio_num_t)GPIO_NUM_25);
  data.attackBtnBit.attack4 = !gpio_get_level((gpio_num_t)GPIO_NUM_26);

  for (uint8_t i = 0; i < 2; i++) {
    if (reading[i] == 0) {
      if (reading[i] != lastButtonState[i]) {
        if ((millis() - lastDebounceTime[i]) > debounceDelay) {
          toggleState[i] = !toggleState[i];  // Toggle button

          data.moveBtnBit.move1 = toggleState[0];
          data.attackBtnBit.attack1 = toggleState[1];

          lastButtonState[i] = reading[i];
        }
      }

    } else {
      lastDebounceTime[i] = millis();
      lastButtonState[i] = reading[i];
    }
  }
}