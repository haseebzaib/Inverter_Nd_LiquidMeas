/*
 * System_Rtos.hpp
 *
 *  Created on: Nov 8, 2024
 *      Author: user
 */

#ifndef SYSTEM_SYSTEM_RTOS_HPP_
#define SYSTEM_SYSTEM_RTOS_HPP_

#include "main.h"

#include "FreeRTOS.h"
#include "task.h"




namespace System_Rtos {

void delay(uint32_t d);

class freertos_Tasks {
public:
	freertos_Tasks(TaskFunction_t pxTaskCode_,
			const char * pcName_,		/*lint !e971 Unqualified char types are allowed for strings and single characters only. */
			const configSTACK_DEPTH_TYPE usStackDepth_,
			void * const pvParameters_,
			UBaseType_t uxPriority_);

	void createTask();
	void suspend();
	void resume();



private:
	TaskFunction_t pxTask;
    char pcName[15];
	configSTACK_DEPTH_TYPE usStackDepth;
	void *pvParameters;
	UBaseType_t uxPriority;
	TaskHandle_t taskHandle;




};


class freertos_queues {

};




}



#endif /* SYSTEM_SYSTEM_RTOS_HPP_ */
