#ifndef MQ2_H
#define MQ2_H
#include "stdint.h"
#include "stm32f1xx_hal.h"
	
//typedef struct{
//  uint32_t       DHT11_GPIO_Pin;
//	GPIO_TypeDef  *DHT11_GPIO;
//}TypeDef_MQ;

void  MQ2_Init(ADC_HandleTypeDef *_hadc);
void  MQ2_Handle();
uint8_t  MQ2_DataToPercent(uint16_t data);



#endif