/*
* Shift74hc595.c
*
* Created: 2015-01-09 23:04:07
*  Author: Krzysztof
*/

#include "Shift74hc595.h"

void initShift(){
	DDRB |= (1 << SHIFT_LATCH);
	DDRB |= (1 << SHIFT_CLCK);
	DDRB |= (1 << SHIFT_DATA);
	
	PORTB &= ~(1 << SHIFT_LATCH);
	PORTB &= ~(1 << SHIFT_CLCK);
	PORTB &= ~(1 << SHIFT_DATA);
}

void writeBytes(uint8_t value){
	writeBytesRCLK(value,0x01);
}

void writeBytesRCLK(uint8_t value, uint8_t pushRCLK){
	if(pushRCLK==1){
		PORTB &= ~(1 << SHIFT_LATCH);
	}
	for(uint8_t i=0;i<8;i++){
		PORTB &= ~(1 << SHIFT_CLCK);
		if(getNthByte(value,i)==0){
			PORTB &= ~(1 << SHIFT_DATA);
			}else{
			PORTB |= (1 << SHIFT_DATA);
		}
		PORTB |= (1 << SHIFT_CLCK);
	}
	if(pushRCLK==1){
		PORTB |= (1 << SHIFT_LATCH);
	}
}