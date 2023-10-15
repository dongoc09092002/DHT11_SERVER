#include "DHT11.h"
char arr[50];
__weak void DHT11_CallBack(char *arr ,uint8_t tem_int , uint8_t tem_float , uint8_t hum_int, uint8_t hum_float){
	
	
}


TIM_HandleTypeDef *htim;


uint8_t int_tem;	
uint8_t int_hum;
uint8_t float_tem;
uint8_t float_hum;
uint8_t check;

void DHT11_Init(HDT11_Typedef *DHT11 , TIM_HandleTypeDef *_htim ,GPIO_TypeDef  *_DHT11_GPIO, uint32_t _DHT11_GPIO_Pin ){
	htim = _htim;
	DHT11->DHT11_GPIO = _DHT11_GPIO;
	DHT11->DHT11_GPIO_Pin = _DHT11_GPIO_Pin;
}
void delay_us(uint16_t us){
	
	htim->Instance->CNT = 0;
	HAL_TIM_Base_Start(htim);
	while(htim->Instance->CNT < us);
	HAL_TIM_Base_Stop(htim);
}
void delay_ms(uint16_t ms){
	uint16_t i;
	for(i = 0 ; i < ms ; i ++){
		delay_us(1000);
	}
}
void DHT11_Start(HDT11_Typedef *DHT11){
	GPIO_InitTypeDef GPIO_InitStruct = {0};
  GPIO_InitStruct.Pin = DHT11->DHT11_GPIO_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(DHT11->DHT11_GPIO, &GPIO_InitStruct);
	HAL_GPIO_WritePin(DHT11->DHT11_GPIO , DHT11->DHT11_GPIO_Pin , 1);
	HAL_GPIO_WritePin(DHT11->DHT11_GPIO , DHT11->DHT11_GPIO_Pin , 0);
	HAL_Delay(20);
	HAL_GPIO_WritePin(DHT11->DHT11_GPIO  , DHT11->DHT11_GPIO_Pin , 1);
}
void DHT11_Wait_Response(HDT11_Typedef *DHT11){
	GPIO_InitTypeDef GPIO_InitStruct = {0};
  GPIO_InitStruct.Pin = DHT11->DHT11_GPIO_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(DHT11->DHT11_GPIO, &GPIO_InitStruct);
	while(HAL_GPIO_ReadPin(DHT11->DHT11_GPIO , DHT11->DHT11_GPIO_Pin) == 1){} // doi no len 0
  while(HAL_GPIO_ReadPin(DHT11->DHT11_GPIO , DHT11->DHT11_GPIO_Pin) == 0);  // doi no len 1
	while(HAL_GPIO_ReadPin(DHT11->DHT11_GPIO , DHT11->DHT11_GPIO_Pin) == 1);  // doi no len 0
}

uint8_t DHT11_Read_Data(HDT11_Typedef *DHT11){
	uint8_t result;
	uint8_t i;
	for(i = 0 ; i < 8 ; i ++){
		while(HAL_GPIO_ReadPin(DHT11->DHT11_GPIO , DHT11->DHT11_GPIO_Pin ) == 0){} // doi no len 1
	  delay_us(50);
		if(HAL_GPIO_ReadPin(DHT11->DHT11_GPIO , DHT11->DHT11_GPIO_Pin ) == 1){
		result = (result<<1) | (1<<0);
		}
	else{
		result = (result<<1) & ~(1<<0);
	}
	
	while(HAL_GPIO_ReadPin(DHT11->DHT11_GPIO , DHT11->DHT11_GPIO_Pin) == 1); // doi no len 0
	}
	return result ;
}


void DHT11_Handle(HDT11_Typedef *DHT11){
	
	DHT11_Start(DHT11);
	DHT11_Wait_Response(DHT11);
	int_hum = DHT11_Read_Data(DHT11);
	float_hum = DHT11_Read_Data(DHT11);
	int_tem = DHT11_Read_Data(DHT11);
	float_tem = DHT11_Read_Data(DHT11);
	check = DHT11_Read_Data(DHT11);
	
	
  char *pt;
  pt = arr ;
  sprintf(arr , "tem=%d&hum=%d" , int_tem , int_hum );
	DHT11_CallBack(arr,int_tem , float_tem , int_hum , float_hum);
	
}