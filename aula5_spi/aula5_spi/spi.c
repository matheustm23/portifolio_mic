/*
 * spi.c
 *
 * Created: 24/04/2026 15:50:58
 *  Author: Matheus T Machado
 */ 
#include <xc.h>

void SPI_config()
{
	DDRB |= (1<<DDB3)|(1<<DDB5);
	SPCR = (0<<SPIE)|(1<<SPE) //Desabilita interrupção e habilita SPI
		 | (0<<DORD)|(1<<MSTR) //Ordem: MSB
		 | (0<<CPOL)|(0<<CPHA) //SPI modo 0
		 | (0<<SPR1)|(1<<SPR0); //Dividor 16, freq=1MHz
		 
	SPSR=(0<<SPI2X); //Completa configuração pra freq de 1MHz
	
}

uint8_t SPI_transceive(uint8_t pTransmittedByte)
{
	uint8_t rReceivedByte;
	SPDR = pTransmittedByte; //Inicia uma transmissão
	while((SPSR & (1<<SPIF) == 0)); //poll do SPIF, bloqueia enquanto SPIF for igual a zero
	uint8_t tReceivedByte = SPDR;
	return tReceivedByte;
}

void SPI_transceiveBuffer(uint8_t *pTransmitBuffer, uint8_t *pReceiveBuffer, uint16_t pSize)
{
	uint8_t *tTransmitPtr = pTransmitBuffer;
	uint8_t *tReceivePtr = pReceiveBuffer;
	uint16_t tCounter;
	
	for(tCounter=0; tCounter<pSize; tCounter++)
	{
		*tReceivePtr = SPI_transceiveByte(*tTransmitPtr);
		tReceivePtr++;
		tTransmitPtr++;
	}
}

