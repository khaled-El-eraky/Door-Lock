/*
 * relay.c
 *
 * Created: 15/08/2020 05:54:31 
 *  Author: Khaled Osama Eraky
 */ 

#include "relay.h"


void Relay_Setup(RelayDataType Relay)
{
	DIO_pinConfigure(Relay.Relay_Dio,Relay.Relay_Pin,OUTPUT);
	Relay_Control(Relay,RELAY_OFF);
}

void Relay_Control(RelayDataType Relay,RelayStates state)
{
	switch (state)
	{
		case RELAY_ON:
		if (Relay.RelayType == RELAY_ACTIVE_HIGH)
		{
			DIO_pinWrite(Relay.Relay_Dio,Relay.Relay_Pin,HIGH);
		}
		else
		{
			DIO_pinWrite(Relay.Relay_Dio,Relay.Relay_Pin,LOW);
		}
		break;
		case RELAY_OFF:
		if (Relay.RelayType == RELAY_ACTIVE_HIGH)
		{
			DIO_pinWrite(Relay.Relay_Dio,Relay.Relay_Pin,LOW);
		}
		else
		{
			DIO_pinWrite(Relay.Relay_Dio,Relay.Relay_Pin,HIGH);
		}
		break;
		default:
		break;
	}
}