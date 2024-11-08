/*
 * sensor_liquid.hpp
 *
 *  Created on: Nov 1, 2024
 *      Author: user
 */

#ifndef SENSOR_SENSOR_LIQUIDMEAS_HPP_
#define SENSOR_SENSOR_LIQUIDMEAS_HPP_

#include "main.h"

namespace sensor_liquidMeas
{

    class liquidSensor {


    public:
    	  enum status
          {
    	     liquidSensor_OK = 0,
    		 liquidSensor_ERR = 1,
    	   };

    	  enum unit
		  {
    		Meter = 0,
			CentiMeter = 1,
			Foot = 2,
			Inch = 3,
    	  };

    	liquidSensor(ADC_HandleTypeDef *hadc);
    	enum status getLevel(enum unit unit_,float LowSpan,float fullSpan,float VoltOut,float *getlevel);



    private:
#define CheckError(func, returnStat, checkStat) \
  if (func != checkStat)          \
  {                            \
    return returnStat;               \
  }

        static constexpr float Resolution = 4096.0;
        static constexpr float Vref = 3.3;




    	ADC_HandleTypeDef *hadc_sensor;





    };



}



#endif /* SENSOR_SENSOR_LIQUIDMEAS_HPP_ */
