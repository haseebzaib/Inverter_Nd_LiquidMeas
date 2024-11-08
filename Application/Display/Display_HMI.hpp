/*
 * Display_HMI.hpp
 *
 *  Created on: Nov 1, 2024
 *      Author: user
 */

#ifndef DISPLAY_DISPLAY_HMI_HPP_
#define DISPLAY_DISPLAY_HMI_HPP_

#include "main.h"
#include "System/System_serial.hpp"

namespace HMI {

class DWIN {

public:
	enum status {
		DWIN_OK = 0, DWIN_ERR = 1,
	};

	enum headers {
		frame1 = 0x5A, frame2 = 0xA5, Send = 0x82, Recv = 0x83,

	};

	enum id {
		TankLevel = 0x2010,
		Time = 0x1010,
		Date = 0x1020,
		Network = 0x8110,
		SigQ = 0x8220,
		Net = 0x8330,



	};

    DWIN(UART_HandleTypeDef *huart);
	enum status SendTankData(uint16_t id, uint16_t val);
	enum status SendTimeDateData(uint16_t id_time,uint16_t id_date,char *time,char *date);
    enum status SendNetworkData(uint16_t id,char *network);
    enum status SendNetworkQuality(uint16_t id,char *CSQ);

private:
#define CheckError(func, returnStat, checkStat) \
  if (func != checkStat)          \
  {                            \
    return returnStat;               \
  }                                 \


	union MIX_UWORD {
		uint16_t W;
		struct {
			uint8_t Lb;
			uint8_t Hb;
		} B;
	};

	static union MIX_UWORD convert_16bit_to_8bit;
	System_serial::serial serial_;




	uint8_t stringTohex(char *input,uint8_t *output,uint8_t index,uint8_t len);





};

}

#endif /* DISPLAY_DISPLAY_HMI_HPP_ */
