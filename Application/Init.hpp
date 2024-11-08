/*
 * Init.hpp
 *
 *  Created on: Nov 8, 2024
 *      Author: user
 */

#ifndef INIT_HPP_
#define INIT_HPP_

//#include "main.h"
//#include "app_main.hpp"
#include "System/System_Rtos.hpp"


void ModemTask(void * pvParameters);
void InverterTask(void * pvParameters);
void ControlnDDisplayTask(void * pvParameters);



#define _StackSize_Modem 512
#define _StackSize_Inverter 256
#define _StackSize_ControlnDDisplay 256


extern System_Rtos::freertos_Tasks ModemTaskHandler;
extern System_Rtos::freertos_Tasks InverterTaskHandler;
extern System_Rtos::freertos_Tasks ControlnDDisplayTaskHandler;

extern System_Rtos::freertos_queues ModemDataQueue;
//extern System_Rtos::freertos_queues InverterDataQueue;


struct ModemData_Runtime {
	char time[10];
	char date[10];
	char timezone[5];
	char pin[15];
	char networkStat[15];
	char quality[10];
};

#endif /* INIT_HPP_ */
