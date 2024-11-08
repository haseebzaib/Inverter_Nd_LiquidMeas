/*
 * sensor_liquid.cpp
 *
 *  Created on: Nov 1, 2024
 *      Author: user
 */


#include "sensor_liquidMeas.hpp"
#include "adc.h"

namespace sensor_liquidMeas {


liquidSensor::liquidSensor(ADC_HandleTypeDef *hadc)
{
	hadc_sensor = hadc;
}

liquidSensor::status liquidSensor::getLevel(enum unit unit_,float LowSpan,float fullSpan,float VoltOut,float *getlevel)
{


	enum status stat = liquidSensor_OK;
	float totalSpan = fullSpan - LowSpan;

	if(hadc_sensor == NULL)
	{
		return liquidSensor_ERR;
	}


	CheckError(HAL_ADC_Start(hadc_sensor),liquidSensor_ERR,HAL_OK);
    CheckError(HAL_ADC_PollForConversion(hadc_sensor, 2000),liquidSensor_ERR,HAL_OK); //discard

    CheckError(HAL_ADC_Start(hadc_sensor),liquidSensor_ERR,HAL_OK);
    CheckError(HAL_ADC_PollForConversion(hadc_sensor, 2000),liquidSensor_ERR,HAL_OK); //discard


    CheckError(HAL_ADC_Start(hadc_sensor),liquidSensor_ERR,HAL_OK);
    CheckError(HAL_ADC_PollForConversion(hadc_sensor, 2000),liquidSensor_ERR,HAL_OK); //take the value


    HAL_ADC_Stop(hadc_sensor);


    uint32_t adcValue = HAL_ADC_GetValue(hadc_sensor);

    float voltage = (adcValue / Resolution) * Vref;

    *getlevel = ((voltage/VoltOut) * totalSpan) + LowSpan;



	  return stat;
}


}
