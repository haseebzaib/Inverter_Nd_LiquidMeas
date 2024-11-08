/*
 * ModemTask.cpp
 *
 *  Created on: Nov 8, 2024
 *      Author: user
 */

#include "app_main.hpp"
#include "Modem/Modem.hpp"
#include "System/System_Rtos.hpp"


Modem::simA7672 simA7672(&GSM_USART2);

void ModemTask(void *pvParameters) {

	simA7672.init();

	while (1) {

		char time[100];
		char date[100];
		char timezone[100];
		char pin[100];
		char networkStat[100];
		char quality[20];

        simA7672.getTimeDate(time, date, timezone);
        simA7672.getSim(pin);
        simA7672.getNetwork(networkStat);
        simA7672.getSignalQ(quality);

		HAL_GPIO_TogglePin(alive_led_GPIO_Port, alive_led_Pin);
		System_Rtos::delay(500);


	}

}

