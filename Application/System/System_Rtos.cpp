/*
 * System_Rtis.cpp
 *
 *  Created on: Nov 8, 2024
 *      Author: user
 */

#include "System_Rtos.hpp"
#include "cstdio"
#include "cstring"

namespace System_Rtos {

void delay(uint32_t d)
{
  vTaskDelay(pdMS_TO_TICKS(d));
}

freertos_Tasks::freertos_Tasks(TaskFunction_t pxTaskCode_, const char *pcName_, /*lint !e971 Unqualified char types are allowed for strings and single characters only. */
const configSTACK_DEPTH_TYPE usStackDepth_, void *const pvParameters_,
		UBaseType_t uxPriority_): taskHandle(0) {

	pxTask = pxTaskCode_;
	std::strcpy(pcName, pcName_);
	usStackDepth = usStackDepth_;
	pvParameters = pvParameters_;
	uxPriority = uxPriority_;


}

void freertos_Tasks::createTask() {
	xTaskCreate(pxTask, pcName, usStackDepth, pvParameters, uxPriority,
			&taskHandle);
}



void freertos_Tasks::suspend() {
   vTaskSuspend(taskHandle);

}

void freertos_Tasks::resume() {
	vTaskResume(taskHandle);
}




}

