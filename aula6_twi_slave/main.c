/*
 * main.c
 *
 * Created: 5/8/2026 3:57:36 PM
 *  Author: Matheus T Machado
 */ 

#define F_CPU 16000000
#include <xc.h>
#include "util/delay.h"
#include "avr/interrupt.h"

uint8_t gTWIData = 5;

ISR(TWI_vect)
{
	uint8_t tState = (TWSR & 0b111111000);
	switch(tState)
	{
		case 0x60: //Slave receiver
		{
			gTWIData=TWDR;
			TWCR = (1<<TWINT) | (1<<TWEN);
		}
	}
}

void TWI_slave_config()
{
	TWBR=12;  ////bit rate 400KHz
	TWSR=(0<<TWPS1)|(0<<TWPS0);	 //Prescaler=1
	TWAR = (0x55<<1)
	TWCR= (1<<TWEN)|(1<<TWIE);
	sei();
}

void TWI_master_write_byte(uint8_t pAdress, uint8_t pData)
{
	TWCR |= (1<<TWINT)|(1<<TWSTA)|(1<<TWEN); //Enviar condicao de start
	
	while((TWCR & (1<<TWINT))==0); //Esperar conclusao
	
	TWDR = (pAdress<<1) | 0; //1 para ler e 0 para escrita
	TWCR |= (1<<TWINT)|(1<<TWEN); //limpar twint para proximo passo
	
	while((TWCR & (1<<TWINT))==0); //Esperar conclusao
	
	uint8_t tState = TWSR & 0b11111000;
	
	switch(tState)
	{
		case 0x18: break; //ack recebido
		case 0x20: break; // nenhum ack recebido
		default: break;
	}
	
	TWCR |= (1<<TWINT)|(1<<TWSTO)|(1<<TWEN); //Envia condicao de stop
}

int main(void)
{
	TWI_master_config();
	_delay_ms(1000);
	while(1) 
	{
		TWI_master_write_byte(0x55, 'a');
		_delay_ms(1000);
	}
}