/*
* ShiftOutTest.c
*
* Created: 2015-01-09 20:27:57
*  Author: Krzysztof
*/


#define F_CPU 1200000

/*#define SHIFT_CLCK PB1
#define SHIFT_LATCH PB0
#define SHIFT_DATA PB2*/

#include <stdlib.h>
#include <avr/io.h>
#include <util/delay.h>
//#include <avr/eeprom.h>

#include "ByteOperations.h"
#include "Shift74hc595.h"
#include "LCDShift.h"

/*void initRand(void)
{
	uint8_t state;
	static uint8_t EEMEM sstate;

	state = eeprom_read_byte(&sstate);

	if (state == 0xff){
		state = 0x02;
	}
	srand(state);
	eeprom_write_byte(&sstate, rand());
}*/

int main(void)
{
	initLcd();
	//initShift();
	while(1){
		asm ("nop");
	}
	//lcdWrite4Bits(128);
	//initRand();
	/*initShift();
	initLcd();
	while(1)
	{
		writeBytes(63);
		_delay_ms(1000);
	}*/
	//return 0;
}
