/*
 * relay.h
 *
 * Created: 15/08/2020 05:54:11 
 *  Author: Khaled Osama Eraky
 */ 


#ifndef RELAY_H_
#define RELAY_H_


#include "Microcontroller_config.h"
#include "DIO.h"
#include "StdTypes.h"


typedef enum {
	RELAY_OFF=0,
	RELAY_ON=1,
	
}RelayStates;

typedef enum {
	RELAY_ACTIVE_LOW,
	RELAY_ACTIVE_HIGH,
	
}RelayActiveRegion;

typedef struct
{
	DIO_Struct *Relay_Dio;
	pinNumber Relay_Pin;
	RelayActiveRegion RelayType;
	
}RelayDataType;

void Relay_Setup(RelayDataType Relay);
void Relay_Control(RelayDataType Relay,RelayStates state);


#endif /* RELAY_H_ */