/*
 * LCD.c
 *
 * Created: 7/13/2020 1:47:10 AM
 *  Author: Khaled Osama Eraky
 *
*/


#include "LCD.h"
#include <util/delay.h>

#if ( _5x10_Dot && Two_lines )
		#pragma GCC error "You cannot Have Two Lines LCD with 5 * 10"
#endif

		/* List Of Command Codes */
#define Clear_display 0x01
#define Return_Home	  0x02
#define Display_off   0x08
#define Display_on   (0x0C | (CURSOR<<1) | (Blink))
#define CURSOR_Shift_Right	 0x14
#define CURSOR_Shift_left	 0x10
#define Display_shift_left    0x18
#define Display_shift_Right	  0x1C
#define Data_Set (0x20 |(_5x10_Dot<<2)|(Two_lines<<3)| (eight_bitdata<<4))
#define DDRAM_CONST 0x80
#define CGRAM_CONST 0x40

#define LCD_1ST_BASE 0x00
#define LCD_2ND_BASE 0x40

#define LCD_LEFT 1
#define LCD_RIGHT 0

#define Space 0x20

	

	void LCD_init(void)
	{
		/* Set The Control Pins Direction to OUtput */
		LCD_CONTROL_IO->ddr.allRegister |=(1<<E) | (1<<RW) | (1<<RS);
		
		#if eight_bitdata
			/* Set the Direction of the 8 Data pins to Output */
			LCD_CONTROL_IO->ddr.allRegister =0xFF;
		#else
			
			#if Upper_Data_port
				/* Set The Direction of The Upper Pins to OP*/
			LCD_Data_IO->ddr.allRegister |=(0xF0);
			#else
				/* Set The Direction of The LOWER Pins to OP*/
			LCD_Data_IO->ddr.allRegister|=(0x0F);
			#endif
			Send_instruction(0x02);
		#endif
		
		Send_instruction(Data_Set);
		Send_instruction(Display_on);
		Send_instruction(Clear_display);
	}
	
	void Send_instruction(uint8_t instruction)
	{

		/* RW, RS Should be 0 when Writing instructions to LCD */
		CLEARBIT(LCD_CONTROL_IO->port.allRegister,RS);
		CLEARBIT(LCD_CONTROL_IO->port.allRegister,RW);
		/* Delay of Address Set 60ns minimum */
		_delay_ms(1);
		
		/* Enable LCD E=1 */
		SETBIT(LCD_CONTROL_IO->port.allRegister,E);
		/* delay for processing PW min 450ns */
		_delay_ms(1); 
		
		#if eight_bitdata		
			LCD_Data_IO->port.allRegister = instruction;
			/* Data set-up time delay  Tdsw = 195 ns */
			_delay_ms(1); 
			/* disable LCD E=0 */
			CLEARBIT(LCD_CONTROL_IO->port.allRegister,E);
			/* Data Hold delay Th = 10ns */ 
			_delay_ms(1); 
		#else 
			
			#if Upper_Data_port
				/* clear the Prev Data */
				LCD_Data_IO->port.allRegister &=0x0F;
				LCD_Data_IO->port.allRegister |= (instruction & 0xF0);
			
			#else	/* Lower Port */
				/* clear the Prev Data */
				LCD_Data_IO->port.allRegister &=0xF0;
				LCD_Data_IO->port.allRegister |= ((instruction >> 4) );
			#endif
			/* Data set-up time delay  Tdsw = 195 ns */
			_delay_ms(1);
		
			/* disable LCD E=0 */
			CLEARBIT(LCD_CONTROL_IO->port.allRegister,E);
			/* Data Hold delay Th = 10ns */
			_delay_ms(1);
			
			/* Enable LCD E=1 */
			SETBIT(LCD_CONTROL_IO->port.allRegister,E);
			/* delay for processing PW min 450ns */
			_delay_ms(1);
			#if Upper_Data_port
				/* clear the Prev Data */
				LCD_Data_IO->port.allRegister &=0x0F;
				LCD_Data_IO->port.allRegister |= ((instruction <<4) );
			
			#else	/* Lower Port */
				/* clear the Prev Data */
				LCD_Data_IO->port.allRegister &=0xF0;
				LCD_Data_IO->port.allRegister |= ((instruction) & 0x0f);
			#endif
				/* Data set-up time delay  Tdsw = 195 ns */
				_delay_ms(1);
				/* disable LCD E=0 */
				CLEARBIT(LCD_CONTROL_IO->port.allRegister,E);
				/* Data Hold delay Th = 10ns */
				_delay_ms(1);
		#endif
	}
	
	
	void LCD_DisplayChar(uint8_t Data)
	{
		/* RW  Should be 0  and RS should be 1 when Writing Data to LCD */
		SETBIT(LCD_CONTROL_IO->port.allRegister,RS);
		CLEARBIT(LCD_CONTROL_IO->port.allRegister,RW);
		/* Delay of Address Set 60ns minimum */
		_delay_ms(1);
		/* Enable LCD E=1 */
		SETBIT(LCD_CONTROL_IO->port.allRegister,E);
		/* delay for processing PW min 450ns */
		_delay_ms(1);
		#if eight_bitdata
			LCD_Data_IO->port.allRegister=Data;
		#else
			#if Upper_Data_port
				/* clear the Prev Data */
				LCD_Data_IO->port.allRegister &=0x0F;
				/* Send MSB (4-bits )*/
				LCD_Data_IO->port.allRegister |= (Data & 0xF0);
				
			#else /* Lower Port */
				/* clear the Prev Data */
				LCD_Data_IO->port.allRegister &=0xF0;
				/* Send MSB (4-bits )*/
				LCD_Data_IO->port.allRegister |= ((Data >> 4) & 0x0f);
			#endif
				
			/* Data set-up time delay  Tdsw = 195 ns */
			_delay_ms(1);
			/* disable LCD E=0 */
			CLEARBIT(LCD_CONTROL_IO->port.allRegister,E);
			/* Data Hold delay Th = 10ns */
			_delay_ms(1);
			/* Enable LCD E=1 */
			SETBIT(LCD_CONTROL_IO->port.allRegister,E);
				
			#if Upper_Data_port
				/* clear the Prev Data */
				LCD_Data_IO->port.allRegister &=0x0F;
				LCD_Data_IO->port.allRegister |= ((Data <<4) & 0xF0);
				/* delay for processing PW min 450ns */
				_delay_ms(1);
			#else	/* Lower Port */
				/* clear the Prev Data */
				LCD_Data_IO->port.allRegister &=0xF0;
				LCD_Data_IO->port.allRegister |= ((Data) & 0x0f);
			#endif
			
			#endif
		/* Data set-up time delay  Tdsw = 195 ns */
		_delay_ms(1);
		/* disable LCD E=0 */
		CLEARBIT(LCD_CONTROL_IO->port.allRegister,E);
		/* Data Hold delay Th = 10ns */
		_delay_ms(1);
		
	}
	
	void LCD_DeleteChar(void)
	{
		Send_instruction(CURSOR_Shift_left);
		LCD_DisplayChar(Space);
		Send_instruction(CURSOR_Shift_left);
	}
	
	
	void LCD_Clear(void)
	{
		/* Clear Screen */
		Send_instruction(Clear_display); 
	}
	
	
	void LCD_DisplayString(char * ptr)
	{
		while(*ptr != '\0')
		{
			LCD_DisplayChar(*ptr);
			ptr++;
		}
	}
	
	void LCD_Select_RowCol(uint8_t Row , uint8_t col)
	{
		uint8_t Address=0;
		
		switch(Row)
		{
			case 0:
					/* When Writing To LCD 1st Col The Base Address is 0x00 */
						Address=col + LCD_1ST_BASE;
						break;
			case 1:
					/* When Writing To LCD 2nd Col The Base Address is 0x40 */
						Address=col + LCD_2ND_BASE;
						break;		
			default:
						break;
		}
		
		Send_instruction(DDRAM_CONST|Address);
	}
	
	//
	//void LCD_DisplayNumber(float64 data , NumberBase Base)
	//{
		///* String to hold the ascii result */
		//char Result[21];
		 ///* 10 for decimal */
		//itoa((int)data,Result,Base);
		///* Display The Result */
		//LCD_DisplayString(Result);
	//}