/*
 * app_main.cpp
 *
 *  Created on: Nov 1, 2024
 *      Author: user
 */


#include "app_main.hpp"
#include "Init.hpp"






void app_mainCpp()
{

	ModemTaskHandler.createTask();
   InterfaceTaskHandler.createTask();
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

