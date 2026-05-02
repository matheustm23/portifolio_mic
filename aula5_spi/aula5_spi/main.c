/*
 * main.c
 *
 * Created: 4/24/2026 3:49:51 PM
 *  Author: Matheus T Machado
 */ 

#define SPI_BUFFER_SIZE 4
#define F_CPU 16000000
#include <xc.h>
#include "spi.h"
#include "util/delay.h"

uint8_t gTransmitBuffer[SPI_BUFFER_SIZE];
uint8_t gReceiveBuffer[SPI_BUFFER_SIZE];

int main(void)
{
	SPI_config();
	
    while(1)
    {
        SPI_transceiveBuffer(gTransmitBuffer, gReceiveBuffer, SPI_BUFFER_SIZE);
		_delay_ms(100);
    }
}