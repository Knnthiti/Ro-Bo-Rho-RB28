#include "driver/gpio.h"

void SetupGPIO_PULLUP() {
  gpio_config_t io_conf = {};
  io_conf.intr_type = GPIO_INTR_DISABLE;
  io_conf.mode = GPIO_MODE_INPUT;

  // รวมหลายพินไว้ใน pin_bit_mask
  io_conf.pin_bit_mask = (1ULL << GPIO_NUM_15) | (1ULL << GPIO_NUM_13) | (1ULL << GPIO_NUM_12) | (1ULL << GPIO_NUM_14) | (1ULL << GPIO_NUM_2) | (1ULL << GPIO_NUM_4) | (1ULL << GPIO_NUM_27) | (1ULL << GPIO_NUM_26) | (1ULL << GPIO_NUM_25) | (1ULL << GPIO_NUM_18);

  io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
  io_conf.pull_up_en = GPIO_PULLUP_ENABLE;

  gpio_config(&io_conf);
}