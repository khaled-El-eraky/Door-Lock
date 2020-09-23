/*
 * KEYPAD.h
 *
 * Created: 7/28/2020 6:23:34 PM
 *  Author: Khaled Osama Eraky
 */ 


#ifndef KEYPAD_H_
#define KEYPAD_H_

#include "Microcontroller_config.h"
#include "StdTypes.h"
#include "Macros.h"
#include "DIO.h"

#define KEY_NOT_PRESSED 10
#define BOUNC_TIME 100
#define COL_NUM 3
#define ROW_NUM 4
#define KEYPAD_DIO DIOA

#define OK    '*'
#define UP    'C'
#define DOWN  'D'
#define DEL   '#'
#define MATCH 'B'
#define ENROL 'A'

void keypad_setup( DIO_Struct *	 keypad_Dio);
uint8_t Keypad_pressed_key( DIO_Struct * Keypad_Dio);




void KeyPadWarningError(void);




#endif /* KEYPAD_H_ */