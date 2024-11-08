/*
 * app_main.cpp
 *
 *  Created on: Nov 1, 2024
 *      Author: user
 */


#include "app_main.hpp"
#include "Init.hpp"


System_Rtos::freertos_Tasks ModemTaskHandler(ModemTask,"Modem",_StackSize_Modem, (void*) 1,24);
System_Rtos::freertos_Tasks InverterTaskHandler(InverterTask,"Inverter",_StackSize_Inverter, (void*) 1,24);
System_Rtos::freertos_Tasks ControlnDDisplayTaskHandler(ControlnDDisplayTask,"ControlDis",_StackSize_ControlnDDisplay, (void*) 1,24);





void app_mainCpp()
{

	ModemTaskHandler.createTask();
	InverterTaskHandler.createTask();
    ControlnDDisplayTaskHandler.createTask();

}



// All the functions that need to be used in C files transport from here
extern "C"
{

    void app_mainC()
    {
    	app_mainCpp();
    }


}

