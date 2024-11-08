/*
 * Init.hpp
 *
 *  Created on: Nov 8, 2024
 *      Author: user
 */

#ifndef INIT_HPP_
#define INIT_HPP_

#include "main.h"
#include "app_main.hpp"
#include "System/System_Rtos.hpp"


void ModemTask(void * pvParameters);
void InterfaceTask(void * pvParameters);
void ControlnDDisplayTask(void * pvParameters);


#define _StackSize_Modem 512
#define _StackSize_Interface 256
#define _StackSize_ControlnDDisplay 256


System_Rtos::freertos_Tasks ModemTaskHandler(ModemTask,"Modem",_StackSize_Modem, (void*) 1,24);
System_Rtos::freertos_Tasks InterfaceTaskHandler(InterfaceTask,"Interface",_StackSize_Interface, (void*) 1,24);
System_Rtos::freertos_Tasks ControlnDDisplayTaskHandler(ControlnDDisplayTask,"ControlDis",_StackSize_ControlnDDisplay, (void*) 1,24);


#endif /* INIT_HPP_ */
