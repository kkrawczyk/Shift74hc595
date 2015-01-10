/*
 * IncFile1.h
 *
 * Created: 2015-01-09 22:30:40
 *  Author: Krzysztof
 */ 


#ifndef INCSHIFT74HC595_H_
#define INCSHIFT74HC595_H_

#include "ByteOperations.h"

#define SHIFT_CLCK PB1
#define SHIFT_LATCH PB0
#define SHIFT_DATA PB2

void initShift();
/* 8 is lowest byte */
void writeBytes(uint8_t value);

void writeBytesRCLK(uint8_t value, uint8_t pushRCLK);



#endif /* INCSHIFT74HC595_H_ */