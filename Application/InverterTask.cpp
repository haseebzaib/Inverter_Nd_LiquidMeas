/*
 * InterfaceTask.cpp
 *
 *  Created on: Nov 8, 2024
 *      Author: user
 */

#include "app_main.hpp"
#include "System/System_Rtos.hpp"
#include "Init.hpp"



void InverterTask(void *pvParameters) {

	while (1) {
		System_Rtos::delay(1000);
	}

}
