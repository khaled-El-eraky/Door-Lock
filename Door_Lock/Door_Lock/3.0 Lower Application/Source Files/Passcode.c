/*
 * Passcode.c
 *
 * Created: 15/08/2020 05:48:28 م
 *  Author: Khaled Osama Eraky
 */ 
#include "Passcode.h"
#include <util/delay.h>

#define Matched 1
#define NotMatched 0


void CopyArray(uint8_t a[] , uint8_t b[] , uint8_t size)
{
	uint8_t i;
	for(i=0;i<size;i++)
	{
		a[i]=b[i];
	}
}

uint8_t compareArray(uint8_t a[] , uint8_t b[] , uint8_t size)
{
	uint8_t i;
	uint8_t comparasion = NotMatched;
	for(i=0;i<size;i++)
	{
		if((a[i] = b[i]))
		{
			comparasion = Matched;
		}
	}
	return comparasion;
}

uint8_t Enter_password(uint8_t * passcode)
{
	uint8_t Ok;
	uint8_t i =0;
	/*6 digit password plus OK button*/
	while (i < 7)
	{
		uint8_t keypad_button =Keypad_pressed_key(KEYPAD_DIO);
		if ((i == 0) && (keypad_button != KEY_NOT_PRESSED) )
		{
			LCD_Clear();
		}
		
		switch (keypad_button)
		{
			case '0':
				if (i!=6)
				{
					LCD_DisplayChar('0');
					passcode [i]='0';
					i++;
			    }
			break;
			case '1':
			if (i!=6){
				LCD_DisplayChar('1');
				passcode [i]='1';
				i++;
			}
			break;
			case '2':
			if (i!=6){
				LCD_DisplayChar('2');
				passcode [i]='2';
				i++;
			}
			break;
			case '3':
			if (i!=6){
				LCD_DisplayChar('3');
				passcode [i]='3';
				i++;
			}
			break;
			case '4':
			if (i!=6){
				LCD_DisplayChar('4');
				passcode [i]='4';
				i++;
			}
			break;
			case '5':
			if (i!=6){
				LCD_DisplayChar('5');
				passcode [i]='5';
				i++;
			}
			break;
			case '6':
			if (i!=6){
				LCD_DisplayChar('6');
				passcode [i]='6';
				i++;
			}
			break;
			case '7':
			if (i!=6){
				LCD_DisplayChar('7');
				passcode [i]='7';
				i++;
			}
			break;
			case '8':
			if (i!=6){
				LCD_DisplayChar('8');
				passcode [i]='8';
				i++;
			}
			break;
			case '9':
			if (i!=6){
				LCD_DisplayChar('9');
				passcode [i]='9';
				i++;
			}
			break;
			case '#':
			if (i!=6){
				LCD_DeleteChar();
				i--;
			}
			break;
			case '*' :
			if (i==6)
			{
				Ok='*';
			}
			i++;
			break;
			default:
			break;
		}
		
		_delay_ms(120);
	}
	
	
	return Ok;
}

void Match_Password (uint8_t *passcode , UserPacket *ALLPasswords , RelayDataType Relay ,  uint8_t *internet_state)
{
	
	if (compareArray(passcode , ALLPasswords[TEMPORARY_PASSWORD].Password , PASSWORD_LENGTH) && 
	    ALLPasswords[TEMPORARY_PASSWORD].AccessTime!=NO_ACCESS_TIME)
	{
		//send USERNAME
		LCD_Clear();
		LCD_DisplayString("AcceptedPassword");
		_delay_ms(2000);
		//LCD_Clear();
		//LCD_DisplayString(ALLPasswords[TEMPORARY_PASSWORD].UserName);
		Relay_Control(Relay , RELAY_ON);
		if ((*internet_state) =='1')
		{
			LCD_Clear();
			LCD_DisplayString("No Internet");
			//gsm send message
		}
		else
		{
			UART_Send_string(ALLPasswords[TEMPORARY_PASSWORD].UserName);
		}
		ALLPasswords[TEMPORARY_PASSWORD].AccessTime=NO_ACCESS_TIME;
		
		
		

	}
	else
	{
		if (compareArray(passcode , ALLPasswords[PASSWORD_ONE].Password,PASSWORD_LENGTH))
		{
			LCD_Clear();
			
			LCD_DisplayString("AcceptedPassword");
			Relay_Control(Relay , RELAY_ON);
			_delay_ms(2000);
			LCD_Clear();
			if (*internet_state ==1)
			{
				//gsm send message
			}
			else
			{
				UART_Send_string(ALLPasswords[PASSWORD_ONE].UserName);
			}
			//LCD_DisplayString(ALLPasswords[PASSWORD_ONE].UserName);
			
			

		}
		else
		{
			if (compareArray(passcode , ALLPasswords[PASSWORD_TWO].Password,PASSWORD_LENGTH))
			{
				LCD_Clear();
				LCD_DisplayString("AcceptedPassword");
				Relay_Control(Relay , RELAY_ON);
				_delay_ms(2000);
				LCD_Clear();
				//LCD_DisplayString(ALLPasswords[PASSWORD_TWO].UserName);
				
				if (*internet_state ==1)
				{
					//gsm send
				}
				else
				{
					UART_Send_string(ALLPasswords[PASSWORD_TWO].UserName);
				}

			}
			else
			{
				if (compareArray(passcode , ALLPasswords[PASSWORD_THREE].Password,PASSWORD_LENGTH))
				{
					LCD_Clear();
					LCD_DisplayString("AcceptedPassword");
					Relay_Control(Relay , RELAY_ON);
					_delay_ms(2000);
					LCD_Clear();
					//LCD_DisplayString(ALLPasswords[PASSWORD_THREE].UserName);
					if (*internet_state ==1)
					{
						//gsm send
					}
					else
					{
						UART_Send_string(ALLPasswords[PASSWORD_THREE].UserName);
					}
				}
				else
				{
					if (compareArray(passcode , ALLPasswords[PASSWORD_FOUR].Password,PASSWORD_LENGTH))
					{
						LCD_Clear();
						LCD_DisplayString("AcceptedPassword");
						Relay_Control(Relay , RELAY_ON);
						_delay_ms(2000);
						LCD_Clear();
						//LCD_DisplayString(ALLPasswords[PASSWORD_FOUR].UserName);
						if (*internet_state ==1)
						{
							//gsm send
						}
						else
						{
							UART_Send_string(ALLPasswords[PASSWORD_FOUR].UserName);
						}

					}
					else
					{
						if (compareArray(passcode , ALLPasswords[PASSWORD_FIVE].Password,PASSWORD_LENGTH))
						{
							LCD_Clear();
							
							LCD_DisplayString("AcceptedPassword");
							Relay_Control(Relay , RELAY_ON);
							_delay_ms(2000);
							LCD_Clear();
					
							//LCD_DisplayString(ALLPasswords[PASSWORD_FIVE].UserName);
							if (*internet_state ==1)
							{
								//gsm send
							}
							else
							{
								UART_Send_string(ALLPasswords[PASSWORD_FIVE].UserName);
							}

						}
						else
						
						{
							LCD_Clear();
							LCD_DisplayString("Wrong Password");
						}
					}

				}
			}
		}
	}
};