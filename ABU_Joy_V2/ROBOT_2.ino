uint8_t toggleState_2;
uint8_t lastButtonState_2 = 1;
long lastDebounceTime_2;

uint8_t reading_2;

uint8_t Reset_2 = 0;

#define debounceDelay_2 100

void ROBOT_2_Game_Play(){
   // อ่านค่าจากปุ่มที่ใช้ toggle
  reading_2 = gpio_get_level((gpio_num_t)GPIO_NUM_18);  // attack1 toggle

  data.moveBtnBit.move1 = !gpio_get_level((gpio_num_t)GPIO_NUM_5);
  data.moveBtnBit.move2 = !gpio_get_level((gpio_num_t)GPIO_NUM_4);
  data.moveBtnBit.move3 = !gpio_get_level((gpio_num_t)GPIO_NUM_14);
  data.moveBtnBit.move4 = !gpio_get_level((gpio_num_t)GPIO_NUM_12);

  data.moveBtnBit.set1 = !gpio_get_level((gpio_num_t)GPIO_NUM_13);
  data.moveBtnBit.set2 = !gpio_get_level((gpio_num_t)GPIO_NUM_15);

  // data.attackBtnBit.attack1 = !gpio_get_level((gpio_num_t)GPIO_NUM_18);
  data.attackBtnBit.attack2 = !gpio_get_level((gpio_num_t)GPIO_NUM_27);
  data.attackBtnBit.attack3 = !gpio_get_level((gpio_num_t)GPIO_NUM_25);
  data.attackBtnBit.attack4 = !gpio_get_level((gpio_num_t)GPIO_NUM_26);

  if (reading_2 == 0) {
    if (reading_2 != lastButtonState_2) {
      if ((millis() - lastDebounceTime_2) > debounceDelay_2) {
        toggleState_2 = !toggleState_2;  // Toggle button
        data.attackBtnBit.attack1 = toggleState_2;
        lastButtonState_2 = reading_2;
      }
    }
  } else {
    lastDebounceTime_2 = millis();
    lastButtonState_2 = reading_2;
  }

  if (data.attackBtnBit.attack2 == 1) {
    _Degree = 0;
  }

  _Degree += data.stickValue[2];

  if ((data.moveBtnBit.set1 == 1) && (Reset_2 == 0)) {
    data.moveBtnBit.move1 = 0;
    data.moveBtnBit.move2 = 0;
    // data.moveBtnBit.move3 = 0;
    data.moveBtnBit.move4 = 0;

    data.moveBtnBit.set1 = 0;
    data.moveBtnBit.set2 = 0;

    data.attackBtnBit.attack1 = 0;
    data.attackBtnBit.attack2 = 0;
    data.attackBtnBit.attack3 = 0;
    data.attackBtnBit.attack4 = 0;

    // for(uint8_t i = 0 ; i < 6 ; i++){
      toggleState_2 = 0;
      lastButtonState_2 = 1;
      lastDebounceTime_2 = 0;
    // }

    _Degree = 0;
  }
  Reset_2 = data.moveBtnBit.set1;
}