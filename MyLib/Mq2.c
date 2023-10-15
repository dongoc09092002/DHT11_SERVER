#include "Mq2.h"
#include "math.h"
ADC_HandleTypeDef *hadc;
__weak void MQ_CallBack_Data(uint8_t data_percent){


}
uint16_t value_adc;
void MQ2_Init(ADC_HandleTypeDef *_hadc){
	hadc = _hadc;
}
uint8_t  MQ2_DataToPercent(uint16_t data){
	uint8_t result = ((data-700)*99) / 3795 ;
	if(result > 99) {
		result = 0;
	}
	return result ;
}
void  MQ2_Handle(){
	  HAL_ADC_Start(hadc);
		HAL_ADC_PollForConversion(hadc,1000);
		value_adc = HAL_ADC_GetValue(hadc);
		uint8_t result_percent = MQ2_DataToPercent(value_adc);
	  MQ_CallBack_Data(result_percent);
		HAL_ADC_Stop(hadc);
}

