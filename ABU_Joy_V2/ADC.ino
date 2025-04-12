void SetupADC(){
  //GPIO13
  adc2_config_channel_atten(ADC2_CHANNEL_4, ADC_ATTEN_DB_11);
  
  //GPIO12
  adc2_config_channel_atten(ADC2_CHANNEL_5, ADC_ATTEN_DB_11);

  //GPIO2
  adc2_config_channel_atten(ADC2_CHANNEL_2, ADC_ATTEN_DB_11);

  //GPIO0
  adc2_config_channel_atten(ADC2_CHANNEL_0, ADC_ATTEN_DB_11);

}

int value_stick[4] = { 0 };

void ReadValue(int8_t Value_OUT[]){
  //joyL_X,joyL_Y ,joyR_X,joyR_Y

  //get_raw GPIO13
  adc2_get_raw(ADC2_CHANNEL_4, ADC_WIDTH_BIT_12, &value_stick[0]);
  
  //get_raw GPIO12
  adc2_get_raw(ADC2_CHANNEL_5, ADC_WIDTH_BIT_12, &value_stick[1]);

  //get_raw GPIO2
  adc2_get_raw(ADC2_CHANNEL_2, ADC_WIDTH_BIT_12, &value_stick[2]);

  //get_raw GPIO0
  adc2_get_raw(ADC2_CHANNEL_0, ADC_WIDTH_BIT_12, &value_stick[3]);

  // Value_OUT[0] = value_stick[2];
  // Value_OUT[1] = value_stick[3];
  // Value_OUT[2] = value_stick[0];
  // Value_OUT[3] = value_stick[1];

  Value_OUT[0] = map(value_stick[2], 144, 3540, 100, -100);
  Value_OUT[1] = map(value_stick[3], 245, 4070, -100, 100);
  Value_OUT[2] = map(value_stick[0], 209, 4095, -100, 100);
  Value_OUT[3] = map(value_stick[1], 209, 4095, 100, -100);

  for(uint8_t i = 0 ; i < 4 ;i++){
    if((Value_OUT[i] < 20)&&(Value_OUT[i] > -20)){
      Value_OUT[i] = 0;
    }
  }
}