/*
 * KEYPAD.c
 *
 * Created: 7/28/2020 6:23:49 PM
 *  Author: Khaled Osama Eraky
 */ 

#include "KEYPAD.h"
#include <util/delay.h>

void keypad_setup( DIO_Struct *	 keypad_Dio){
	
	vuint8_t  direction_byte=0xF0;
	vuint8_t  port_byte=0xFF;
	
	/*Low order bits is input pull_up and high order bits is output and write 1 to it*/
	DIO_portConfigure(keypad_Dio , direction_byte);
	DIO_portWrite(keypad_Dio , port_byte);
}

/* Connect the Keypad to specified port 
   Rows >> from pin4 to pin7 as output
   Column >>from pin0 to pin3 as input
   when the rows out logic 0 and column 
   read zero it return the array element
   */
uint8_t Keypad_pressed_key( DIO_Struct * Keypad_Dio){
	uint8_t button_pressed=KEY_NOT_PRESSED;
	uint8_t KeyPad_elemnts [ROW_NUM][COL_NUM]=
	{
	{'1','2','3'},
	{'4','5','6'},
	{'7','8','9'},
    {'*','0','#'},
    };
	
	for (uint8_t Row = 0; Row < ROW_NUM; Row++)
	
	{ 
		vuint8_t Row_byte = ~(0b00010000 << Row);
		DIO_portWrite(Keypad_Dio , Row_byte);

		for (uint8_t Col = 0; Col < COL_NUM; Col++)
		{
			if (!(DIO_pinRead(Keypad_Dio, Col)))
			{ 
				button_pressed= KeyPad_elemnts[Row][Col];
				_delay_us(BOUNC_TIME);
			}
			
		}
	}
	return button_pressed;
};
