/*
 * sm28vlt32.c
 *
 * Created: 24/04/2026 16:40:05
 *  Author: Matheus T Machado
 */ 

#include "spi.h"
#include <xc.h>

uint8_t SM28VLT32_config()
{
	DDRB |= (1<<DDB0); //Configura chipset como saida
}

uint8_t SM28VLT32_writeWord(uint32_t pAddress, uint16_t pData)
{
	uint8_t tTransmitBuffer[7];
	uint8_t tReceiveBuffer[7];
	
	PORTB &= ~(1<<PORTB0); //chip select = 0
	
	tTransmitBuffer[0] = 0x17; //comando de escrita
	tTransmitBuffer[1] = (pAddress & 0x00FF0000) >> 16;
	tTransmitBuffer[2] = (pAddress & 0x0000FF00) >> 8;
	tTransmitBuffer[3] = (pAddress & 0x000000FF) >> 0;
	tTransmitBuffer[4] = (pAddress & 0xFF00) >> 8;
	tTransmitBuffer[5] = (pAddress & 0x00FF) >> 0;
	tTransmitBuffer[6] = 0x00; //dummy
	
	SPI_transceiveBuffer(tTransmitBuffer, tReceiveBuffer, 7);
	
	PORTB |= (1<<PORTB0); //chip select = 1
	
	return tReceiveBuffer[0];
	
}