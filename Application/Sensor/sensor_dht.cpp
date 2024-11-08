/*
 * sensor_dht.cpp
 *
 *  Created on: Nov 1, 2024
 *      Author: user
 */

#include "sensor_dht.hpp"

namespace sensor_dht {



DHT::DHT(TIM_HandleTypeDef *htim,GPIO_TypeDef *port,uint16_t pin) {

    internal_dht_.htim = htim;
    internal_dht_.port = port;
    internal_dht_.pin = pin;

}


void DHT::set_gpio_mode(uint8_t pMode){
	GPIO_InitTypeDef GPIO_InitStruct = {0};

	if(pMode == OUTPUT)
	{
	  GPIO_InitStruct.Pin = internal_dht_.pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	  HAL_GPIO_Init(internal_dht_.port, &GPIO_InitStruct);
	}else if(pMode == INPUT)
	{
	  GPIO_InitStruct.Pin = internal_dht_.pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	  HAL_GPIO_Init( internal_dht_.port, &GPIO_InitStruct);
	}
}


DHT::status DHT::read(uint8_t *temp,uint8_t *humidity){
	enum status stat = DHT_OK;

	uint16_t mTime1 = 0, mTime2 = 0, mBit = 0;
		uint8_t humVal = 0, tempVal = 0, parityVal = 0, genParity = 0;
		uint8_t mData[40];

		//start comm
		set_gpio_mode(OUTPUT);			//set pin direction as input
		HAL_GPIO_WritePin( internal_dht_.port,  internal_dht_.pin, GPIO_PIN_RESET);
		HAL_Delay(18);					//wait 18 ms in Low state
		//__disable_irq();	//disable all interupts to do only read dht otherwise miss timer
		HAL_TIM_Base_Start( internal_dht_.htim); //start timer
		set_gpio_mode(INPUT);
		//check dht answer
		__HAL_TIM_SET_COUNTER( internal_dht_.htim, 0);				//set timer counter to zero
		while(HAL_GPIO_ReadPin( internal_dht_.port,  internal_dht_.pin) == GPIO_PIN_SET){
			if((uint16_t)__HAL_TIM_GET_COUNTER( internal_dht_.htim) > 500){
				//__enable_irq();
				//return 0;
				goto handleReturn;
			}
		}
		__HAL_TIM_SET_COUNTER( internal_dht_.htim, 0);
		while(HAL_GPIO_ReadPin( internal_dht_.port,  internal_dht_.pin) == GPIO_PIN_RESET){
			if((uint16_t)__HAL_TIM_GET_COUNTER( internal_dht_.htim) > 500){
				//__enable_irq();
				//return 0;
				goto handleReturn;
			}
		}
		mTime1 = (uint16_t)__HAL_TIM_GET_COUNTER( internal_dht_.htim);
		__HAL_TIM_SET_COUNTER( internal_dht_.htim, 0);
		while(HAL_GPIO_ReadPin( internal_dht_.port,  internal_dht_.pin) == GPIO_PIN_SET){
			if((uint16_t)__HAL_TIM_GET_COUNTER( internal_dht_.htim) > 500){
				//__enable_irq();
				//return 0;
				goto handleReturn;
			}
		}
		mTime2 = (uint16_t)__HAL_TIM_GET_COUNTER( internal_dht_.htim);

		//if answer is wrong return
		if(mTime1 < 75 && mTime1 > 85 && mTime2 < 75 && mTime2 > 85)
		{
			//__enable_irq();
			//return 0;
			goto handleReturn;
		}

	//	HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_SET);
		for(int j = 0; j < 40; j++)
		{
			__HAL_TIM_SET_COUNTER( internal_dht_.htim, 0);
			while(HAL_GPIO_ReadPin( internal_dht_.port,  internal_dht_.pin) == GPIO_PIN_RESET){
				if((uint16_t)__HAL_TIM_GET_COUNTER( internal_dht_.htim) > 500){
					//__enable_irq();
					//return 0;
					goto handleReturn;
				}

			}
			__HAL_TIM_SET_COUNTER( internal_dht_.htim, 0);
			while(HAL_GPIO_ReadPin( internal_dht_.port,  internal_dht_.pin) == GPIO_PIN_SET){
				if((uint16_t)__HAL_TIM_GET_COUNTER( internal_dht_.htim) > 500){
					//__enable_irq();
					//return 0;
					goto handleReturn;
				}

			}
			mTime1 = (uint16_t)__HAL_TIM_GET_COUNTER( internal_dht_.htim);

			//check pass time in high state
			//if pass time 25uS set as LOW
			if(mTime1 > 20 && mTime1 < 30)
			{
				mBit = 0;
			}
			else if(mTime1 > 60 && mTime1 < 80) //if pass time 70 uS set as HIGH
			{
				 mBit = 1;
			}

			//set i th data in data buffer
			mData[j] = mBit;

		}

		HAL_TIM_Base_Stop( internal_dht_.htim); //stop timer
		//__enable_irq(); //enable all interrupts

		//get hum value from data buffer
		for(int i = 0; i < 8; i++)
		{
			humVal += mData[i];
			humVal = humVal << 1;
		}

		//get temp value from data buffer
		for(int i = 16; i < 24; i++)
		{
			tempVal += mData[i];
			tempVal = tempVal << 1;
		}

		//get parity value from data buffer
		for(int i = 32; i < 40; i++)
		{
			parityVal += mData[i];
			parityVal = parityVal << 1;
		}

		parityVal = parityVal >> 1;
		humVal = humVal >> 1;
		tempVal = tempVal >> 1;

		genParity = humVal + tempVal;

	//	if(genParity == parityVal)

		internal_dht_.temperature = tempVal;
		internal_dht_.humidty = humVal;


		*temp =  internal_dht_.temperature;
		*humidity = internal_dht_.humidty;





handleReturn:
  return stat;

}




}
