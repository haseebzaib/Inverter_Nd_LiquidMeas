/*
 * sensor_dht.hpp
 *
 *  Created on: Nov 1, 2024
 *      Author: user
 */

#ifndef SENSOR_SENSOR_DHT_HPP_
#define SENSOR_SENSOR_DHT_HPP_


#include "main.h"
#include "gpio.h"



namespace sensor_dht
{

  class DHT
  {
  public:
	  enum status
	  {
		  DHT_OK = 0,
		  DHT_ERR = 1,
	  };

	  DHT(TIM_HandleTypeDef *htim,GPIO_TypeDef *port,uint16_t pin);

	  enum status read(uint8_t *temp,uint8_t *humidity);




  private:
	  struct internal_dht
	  {
			GPIO_TypeDef* port;	///GPIO Port ex:GPIOA
			uint16_t pin; ///GPIO pin ex:GPIO_PIN_2
			TIM_HandleTypeDef *htim; /// timer for measure time ex:htim3
			uint8_t temperature; ///Temperature value
			uint8_t humidty; ///humidity value
	  };
	  struct internal_dht internal_dht_;
	  static constexpr uint8_t OUTPUT = 1;
      static constexpr uint8_t INPUT = 0;
      void set_gpio_mode(uint8_t pMode);


  };

}




#endif /* SENSOR_SENSOR_DHT_HPP_ */
