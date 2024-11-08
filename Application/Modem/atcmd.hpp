/*
 * atcmd.hpp
 *
 *  Created on: Nov 6, 2024
 *      Author: user
 */

#ifndef MODEM_ATCMD_HPP_
#define MODEM_ATCMD_HPP_


static constexpr uint8_t atcmd_AT[] = "AT\r\n";
/*Reset GSM*/
static constexpr uint8_t atcmd_ATCRESET[] = "AT+CRESET\r\n";
/*Network registeration*/
static constexpr uint8_t atcmd_ATCREG[] = "AT+CREG=1\r\n";
/*Prefered Message Storage*/
static constexpr uint8_t atcmd_ATCPMS[] = "AT+CPMS=\"ME\",\"ME\",\"ME\"\r\n";
/*Operator Selection*/
static constexpr uint8_t atcmd_ATCOPS[] = "AT+COPS=0\r\n";
/*SMS format*/
static constexpr uint8_t atcmd_ATCMGF[] = "AT+CMGF=1\r\n";
/*Packet domain attach*/
static constexpr uint8_t atcmd_ATCGATT[] = "AT+CGATT=1\r\n";
/*Get CLK time */
static constexpr uint8_t atcmd_ATCCLK[] = "AT+CCLK?\r\n";
/*Sim status*/
static constexpr uint8_t atcmd_ATCPIN[] = "AT+CPIN?\r\n";
/*get Network status*/
static constexpr uint8_t atcmd_GATCREG[] = "AT+CREG?\r\n";
/*get quality*/
static constexpr uint8_t atcmd_ATCSQ[] = "AT+CSQ\r\n";
/*Current manufacture parameters*/
static constexpr uint8_t atcmd_AT_F0[] = "AT&F0]\r\n";
/*Echo control*/
static constexpr uint8_t atcmd_ATE1[] = "ATE1\r\n";

#endif /* MODEM_ATCMD_HPP_ */
