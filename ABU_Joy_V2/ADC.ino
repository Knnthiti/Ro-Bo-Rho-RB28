#include <driver/adc.h>

void SetupADC(){
  //GPIO34
  adc1_config_channel_atten(ADC1_CHANNEL_6, ADC_ATTEN_DB_11);

  //GPIO35
  adc1_config_channel_atten(ADC1_CHANNEL_7, ADC_ATTEN_DB_11);

  //GPIO32
  adc1_config_channel_atten(ADC1_CHANNEL_4, ADC_ATTEN_DB_11);

  //GPIO33
  adc1_config_channel_atten(ADC1_CHANNEL_5, ADC_ATTEN_DB_11);

  adc1_config_width(ADC_WIDTH_BIT_12);

}

int value_stick[4] = { 0 };

void ReadValue(int8_t Value_OUT[]){
  //joyL_X,joyL_Y ,joyR_X,joyR_Y
  value_stick[0] = adc1_get_raw(ADC1_CHANNEL_7);
  value_stick[1] = adc1_get_raw(ADC1_CHANNEL_6);
  value_stick[2] = adc1_get_raw(ADC1_CHANNEL_5);
  value_stick[3] = adc1_get_raw(ADC1_CHANNEL_4);

  // Value_OUT[0] = value_stick[3];
  // Value_OUT[1] = value_stick[2];
  // Value_OUT[2] = value_stick[1];
  // Value_OUT[3] = value_stick[0];

  ////////////////////////////ROBOT_1///////////////////////////////////
  Value_OUT[0] = map(value_stick[0], 390, 3280, -100, 100);
  Value_OUT[1] = map(value_stick[1], 390, 3150, -100, 100);
  // Value_OUT[2] = map(value_stick[2], 415, 3255, -5, 5);
  Value_OUT[3] = map(value_stick[3], 345, 3315, -100, 100);
  ////////////////////////////ROBOT_1///////////////////////////////////

  for(uint8_t i = 0 ; i < 4 ;i++){
    if((Value_OUT[i] < 18)&&(Value_OUT[i] > -18)){
      Value_OUT[i] = 0;
    }
  }

  Value_OUT[2] = map(value_stick[2], 415, 3255, -2, 2);
}

