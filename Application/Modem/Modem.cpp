/*
 * Modem_SimA7672.cpp
 *
 *  Created on: Nov 5, 2024
 *      Author: user
 */

#include "Modem.hpp"
#include "cstdio"
#include "cstring"
#include "System/System_serial.hpp"
#include "atcmd.hpp"
#include "main.h"

namespace Modem {

struct simA7672::classInstanceRecorder simA7672::ClassInstances[numberofuart] =
		{ nullptr };

uint8_t simA7672::ClassInstanceIncrementer = 0;

simA7672::simA7672(UART_HandleTypeDef *huart) :
		GlobalTxBufs { simA7672::Txbuffer }, GlobalRxBufs { simA7672::Rxbuffer }, serial_(
				huart), checking() {

	simA7672::ClassInstances[ClassInstanceIncrementer].huart = huart;
	simA7672::ClassInstances[ClassInstanceIncrementer].Instance = this;

	simA7672::ClassInstanceIncrementer++;
	if (simA7672::ClassInstanceIncrementer > numberofuart) {
		simA7672::ClassInstanceIncrementer = 0;
	}

	setModemCallback(simA7672::RxCBStatic, simA7672::TxCBStatic);

}

enum simA7672::status simA7672::init() {
	status stat = simA7672_OK;

	//Run 3 times
	PrepRxTx(atcmd_AT, sizeof(atcmd_AT) - 1, 1000, _LF, CMD_mode);
	stat = check_eventTimeout(rx_evt, 5000);

	PrepRxTx(atcmd_AT, sizeof(atcmd_AT) - 1, 1000, _LF, CMD_mode);
	stat = check_eventTimeout(rx_evt, 5000);

	PrepRxTx(atcmd_AT, sizeof(atcmd_AT) - 1, 1000, _LF, CMD_mode);
	stat = check_eventTimeout(rx_evt, 5000);

	PrepRxTx(atcmd_ATCRESET, sizeof(atcmd_ATCRESET) - 1, 1000, _LF, CMD_mode);
	stat = check_eventTimeout(rx_evt, 5000);

	HAL_Delay(30000);

	/*After reset send two AT just to make gsm responsive*/
	PrepRxTx(atcmd_AT, sizeof(atcmd_AT) - 1, 1000, _LF, CMD_mode);
	stat = check_eventTimeout(rx_evt, 5000);

	PrepRxTx(atcmd_AT, sizeof(atcmd_AT) - 1, 1000, _LF, CMD_mode);
	stat = check_eventTimeout(rx_evt, 5000);

	PrepRxTx(atcmd_AT, sizeof(atcmd_AT) - 1, 1000, _LF, CMD_mode);
	stat = check_eventTimeout(rx_evt, 5000);

	PrepRxTx(atcmd_AT_F0, sizeof(atcmd_AT_F0) - 1, 1000, _LF, CMD_mode);
	stat = check_eventTimeout(rx_evt, 5000);

	PrepRxTx(atcmd_ATE1, sizeof(atcmd_ATE1) - 1, 1000, _LF, CMD_mode);
	stat = check_eventTimeout(rx_evt, 5000);

	PrepRxTx(atcmd_ATCREG, sizeof(atcmd_ATCREG) - 1, 1000, _LF, CMD_mode);
	stat = check_eventTimeout(rx_evt, 5000);

	PrepRxTx(atcmd_ATCPMS, sizeof(atcmd_ATCPMS) - 1, 1000, _LF, CMD_mode);
	stat = check_eventTimeout(rx_evt, 5000);

	PrepRxTx(atcmd_ATCOPS, sizeof(atcmd_ATCOPS) - 1, 1000, _LF, CMD_mode);
	stat = check_eventTimeout(rx_evt, 5000);

	PrepRxTx(atcmd_ATCMGF, sizeof(atcmd_ATCMGF) - 1, 1000, _LF, CMD_mode);
	stat = check_eventTimeout(rx_evt, 5000);

	PrepRxTx(atcmd_ATCGATT, sizeof(atcmd_ATCGATT) - 1, 1000, _LF, CMD_mode);
	stat = check_eventTimeout(rx_evt, 5000);

	return stat;

}

enum simA7672::status simA7672::loop() {
	status stat = simA7672_OK;

	return stat;
}

/*Set functions*/
enum simA7672::status simA7672::setTextMode() {
	status stat = simA7672_OK;

	PrepRxTx(atcmd_ATCMGF, sizeof(atcmd_ATCMGF) - 1, 1000, _LF, CMD_mode);
	stat = check_eventTimeout(rx_evt, 5000);

