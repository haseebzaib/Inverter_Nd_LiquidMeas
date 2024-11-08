/*
 * ModemTask.cpp
 *
 *  Created on: Nov 8, 2024
 *      Author: user
 */

#include "app_main.hpp"
#include "Modem/Modem.hpp"
#include "System/System_Rtos.hpp"
#include "Init.hpp"


struct ModemData_Runtime ModemData;
uint8_t queuebuffer[1*sizeof(struct ModemData_Runtime)];

Modem::simA7672 simA7672(&GSM_USART2);
System_Rtos::freertos_queues ModemDataQueue(1,sizeof(struct ModemData_Runtime),	queuebuffer);




void ModemTask(void *pvParameters) {

	ModemDataQueue.queueCreate();
	simA7672.init();

	while (1) {



        simA7672.getTimeDate(ModemData.time, ModemData.date, ModemData.timezone);
        simA7672.getSim(ModemData.pin);
        simA7672.getNetwork(ModemData.networkStat);
        simA7672.getSignalQ(ModemData.quality);

		HAL_GPIO_TogglePin(alive_led_GPIO_Port, alive_led_Pin);
		System_Rtos::delay(500);




	}

}

