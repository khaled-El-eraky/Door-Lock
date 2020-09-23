/*
 * Lowermain.h
 *
 * Created: 13/08/2020 02:41:50 
 *  Author: Khaled Osama Eraky
 */ 


#ifndef LOWERMAIN_H_
#define LOWERMAIN_H_

#include "Passcode.h"
void Save_Data(uint8_t*recived_packet , UserPacket* ALLPasswords);
void Check_Data(uint8_t*recived_packet , uint8_t*internet_state , UserPacket* ALLPasswords , RelayDataType Relay );



#endif /* LOWERMAIN_H_ */