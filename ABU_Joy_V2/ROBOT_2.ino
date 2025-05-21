uint8_t toggleState[5];
uint8_t lastButtonState[5] = { 1 };
long lastDebounceTime[5];

uint8_t reading[5];

#define debounceDelay 100

void ROBOT_2_Game_Play() {
  // อ่านค่าจากปุ่มที่ใช้ toggle
  reading[0] = gpio_get_level((gpio_num_t)GPIO_NUM_18);  // attack1 toggle
  reading[1] = gpio_get_level((gpio_num_t)GPIO_NUM_27);  // attack2 toggle
  reading[2] = gpio_get_level((gpio_num_t)GPIO_NUM_25);  // attack3 toggle
  reading[3] = gpio_get_level((gpio_num_t)GPIO_NUM_26);  // attack4 toggle

  reading[4] = gpio_get_level((gpio_num_t)GPIO_NUM_2);   // move1 toggle

  // data.moveBtnBit.move1 = !gpio_get_level((gpio_num_t)GPIO_NUM_2);
  data.moveBtnBit.move2 = !gpio_get_level((gpio_num_t)GPIO_NUM_4);
  data.moveBtnBit.move3 = !gpio_get_level((gpio_num_t)GPIO_NUM_14);

  data.moveBtnBit.move4 = !gpio_get_level((gpio_num_t)GPIO_NUM_12);
  data.moveBtnBit.set1 = !gpio_get_level((gpio_num_t)GPIO_NUM_13);
  data.moveBtnBit.set2 = !gpio_get_level((gpio_num_t)GPIO_NUM_15);

  // data.attackBtnBit.attack1 = gpio_get_level((gpio_num_t)GPIO_NUM_18);
  // data.attackBtnBit.attack2 = !gpio_get_level((gpio_num_t)GPIO_NUM_27);
  // data.attackBtnBit.attack3 = !gpio_get_level((gpio_num_t)GPIO_NUM_25);
  // data.attackBtnBit.attack4 = !gpio_get_level((gpio_num_t)GPIO_NUM_26);

  for (uint8_t i = 0; i < 5; i++) {
    if (reading[i] == 0) {
      if (reading[i] != lastButtonState[i]) {
        if ((millis() - lastDebounceTime[i]) > debounceDelay) {
          toggleState[i] = !toggleState[i];  // Toggle button

          data.attackBtnBit.attack1 = toggleState[0];
          data.attackBtnBit.attack2 = toggleState[1];
          data.attackBtnBit.attack3 = toggleState[2];
          data.attackBtnBit.attack4 = toggleState[3];

          data.moveBtnBit.move1 = toggleState[4];

          lastButtonState[i] = reading[i];
        }
      }

    } else {
      lastDebounceTime[i] = millis();
      lastButtonState[i] = reading[i];
    }
  }
}