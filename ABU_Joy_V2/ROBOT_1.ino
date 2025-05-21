uint8_t toggleState_1[3];
uint8_t lastButtonState_1[3] = { 1 };
long lastDebounceTime_1[3];

uint8_t reading_1[3];

#define debounceDelay 100

void ROBOT_1_Game_Play() {
  // อ่านค่าจากปุ่มที่ใช้ toggle
  reading_1[0] = gpio_get_level((gpio_num_t)GPIO_NUM_25);  // attack3 toggle
  reading_1[1] = gpio_get_level((gpio_num_t)GPIO_NUM_26);  // attack4 toggle
  reading_1[2] = gpio_get_level((gpio_num_t)GPIO_NUM_12);  //move4

  data.moveBtnBit.move1 = !gpio_get_level((gpio_num_t)GPIO_NUM_5);
  data.moveBtnBit.move2 = !gpio_get_level((gpio_num_t)GPIO_NUM_4);
  data.moveBtnBit.move3 = !gpio_get_level((gpio_num_t)GPIO_NUM_14);
  // data.moveBtnBit.move4 = !gpio_get_level((gpio_num_t)GPIO_NUM_12);

  data.moveBtnBit.set1 = !gpio_get_level((gpio_num_t)GPIO_NUM_13);
  data.moveBtnBit.set2 = !gpio_get_level((gpio_num_t)GPIO_NUM_15);

  data.attackBtnBit.attack1 = !gpio_get_level((gpio_num_t)GPIO_NUM_18);
  data.attackBtnBit.attack2 = !gpio_get_level((gpio_num_t)GPIO_NUM_27);
  // data.attackBtnBit.attack3 = !gpio_get_level((gpio_num_t)GPIO_NUM_25);
  // data.attackBtnBit.attack4 = !gpio_get_level((gpio_num_t)GPIO_NUM_26);

  for (uint8_t i = 0; i < 3; i++) {
    if (reading_1[i] == 0) {
      if (reading_1[i] != lastButtonState_1[i]) {
        if ((millis() - lastDebounceTime_1[i]) > debounceDelay) {
          toggleState_1[i] = !toggleState_1[i];  // Toggle button

          if (i == 0) {
            data.attackBtnBit.attack3 = toggleState_1[0];

            // ถ้าเปิด attack3 แล้ว attack4 เปิดอยู่ → ปิด attack4
            if (data.attackBtnBit.attack3 && data.attackBtnBit.attack4) {
              data.attackBtnBit.attack4 = 0;
              toggleState_1[1] = 0;  // sync toggle state
            }

          } else if (i == 1) {
            data.attackBtnBit.attack4 = toggleState_1[1];

            // ถ้าเปิด attack4 แล้ว attack3 เปิดอยู่ → ปิด attack3
            if (data.attackBtnBit.attack4 && data.attackBtnBit.attack3) {
              data.attackBtnBit.attack3 = 0;
              toggleState_1[0] = 0;  // sync toggle state
            }

          } else if (i == 2) {
            data.moveBtnBit.move4 = toggleState_1[2];
          }

          lastButtonState_1[i] = reading_1[i];
        }
      }
    } else {
      lastDebounceTime_1[i] = millis();
      lastButtonState_1[i] = reading_1[i];
    }
  }
}