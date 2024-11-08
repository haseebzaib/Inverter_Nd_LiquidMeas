/*
 * System_common.hpp
 *
 *  Created on: Nov 6, 2024
 *      Author: user
 */

#include "main.h"


namespace System_sys {

class Parsing_Checking {
public:
	enum status {
		sys_ok,
		sys_err,
		sys_notFound,
	};


	Parsing_Checking();

	enum status checkResponse_OK_ERR(const char *buffer,uint16_t bufferSize);
    enum status parseDate_Time_Timezone( char *buffer,  uint16_t bufferLen, char *datebuf, char *timebuf, char *timezonebuf );
    enum status parseSkipCharnDTillEndChar(char *buffer, uint16_t bufferLen,char *CheckString,uint8_t skipChar,uint8_t endChar,char *databuf);

private:



};


}
