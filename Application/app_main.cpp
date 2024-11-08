/*
 * app_main.cpp
 *
 *  Created on: Nov 1, 2024
 *      Author: user
 */


#include "app_main.hpp"
#include "tim.h"
#include "main.h"
#include "Sensor/sensor_dht.hpp"
#include "Display/Display_HMI.hpp"
#include "Sensor/sensor_liquidMeas.hpp"
#include "System/System_serial.hpp"
#include "Modem/Modem.hpp"
#include "usart.h"
#include "adc.h"

sensor_dht::DHT DHT11(&DHT_Timer,DHT11_GPIO_Port,DHT11_Pin);
sensor_dht::DHT::status dhtStat;
sensor_liquidMeas::liquidSensor liquidSensor(&hadc1);
sensor_liquidMeas::liquidSensor::status liquidStat;


HMI::DWIN LCD(&HMI_USART1);
Modem::simA7672 simA7672(&GSM_USART2);

uint16_t val = 0;

float value;

void app_mainCpp()
{
//	uint8_t temp;
//	uint8_t humd;



   simA7672.init();

uint8_t i = 0;
	while(1)
	{


//		liquidStat = liquidSensor.getLevel(sensor_liquidMeas::liquidSensor::Meter, 0.0, 10.0, 3.3, &value);

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

        LCD.SendTimeDateData(LCD.Time,LCD.Date, time, date);
        LCD.SendTankData(LCD.TankLevel, i);
        LCD.SendNetworkData(LCD.Network, networkStat);
        LCD.SendNetworkQuality(LCD.SigQ, quality);


		HAL_GPIO_TogglePin(alive_led_GPIO_Port, alive_led_Pin);
		HAL_Delay(200);
		i++;
	}

}



// All the functions that need to be used in C files transport from here
extern "C"
{
    void app_mainC()
    {
    	app_mainCpp();
    }


}

