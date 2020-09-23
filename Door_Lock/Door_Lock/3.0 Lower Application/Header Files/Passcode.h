/*
 * Passcode.h
 *
 * Created: 15/08/2020 05:48:10 
 *  Author: Khaled Osama Eraky
 */ 


#ifndef PASSCODE_H_
#define PASSCODE_H_

#include "KEYPAD.h"
#include "LCD.h"
#include "USART.h"
#include "relay.h"

#define TEMPORARY_PASSWORD 0
#define PASSWORD_ONE 1
#define PASSWORD_TWO 2
#define PASSWORD_THREE 3
#define PASSWORD_FOUR 4
#define PASSWORD_FIVE 5

#define CHECKBYTE 0
#define PASSWORD 1
#define PHONE_NUMBER 7
#define ACCESS_TIME 18
#define FINGER_PRINT_ID 19
#define USERNAME 20

#define ONE_ACCESS_TIME '1'
#define NO_ACCESS_TIME  '2'
#define PERMENANT_ACCESS '0'
#define PASSWORD_LENGTH 6


typedef struct
{
	uint8_t Password[6];
	uint8_t PhoneNumber[11];
	uint8_t FingerPrintID;
	uint8_t AccessTime ;
	uint8_t UserName[15];
}UserPacket;

uint8_t Enter_password(uint8_t * passcode);
uint8_t compareArray(uint8_t a[],uint8_t b[],uint8_t size);
void CopyArray(uint8_t a[],uint8_t b[],uint8_t size);
void Match_Password (uint8_t * passcode, UserPacket *ALLPasswords , RelayDataType Relay ,  uint8_t *internet_state);




#endif /* PASSCODE_H_ */