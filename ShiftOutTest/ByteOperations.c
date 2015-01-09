/*
 * CFile1.c
 *
 * Created: 2015-01-09 21:18:50
 *  Author: Krzysztof
 */ 

#include "ByteOperations.h"

uint8_t getNthByte(uint8_t number, uint8_t bit){
	uint8_t masked_n = number & (1 << bit);
	return masked_n >> bit;
}