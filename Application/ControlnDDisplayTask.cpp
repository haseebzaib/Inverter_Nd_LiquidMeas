/*
 * ControlnDDisplayTask.cpp
 *
 *  Created on: Nov 8, 2024
 *      Author: user
 */

#include "app_main.hpp"
#include "System/System_Rtos.hpp"
#include "Display/Display_HMI.hpp"
#include "Sensor/sensor_liquidMeas.hpp"
#include "Init.hpp"


sensor_liquidMeas::liquidSensor liquidSensor(&hadc1);
HMI::DWIN LCD(&HMI_USART1);

void ControlnDDisplayTask(void *pvParameters) {

	while (1) {
		System_Rtos::delay(500);


	}

}
