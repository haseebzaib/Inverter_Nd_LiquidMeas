/*
 * Display_HMI.cpp
 *
 *  Created on: Nov 1, 2024
 *      Author: user
 */



#include "Display_HMI.hpp"
#include "cstring"
//#include "regex"
#include "string"

namespace HMI {

union DWIN::MIX_UWORD DWIN::convert_16bit_to_8bit;

DWIN::DWIN(UART_HandleTypeDef *huart) : serial_(huart){

}


enum DWIN::status DWIN::SendTankData(uint16_t id,uint16_t val)
   {
       status stat = DWIN_OK;
       uint8_t buf[100];
       buf[0] = frame1;
       buf[1] = frame2;
       buf[2] = 0x05;
       buf[3] = Send;
       convert_16bit_to_8bit.W = id;
       buf[4] = convert_16bit_to_8bit.B.Hb;
       buf[5] = convert_16bit_to_8bit.B.Lb;
       convert_16bit_to_8bit.W = val;
       buf[6] = convert_16bit_to_8bit.B.Hb;
       buf[7] = convert_16bit_to_8bit.B.Lb;
       serial_.TransmitData(buf, 8, 1000);

       return stat;
   }



enum DWIN::status DWIN::SendTimeDateData(uint16_t id_time,uint16_t id_date,char *time,char *date)
{
	 status stat = DWIN_OK;
	 uint8_t len = 0;
	 uint8_t buf[100];

     buf[0] = frame1;
     buf[1] = frame2;
     buf[3] = Send;
     convert_16bit_to_8bit.W = id_time;
     buf[4] = convert_16bit_to_8bit.B.Hb;
     buf[5] = convert_16bit_to_8bit.B.Lb;
     len = 3;
     len = stringTohex(time,buf,6,len);
     buf[2] = len;

     serial_.TransmitData(buf, len + 3, 1000);


     HAL_Delay(500);

     memset(buf,0,100);
     buf[0] = frame1;
     buf[1] = frame2;
     buf[3] = Send;
     convert_16bit_to_8bit.W = id_date;
     buf[4] = convert_16bit_to_8bit.B.Hb;
     buf[5] = convert_16bit_to_8bit.B.Lb;
     len = 3;
     len = stringTohex(date,buf,6,len);
     buf[2] = len;

     serial_.TransmitData(buf, len + 3, 1000);

	 //memset(buf,0,100);

	 return stat;
}

enum DWIN::status DWIN::SendNetworkData(uint16_t id,char *network)
{
	 status stat = DWIN_OK;
	 uint8_t len = 0;
	 uint8_t buf[100];

     buf[0] = frame1;
     buf[1] = frame2;
     buf[3] = Send;
     convert_16bit_to_8bit.W = id;
     buf[4] = convert_16bit_to_8bit.B.Hb;
     buf[5] = convert_16bit_to_8bit.B.Lb;
     len = 3;
     len = stringTohex(network,buf,6,len);
     buf[2] = len;

     serial_.TransmitData(buf, len + 3, 1000);

	 return stat;

}
enum DWIN::status DWIN::SendNetworkQuality(uint16_t id,char *CSQ)
{
	 status stat = DWIN_OK;
	 uint8_t len = 0;
	 uint8_t buf[100];

     buf[0] = frame1;
     buf[1] = frame2;
     buf[3] = Send;
     convert_16bit_to_8bit.W = id;
     buf[4] = convert_16bit_to_8bit.B.Hb;
     buf[5] = convert_16bit_to_8bit.B.Lb;
     len = 3;
     len = stringTohex(CSQ,buf,6,len);
     buf[2] = len;

     serial_.TransmitData(buf, len + 3, 1000);

	 return stat;
}


uint8_t DWIN::stringTohex(char *input,uint8_t *output,uint8_t index,uint8_t len)
{

	    size_t length = std::strlen(input);


	     for (size_t i = 0; i < length; ++i) {
	    	if(input[i] != '\0')
	    	 {
	    	   output[index] = static_cast<uint8_t>(input[i]);
	    	   len++;
	    	   index++;
	    	 }
	    	else
	    	{
	    		break;
	    	}
	     }

	    return len;

}

}
