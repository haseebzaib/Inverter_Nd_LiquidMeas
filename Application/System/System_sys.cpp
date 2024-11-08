/*
 * System_common.cpp
 *
 *  Created on: Nov 6, 2024
 *      Author: user
 */




#include "cstring"
#include "string"
#include "System_sys.hpp"


//TODO
//Put receiving buffer check as well due to overflow check its length as well

namespace System_sys {

Parsing_Checking::Parsing_Checking()
{

}

enum Parsing_Checking::status Parsing_Checking::checkResponse_OK_ERR(const char *buffer,uint16_t bufferSize)
{
	enum status stat = sys_notFound;

    if(std::strstr(buffer,"OK") != nullptr)
    {
    	stat = sys_ok;

    }
    else if(std::strstr(buffer, "ERROR") != nullptr)
    {
    	stat = sys_err;

    }


    return stat;


}

enum Parsing_Checking::status Parsing_Checking::parseDate_Time_Timezone( char *buffer, uint16_t bufferLen ,char *datebuf, char *timebuf, char *timezonebuf)
{
	enum status stat = sys_ok;

    static const char* months[] = {
        "Err", "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
    };

	int Ncolonpos;
	char *Scolonpos;
	int Ncommapos;
	char *Scommapos;
	int Npluspos;
	char *Spluspos;
	int Nminuspos;
	char *Sminuspos;


	char *DatePart;
	char *TimePart;
	char *TimezonePart;


	char temp[100];

	char compare_sign[10];
	int8_t useSign = -1;


	std::strncpy(temp,buffer,bufferLen);

	if(!std::strstr((const char *)temp,"+CCLK:"))
	{

		return sys_notFound;

	}

	Scolonpos = std::strchr(temp, ':');


	if(Scolonpos != nullptr)
	{
		Ncolonpos = Scolonpos - temp;
        Ncolonpos = Ncolonpos + 3;
	}
	else
	{
		return sys_notFound;
	}

	Scommapos = std::strchr(temp, ',');
	if(Scommapos != nullptr)
	{
		Ncommapos = Scommapos - temp;
		Ncommapos = Ncommapos + 1;
	}
	else
	{
		return sys_notFound;
	}


	Sminuspos = std::strchr(temp, '-');
	if(Sminuspos != nullptr)
	{
		Nminuspos = Sminuspos - temp;
		std::strcpy(compare_sign,"-");
		useSign = 0;
	}
	else
	{
		Spluspos = std::strchr(temp, '+');
		if(Spluspos != nullptr)
		{
			Npluspos = Spluspos - temp;
			std::strcpy(compare_sign,"+");
			useSign = 1;
		}
		else
		{
		   return sys_notFound;
		}
	}




	DatePart = std::strtok(temp + Ncolonpos  , ",");



	if(DatePart != nullptr)
	{
	    // Split the date part into day, month, and year
	    char* year = std::strtok(DatePart, "/");
	    int year_ = std::atoi(year);
	    char* monthStr = std::strtok(DatePart+4, "/");
	    int month = std::atoi(monthStr);
	    char* day = std::strtok(DatePart+7, "/");
	    int day_ = std::atoi(day);

	    std::snprintf(datebuf, 20, "%02d-%s-%02d", day_, months[month], year_);

	}
	else
	{
		return sys_notFound;
	}




	TimePart = std::strtok(temp + Ncommapos  , compare_sign);

	if(TimePart != nullptr)
	{
		std::strcpy(timebuf,TimePart);
	}
	else
	{

	  return sys_notFound;

	}


	uint16_t len = strlen(TimePart);

	std::strncpy(timezonebuf,buffer + Ncommapos + len  ,3);



	  return stat;

}

enum Parsing_Checking::status Parsing_Checking::parseSkipCharnDTillEndChar(char *buffer, uint16_t bufferLen,char *CheckString,
		                                                         uint8_t skipChar,uint8_t endChar,char *databuf)
{


	enum status stat = sys_notFound;
    uint16_t len = 0;
	char temp[100];

	std::strncpy(temp,buffer,bufferLen);

	if(!std::strstr((const char *)temp,CheckString))
	{

		return sys_notFound;

	}

	int Ncolonpos;
	char *Scolonpos;
	int Nendpos;
	char *Sendpos;


	Scolonpos = std::strchr(temp, skipChar);


	if(Scolonpos != nullptr)
	{
		Ncolonpos = Scolonpos - temp;
		if(skipChar == ':')
        {
			Ncolonpos = Ncolonpos + 2;
        }
		else
		{
			Ncolonpos = Ncolonpos + 1;
		}
	}
	else
	{
		return sys_notFound;
	}


	uint16_t buf_index = Ncolonpos;

	while(len < bufferLen - Ncolonpos && buf_index < bufferLen)
	{

		if(buffer[buf_index] != endChar)
		{
			databuf[len] = buffer[buf_index];

		}else if(buffer[buf_index] == endChar)
		{
			databuf[len] = 0x00;
			return sys_ok;
		}


		buf_index++;
		len++;

	}


	  return stat;
}




}