	return stat;
}

enum simA7672::status simA7672::setTimeDate(char *TimeDate) {
	status stat = simA7672_OK;

	return stat;
}

/*Get Functions*/
void simA7672::getSim(char *pin) {
	status stat;

	PrepRxTx(atcmd_ATCPIN, sizeof(atcmd_ATCPIN) - 1, 1000, _LF, CMD_mode);
	stat = check_eventTimeout(rx_evt, 5000);
	if (stat == simA7672_OK
			&& checking.checkResponse_OK_ERR((const char*) Rxbuffer,
					Rx_info.Rxcount) == checking.sys_ok) {
		if (checking.parseSkipCharnDTillEndChar((char*) Rxbuffer,
				Rx_info.Rxcount, (char*) "+CPIN:", ':', _CR, pin)
				== checking.sys_ok) {
			return;
		} else {
			std::strcpy(pin, "--------");
		}

	} else {
		std::strcpy(pin, "--------");
	}

}
void simA7672::getPin() {

}
void simA7672::getNetwork(char *networkStat) {
	status stat;

	PrepRxTx(atcmd_GATCREG, sizeof(atcmd_GATCREG) - 1, 1000, _LF, CMD_mode);
	stat = check_eventTimeout(rx_evt, 5000);

	if (stat == simA7672_OK
			&& checking.checkResponse_OK_ERR((const char*) Rxbuffer,
					Rx_info.Rxcount) == checking.sys_ok) {
		if (checking.parseSkipCharnDTillEndChar((char*) Rxbuffer,
				Rx_info.Rxcount, (char*) "+CREG:", ',', _CR, networkStat)
				== checking.sys_ok) {
			switch (*networkStat) {
			case '0': {
				std::strcpy(networkStat, "Not reg");

				break;
			}
			case '1': {
				std::strcpy(networkStat, "Registered, home network");

				break;
			}
			case '2': {
				std::strcpy(networkStat, "Currently Searching");

				break;
			}
			case '3': {
				std::strcpy(networkStat, "Registration denied");

				break;
			}
			case '4': {
				std::strcpy(networkStat, "Unknown");

				break;
			}
			case '5': {
				std::strcpy(networkStat, "Registered,roaming");

				break;
			}
			case '6': {
				std::strcpy(networkStat, "Registered SMS only");

				break;
			}
			case '7': {
				std::strcpy(networkStat, "Registered SMS only,roaming");

				break;
			}
			default: {
				std::strcpy(networkStat, "--------");

				break;
			}
			}
			return;
		} else {
			std::strcpy(networkStat, "--------");
		}

	} else {
		std::strcpy(networkStat, "--------");
	}

}
void simA7672::getSignalQ(char *quality) {

	status stat;

	char buffer[10];
	int8_t csq = 0;
	PrepRxTx(atcmd_ATCSQ, sizeof(atcmd_ATCSQ) - 1, 1000, _LF, CMD_mode);
	stat = check_eventTimeout(rx_evt, 5000);

	if (stat == simA7672_OK
			&& checking.checkResponse_OK_ERR((const char*) Rxbuffer,
					Rx_info.Rxcount) == checking.sys_ok) {
		if (checking.parseSkipCharnDTillEndChar((char*) Rxbuffer,
				Rx_info.Rxcount, (char*) "+CSQ:", ':', ',', buffer)
				== checking.sys_ok) {

			csq = std::atoi(buffer);
			if (csq >= 99) {
				csq = 0;

			} else {
				csq = (2 * (csq)) - 113;
			}

			std::sprintf(quality, "%02d dbm", csq);

			return;
		} else {
			std::strcpy(quality, "--------");
		}

	} else {
		std::strcpy(quality, "--------");
	}

}
void simA7672::getTimeDate(char *Time, char *Date, char *timezone) {
	status stat;

	PrepRxTx(atcmd_ATCCLK, sizeof(atcmd_ATCCLK) - 1, 1000, _LF, CMD_mode);
	stat = check_eventTimeout(rx_evt, 5000);

	if (stat == simA7672_OK
			&& checking.checkResponse_OK_ERR((const char*) Rxbuffer,
					Rx_info.Rxcount) == checking.sys_ok) {
		if (checking.parseDate_Time_Timezone((char*) Rxbuffer, Rx_info.Rxcount,
				Date, Time, timezone) == checking.sys_ok) {
			return;
		} else {
			std::strcpy(Date, "ER-ER-ER");
			std::strcpy(Time, "ER:ER:ER");
			std::strcpy(timezone, "ERR");
		}

	} else if (stat == simA7672_OK
			&& checking.checkResponse_OK_ERR((const char*) Rxbuffer,
					Rx_info.Rxcount) == checking.sys_err) {
		/*ToDo*/
	} else {
		/*ToDo*/
	}

}

void simA7672::PrepRx(uint8_t end_char, enum Rxmode Rxmode) {

	memset(this->Rxbuffer, 0, this->BufferLen);
	rst_event(rx_evt);

	Rx_info.end_char = end_char;
	Rx_info.rx_mode = Rxmode;
	Rx_info.detect_endchar = 0;
	Rx_info.end_char_count = 0;
	Rx_info.release_event = -1;
	Rx_info.Rx = Rxbuffer;
	Rx_info.Rxcount = 0;
	serial_.RxintEn(Rx_info.Rx, BufferLen);

}
void simA7672::PrepTx(const uint8_t *Txbuf, uint16_t len, uint16_t timeout) {
	memset(Txbuffer, 0, BufferLen);
	rst_event(tx_evt);
	serial_.TransmitData(Txbuf, len, timeout);

}
void simA7672::PrepRxTx(const uint8_t *Txbuf, uint16_t len, uint16_t timeout,
		uint8_t end_char, enum Rxmode Rxmode) {

	memset(Rxbuffer, 0, BufferLen);
	memset(Txbuffer, 0, BufferLen);
	rst_event(rx_evt);
	rst_event(tx_evt);

	Rx_info.end_char = end_char;
	Rx_info.rx_mode = Rxmode;
	Rx_info.detect_endchar = 0;
	Rx_info.end_char_count = 0;
	Rx_info.release_event = -1;
	Rx_info.Rx = Rxbuffer;
	Rx_info.Rxcount = 0;
	serial_.RxintEn(Rx_info.Rx, BufferLen);
	serial_.TransmitData(Txbuf, len, timeout);

}
inline void simA7672::set_event(enum eventType event) {
	Event[event] = 1;
}
inline void simA7672::rst_event(enum eventType event) {
	Event[event] = 0;
}
enum simA7672::status simA7672::check_event(enum eventType event) {

