/*
 * main.c
 *
 * Created: 3/27/2026 1:54:26 PM
 *  Author: Matheus
 */ 

#include <xc.h>
#define F_CPU 16000000
#include <util/delay.h>

//buffer bytes
uint8_t gMessage[4] = {200, 100, 50, 94}; //ultimo byte é checksum

int main(void)
{
	UBRR0=103; //Configurar BAUD Rate para 9600
	UCSR0A=(0<<U2X0);
	UCSR0B=(1<<TXEN0)|(0<<UCSZ02) ;  //Habilita transmissor
	UCSR0C=(0<<UMSEL01)|(0<<UMSEL00) //Modo assíncrono
		  |(1<<UPM01)|(0<<UPM00)     //Habilita paridade par
		  | (0<<USBS0)			     //1 bit de stop
		  |(1<<UCSZ01)|(1<<UCSZ00);  //Frames de 8 bits
	
    while(1)
    {
		int i;
		for(i=0; i<4; i++)
		{
			UDR0= gMessage[i];
			_delay_ms(2);
		}
		
	   _delay_ms(10);
    }
	
	
}