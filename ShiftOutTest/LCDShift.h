/*
 * LCDShift.h
 *
 * Created: 2015-01-10 01:54:58
 *  Author: Krzysztof
 */ 


#ifndef LCDSHIFT_H_
#define LCDSHIFT_H_

#define F_CPU 1200000

#include <stdlib.h>
#include <avr/io.h>
#include <util/delay.h>

#include "ByteOperations.h"
#include "Shift74hc595.h"

//Shift Pins -> HAVE TO CHECK BIT ORDER!!
#define LCD_QA 7
#define LCD_QB 6
#define LCD_QC 5
#define LCD_QD 4
#define LCD_QE 3
#define LCD_QF 2
#define LCD_QG 1
#define LCD_QH 0

//LCD Pins
#define LCD_RS LCD_QA
#define LCD_RW LCD_QB
#define LCD_ENABLE LCD_QC
#define LCD_D4 LCD_QD
#define LCD_D5 LCD_QE
#define LCD_D6 LCD_QF
#define LCD_D7 LCD_QG

// commands
#define LCD_CLEARDISPLAY 0x01
#define LCD_RETURNHOME 0x02
#define LCD_ENTRYMODESET 0x04
#define LCD_DISPLAYCONTROL 0x08
#define LCD_CURSORSHIFT 0x10
#define LCD_FUNCTIONSET 0x20
#define LCD_SETCGRAMADDR 0x40
#define LCD_SETDDRAMADDR 0x80

// flags for display entry mode
#define LCD_ENTRYRIGHT 0x00
#define LCD_ENTRYLEFT 0x02
#define LCD_ENTRYSHIFTINCREMENT 0x01
#define LCD_ENTRYSHIFTDECREMENT 0x00

// flags for display on/off control
#define LCD_DISPLAYON 0x04
#define LCD_DISPLAYOFF 0x00
#define LCD_CURSORON 0x02
#define LCD_CURSOROFF 0x00
#define LCD_BLINKON 0x01
#define LCD_BLINKOFF 0x00

// flags for display/cursor shift
#define LCD_DISPLAYMOVE 0x08
#define LCD_CURSORMOVE 0x00
#define LCD_MOVERIGHT 0x04
#define LCD_MOVELEFT 0x00

// flags for function set
#define LCD_8BITMODE 0x10
#define LCD_4BITMODE 0x00
#define LCD_2LINE 0x08
#define LCD_1LINE 0x00
#define LCD_5x10DOTS 0x04
#define LCD_5x8DOTS 0x00

uint8_t lcdCurrentPins;
uint8_t lcdCurrentLine;
uint8_t lcdFunctions;
uint8_t lcdDisplayControl;
uint8_t lcdDisplayMode;

void initLcd();
void setLcdFunctions(uint8_t func);
void setLcdPin(uint8_t pin,uint8_t val);
void lcdSend(uint8_t value, uint8_t mode);
void lcdSendOnly4(uint8_t value, uint8_t mode);
void lcdWrite4Bits(uint8_t value);
void lcdPulseEnable();
void lcdCommand(uint8_t value);
void lcdCommand4bit(uint8_t value);
void lcdSetCursor(uint8_t col, uint8_t row);
void lcdDisplay();
void lcdClear();
//High level functions
void ldcSetCursorBlinking(uint8_t val);
void lcdWrite(uint8_t value);
void lcdWriteText(const char *s);
void lcdSetAutoscroll(uint8_t val); //Doesn't work yet!
void lcdSetCursorVisible(uint8_t val);


#endif /* LCDSHIFT_H_ */