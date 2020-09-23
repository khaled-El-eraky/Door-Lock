/*
 * Door_Lock.c
 *
 * Created: 9/22/2020 1:01:11 AM
 *  Author: Khaled Osama Eraky
 */ 

#include "Microcontroller_config.h"
#include "LCD.h"
#include "KEYPAD.h"
#include "Passcode.h"
#include "relay.h"
#include <util/delay.h>

int main(void)
{
	LCD_init();
	keypad_setup(KEYPAD_DIO);
	
	RelayDataType relay ={DIOB , PIN0 ,RELAY_ACTIVE_HIGH};
	Relay_Setup(relay);
	uint8_t Internet_State;
	uint8_t *Internet_State_Ptr=&Internet_State;

    /* Test */
	UserPacket AllPasswords[6]=
	{
	{"555555" , "01033060899" , '3' , '0' , "shaimaa"},
	{"112233" , "01033060808" , '0' , '2' , "khaled"},
	{"111333" , "01033060808" , '0' , '3' , "dalia"},
	{"111111" , "01033060808" , '0' , '4' , "waly"},
	{"222222" , "01033060808" , '0' , '5' , "hamdy"}
	};
	
	
    while(1)
    {
		LCD_DisplayString("Enter Password");
		uint8_t password[6];
		uint8_t RESULT = Enter_password(password);
		if (RESULT ==OK)
		{
			Match_Password(password,AllPasswords,relay,Internet_State_Ptr);
		}
		_delay_ms(500);
	

    }
}