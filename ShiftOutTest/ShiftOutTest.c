/*
* ShiftOutTest.c
*
* Created: 2015-01-09 20:27:57
*  Author: Krzysztof
*/


#define F_CPU 1200000

#define SHIFT_CLCK PB1
#define SHIFT_LATCH PB0
#define SHIFT_DATA PB2

#include <stdlib.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/eeprom.h>

#include "ByteOperations.h"
#include "Shift74hc595.h"

void initRand(void)
{
	uint8_t state;
	static uint8_t EEMEM sstate;

	state = eeprom_read_byte(&sstate);

	// Check if it's unwritten EEPROM (first time). Use something funny
	// in that case.
	if (state == 0xff)
	state = 0xAA;
	srand(state);
	eeprom_write_byte(&sstate, rand());
}

int main(void)
{
	initRand();
	DDRB |= (1 << SHIFT_LATCH); // latch
	DDRB |= (1 << SHIFT_CLCK); // clock
	DDRB |= (1 << SHIFT_DATA); // data
	
	PORTB &= ~(1 << SHIFT_LATCH);
	for(uint8_t i=0;i<=10;i++){
		PORTB &= ~(1 << SHIFT_CLCK);
		PORTB &= ~(1 << SHIFT_DATA);
		PORTB |= (1 << SHIFT_CLCK);
	}
	PORTB |= (1 << SHIFT_LATCH);
	_delay_ms(1000);
	while(1)
	{
		PORTB &= ~(1 << SHIFT_LATCH);
		for(uint8_t i=0;i<8;i++){
			PORTB &= ~(1 << SHIFT_CLCK);
			if(getNthByte(255,i)==0){
				PORTB &= ~(1 << SHIFT_DATA);
				}else{
				PORTB |= (1 << SHIFT_DATA);
			}
			PORTB |= (1 << SHIFT_CLCK);
		}
		PORTB |= (1 << SHIFT_LATCH);
		_delay_ms(1000);
		PORTB &= ~(1 << SHIFT_LATCH);
		for(uint8_t i=0;i<=10;i++){
			PORTB &= ~(1 << SHIFT_CLCK);
			PORTB &= ~(1 << SHIFT_DATA);
			PORTB |= (1 << SHIFT_CLCK);
		}
		PORTB |= (1 << SHIFT_LATCH);
		_delay_ms(1000);
	}
	return 0;
}
/*
int main(void)
{
DDRB |= (1 << SHIFT_LATCH);
DDRB |= (1 << SHIFT_CLCK);
while(1)
{
PORTB |= (1 << SHIFT_LATCH);
PORTB &= ~(1 << SHIFT_CLCK);
_delay_ms(200);
PORTB &= ~(1 << SHIFT_LATCH);
PORTB |= (1 << SHIFT_CLCK);
_delay_ms(200);
}
return 0;
}*/