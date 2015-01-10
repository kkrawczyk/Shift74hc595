/*
 * LCDShift.c
 *
 * Created: 2015-01-10 01:55:11
 *  Author: Krzysztof
 */ 

#include "LCDShift.h"

void initLcd(){
	initShift();
	lcdFunctions = LCD_4BITMODE | LCD_1LINE | LCD_5x8DOTS;
	lcdCurrentPins = 0x00;
	lcdCurrentLine = 0;
	setLcdFunctions(LCD_2LINE);
	
	//Wait before sending commands to LCD! 
	_delay_ms(100);
	setLcdPin(LCD_RS,0x00);
	setLcdPin(LCD_RW,0x00);
	setLcdPin(LCD_ENABLE,0x00);
}

void setLcdFunctions(uint8_t func){
	lcdFunctions |= func;
}

void setLcdPin(uint8_t pin,uint8_t val){
	if(val==0){
		setNthByteLow(&lcdCurrentPins,pin);
	}else{
		setNthByteHigh(&lcdCurrentPins,pin);
	}
	writeBytes(lcdCurrentPins);
}

void lcdSend(uint8_t value, uint8_t mode){
	setLcdPin(LCD_RS,mode);
	setLcdPin(LCD_RW,0);
	    //write4bits(value>>4);
	    //write4bits(value);
}

void lcdWrite4Bits(uint8_t value){
	for (int i = 0; i < 4; i++) {
		/*Checked: 
		* getNthByte(value,i) is equal to (value >> i) & 0x01
		*/
		uint8_t tmp = getNthByte(value,i);
		digitalWrite(_data_pins[i], (value >> i) & 0x01);
	}
	lcdPulseEnable();
}

void lcdPulseEnable(){
	setLcdPin(LCD_ENABLE,0);
	_delay_us(10); //Recomended - none
	setLcdPin(LCD_ENABLE,1);
	_delay_us(10); //Recomended - > 450ns
	setLcdPin(LCD_ENABLE,0);
	_delay_us(100); //Recomended > 37us
}