/*
 * Lowermain.c
 *
 * Created: 13/08/2020 02:42:09 
 *  Author: Khaled Osama Eraky
 */
#include "Lowermain.h"
 #include "Passcode.h"
 #include <util/delay.h>
 
 
	void Save_Data(uint8_t*recived_packet , UserPacket* ALLPasswords)
	{ if (recived_packet[ACCESS_TIME]==ONE_ACCESS_TIME)
		{
			CopyArray((uint8_t*)(ALLPasswords[TEMPORARY_PASSWORD].Password) ,recived_packet+PASSWORD , 6);
			CopyArray(ALLPasswords[TEMPORARY_PASSWORD].PhoneNumber ,recived_packet+PHONE_NUMBER ,11);
			CopyArray((uint8_t*)(ALLPasswords[TEMPORARY_PASSWORD].AccessTime) ,(uint8_t*)(recived_packet+ACCESS_TIME) ,1);
			CopyArray((ALLPasswords[TEMPORARY_PASSWORD].FingerPrintID) ,recived_packet+FINGER_PRINT_ID ,1);
			CopyArray((uint8_t*)ALLPasswords[TEMPORARY_PASSWORD].UserName ,recived_packet+USERNAME ,15);
		}
		else
		{
			
		}
	}
	
	void Check_Data(uint8_t*recived_packet , uint8_t*internet_state , UserPacket* ALLPasswords , RelayDataType Relay )
	{
		switch(recived_packet[0])
		{
			
			
			case '0':
			Save_Data(recived_packet , ALLPasswords);
			LCD_DisplayString("struct data");
			_delay_ms(1000);
			break;
			case '1':
			Relay_Control(Relay , RELAY_ON);
			LCD_DisplayString("open lock");
			break;
			case '2':
			*internet_state='1';
			LCD_DisplayString("no Internet");
			_delay_ms(1000);
			break;
			case '3':
			*internet_state='0';
			LCD_DisplayString("Internet available");
			break;
		}
		
	}
	