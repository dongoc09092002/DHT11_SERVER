#ifndef DHT11_H
#define DHT11_H
#include "stm32f1xx_hal.h"
#include "stdio.h"
typedef struct {
	uint32_t DHT11_GPIO_Pin;
	GPIO_TypeDef  *DHT11_GPIO;
}HDT11_Typedef;
void DHT11_Handle(HDT11_Typedef *DHT11);
void DHT11_Start(HDT11_Typedef *DHT11);
void DHT11_Wait_Response(HDT11_Typedef *DHT11);
void DHT11_Init(HDT11_Typedef *DHT11 , TIM_HandleTypeDef *_htim ,GPIO_TypeDef  *_DHT11_GPIO, uint32_t _DHT11_GPIO_Pin );
#endif