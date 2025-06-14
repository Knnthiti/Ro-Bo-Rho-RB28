uint8_t toggleState[6];
uint8_t lastButtonState[6] = { 1 };
long lastDebounceTime[6];

uint8_t reading[6];

uint8_t Reset = 0;

#define debounceDelay 100

void ROBOT_1_Game_Play() {
  // อ่านค่าจากปุ่มที่ใช้ toggle
  reading[0] = gpio_get_level((gpio_num_t)GPIO_NUM_18);  // attack1 toggle
  reading[1] = gpio_get_level((gpio_num_t)GPIO_NUM_27);  // attack2 toggle
  reading[2] = gpio_get_level((gpio_num_t)GPIO_NUM_26);  // attack3 toggle
  reading[3] = gpio_get_level((gpio_num_t)GPIO_NUM_25);  // attack4 toggle
  reading[4] = gpio_get_level((gpio_num_t)GPIO_NUM_12);  //move4
  // reading[5] =!gpio_get_level((gpio_num_t)GPIO_NUM_13);  //set1

  data.moveBtnBit.move1 = !gpio_get_level((gpio_num_t)GPIO_NUM_4);
  data.moveBtnBit.move2 = !gpio_get_level((gpio_num_t)GPIO_NUM_5);
  data.moveBtnBit.move3 = !gpio_get_level((gpio_num_t)GPIO_NUM_14);
  // data.moveBtnBit.move4 = !gpio_get_level((gpio_num_t)GPIO_NUM_12);

  data.moveBtnBit.set1 = !gpio_get_level((gpio_num_t)GPIO_NUM_13);
  data.moveBtnBit.set2 = !gpio_get_level((gpio_num_t)GPIO_NUM_15);

  // data.attackBtnBit.attack1 = !gpio_get_level((gpio_num_t)GPIO_NUM_18);
  // data.attackBtnBit.attack2 = !gpio_get_level((gpio_num_t)GPIO_NUM_27);
  // data.attackBtnBit.attack3 = !gpio_get_level((gpio_num_t)GPIO_NUM_25);
  // data.attackBtnBit.attack4 = !gpio_get_level((gpio_num_t)GPIO_NUM_26);

  for (uint8_t i = 0; i < 6; i++) {
    if (reading[i] == 0) {
      if (reading[i] != lastButtonState[i]) {
        if ((millis() - lastDebounceTime[i]) > debounceDelay) {
          toggleState[i] = !toggleState[i];  // Toggle button

          if (i == 0) {
            data.attackBtnBit.attack1 = toggleState[0];
          } else if (i == 1) {
            data.attackBtnBit.attack2 = toggleState[1];
          } else if (i == 2) {
            data.attackBtnBit.attack3 = toggleState[2];
          } else if (i == 3) {
            data.attackBtnBit.attack4 = toggleState[3];
          } else if (i == 4) {
            data.moveBtnBit.move4 = toggleState[4];
          } 
          // else if (i == 5) {
          //   data.moveBtnBit.set1 = toggleState[5];
          // }

          lastButtonState[i] = reading[i];
        }
      }
    } else {
      lastDebounceTime[i] = millis();
      lastButtonState[i] = reading[i];
    }
  }

  if ((data.attackBtnBit.attack2 == 1) && (lastButtonState[1] == 0)) {
    _Degree = 135;
  }

  if ((data.attackBtnBit.attack4 == 1) && (lastButtonState[3] == 0)) {
    _Degree = 0;
  }

  _Degree += data.stickValue[2];

  if (data.moveBtnBit.set1 == 1){
    data.moveBtnBit.move1 = 0;
    data.moveBtnBit.move2 = 0;
    data.moveBtnBit.move3 = 0;
    data.moveBtnBit.move4 = 0;

    // data.moveBtnBit.set1 = 0;
    data.moveBtnBit.set2 = 0;

    data.attackBtnBit.attack1 = 0;
    data.attackBtnBit.attack2 = 0;
    data.attackBtnBit.attack3 = 0;
    data.attackBtnBit.attack4 = 0;

    for(uint8_t i = 0 ; i < 6 ; i++){
      toggleState[i] = 0;
      lastButtonState[i] = 1;
      lastDebounceTime[i] = 0;
    }

    _Degree = 0;
  }
  Reset = data.moveBtnBit.set1;
}