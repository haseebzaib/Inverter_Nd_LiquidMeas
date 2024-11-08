/*
 * InterfaceTask.cpp
 *
 *  Created on: Nov 8, 2024
 *      Author: user
 */

#include "app_main.hpp"
#include "System/System_Rtos.hpp"
void InterfaceTask(void *pvParameters) {

	while (1) {
		System_Rtos::delay(500);
	}

}
