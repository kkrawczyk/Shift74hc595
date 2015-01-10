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
	lcdDisplayControl = LCD_DISPLAYON | LCD_CURSORON | LCD_BLINKOFF;
	lcdDisplayMode = LCD_ENTRYLEFT | LCD_ENTRYSHIFTDECREMENT;
	lcdCurrentPins = 0x00;
	lcdCurrentLine = 0;
	//setLcdFunctions(LCD_2LINE);
	
	//Wait before sending commands to LCD!
	_delay_ms(100);
	setLcdPin(LCD_RS,0x00);
	setLcdPin(LCD_RW,0x00);
	setLcdPin(LCD_ENABLE,0x00);
	_delay_ms(200);
	/*lcdCommand4bit(LCD_FUNCTIONSET | lcdFunctions); // Perhaps use: lcdSendOnly4
	_delay_us(9000); //Delay > 4.1ms
	lcdCommand4bit(LCD_FUNCTIONSET | lcdFunctions); // Perhaps use: lcdSendOnly4
	_delay_us(300); // Delay > 150us
	lcdCommand4bit(LCD_FUNCTIONSET | lcdFunctions); // Perhaps use: lcdSendOnly4*/
	//Start:
	
	lcdCommand4bit(LCD_FUNCTIONSET | lcdFunctions);
	setLcdFunctions(LCD_2LINE);
	lcdCommand(LCD_FUNCTIONSET | lcdFunctions);
	lcdDisplay();
	//lcdDisplay();
	lcdClear();
	
	// set the entry mode
	lcdCommand(LCD_ENTRYMODESET | lcdDisplayMode);
}

void lcdSetCursor(uint8_t col, uint8_t row)
{
	int row_offsets[] = { 0x00, 0x40, 0x14, 0x54 };
	if ( row >= 2 ) {
		row = 1;    // we count rows starting w/0
	}
	
	lcdCommand(LCD_SETDDRAMADDR | (col + row_offsets[row]));
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
	//_delay_ms(1000);
}

void lcdClear(){
	lcdCommand(LCD_CLEARDISPLAY);
	_delay_us(2000);// this command takes a long time!
}

void lcdDisplay(){
	lcdDisplayControl |= LCD_DISPLAYON;
	lcdCommand(LCD_DISPLAYCONTROL | lcdDisplayControl);
}

void lcdWrite(uint8_t value){
	lcdSend(value, 1);
}

void lcdCommand4bit(uint8_t value){
	lcdSendOnly4(value,0);
}
void lcdCommand(uint8_t value){
	lcdSend(value, 0);
}

void lcdSend(uint8_t value, uint8_t mode){
	setLcdPin(LCD_RS,mode);
	setLcdPin(LCD_RW,0);
	lcdWrite4Bits(value>>4);
	lcdWrite4Bits(value);
}

void lcdSendOnly4(uint8_t value, uint8_t mode){
	setLcdPin(LCD_RS,mode);
	setLcdPin(LCD_RW,0);
	lcdWrite4Bits(value>>4);
	//lcdWrite4Bits(value);
}

void lcdWrite4Bits(uint8_t value){
	uint8_t byte0 = getNthByte(value,0);
	uint8_t byte1 = getNthByte(value,1);
	uint8_t byte2 = getNthByte(value,2);
	uint8_t byte3 = getNthByte(value,3);
	setLcdPin(LCD_D4,byte0);
	setLcdPin(LCD_D5,byte1);
	setLcdPin(LCD_D6,byte2);
	setLcdPin(LCD_D7,byte3);
	//for (int i = 0; i < 4; i++) {
	/*Checked:
	* getNthByte(value,i) is equal to (value >> i) & 0x01
	*/
	//uint8_t tmp = getNthByte(value,i);
	//0 -> pin5 arduino -> D4
	//1 -> D5
	//2 -> D6
	//3 -> D7
	//digitalWrite(_data_pins[i], (value >> i) & 0x01);
	//}
	lcdPulseEnable();
}

void lcdPulseEnable(){
	setLcdPin(LCD_ENABLE,0);
	_delay_us(1); //Recomended - none
	setLcdPin(LCD_ENABLE,1);
	_delay_us(1); //Recomended - > 450ns
	setLcdPin(LCD_ENABLE,0);
	_delay_us(100); //Recomended > 37us
}