	status stat = simA7672_OK;

	if (Event[event]) {
		stat = simA7672_OK;
	} else if (!Event[event]) {
		stat = simA7672_ERR;
	}

	return stat;

}
enum simA7672::status simA7672::check_eventForever(enum eventType event) {
	status stat = simA7672_OK;

	while (check_event(event) != simA7672_OK) {
		//wait here forever
	}

	return stat;

}
enum simA7672::status simA7672::check_eventTimeout(enum eventType event,
		uint16_t timeout) {
	status stat = simA7672_OK;
	uint32_t prev_time = 0;

	prev_time = HAL_GetTick(); //we get new time before going into while
	while ((check_event(event) != simA7672_OK)
			&& (HAL_GetTick() - prev_time < timeout)) {
		//wait here until get event or time passes
		HAL_Delay(10);
	}

	if (check_event(event) != simA7672_OK) {
		stat = simA7672::simA7672_ERR;
	}

	return stat;

}

/*Interrupt callbacks*/

void simA7672::RxCB(uint8_t data) {
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wvolatile"
	if (Rx_info.rx_mode == CMD_mode) {
		*Rx_info.Rx++ = data;
		Rx_info.Rxcount++;

		if (Rx_info.end_char_count == 1) {
			Rx_info.release_event++;

		}

		if (Rx_info.detect_nextlinechar == 1 && (data == 'O' || data == 'E')) {
			Rx_info.detect_nextlinechar = 0; //reset it
			Rx_info.end_char_count = 1;
			if (data == 'O') {
				Rx_info.total_char = 2;
			} else if (data == 'E') {
				Rx_info.total_char = 5;
			}

		} else {
			Rx_info.detect_nextlinechar = 0; //reset it

		}

		if (data == simA7672::_LF) {
			Rx_info.detect_nextlinechar = 1;

		}

		if (Rx_info.release_event >= Rx_info.total_char) {
			set_event(rx_evt);
			serial_.RxintDis();
		}

	}
#pragma GCC diagnostic pop

}

void simA7672::TxCB(UART_HandleTypeDef *huart) {

}

void simA7672::RxCBStatic(UART_HandleTypeDef *huart, uint8_t data) {
	// Find the instance and call its instance method
	uint8_t i = 0;
	for (i = 0; i < numberofuart; i++) {
		if (ClassInstances[i].huart == huart) {
			break;
		}
	}

	if (ClassInstances[i].Instance) {
		ClassInstances[i].Instance->RxCB(data); // Delegate to instance-specific method
	}

}
void simA7672::TxCBStatic(UART_HandleTypeDef *huart) {

}

}

