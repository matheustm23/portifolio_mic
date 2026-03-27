/*
 * main.c
 * Created: 3/27/2026 3:55:02 PM
 *  Author: Matheus*/ 

#include <xc.h>

//FUNCAO PRINCIPAL: UART RX
int main(void)
{
	DDRB = (1<<DDB0); //Configura pino PB0 como saída
	UBRR0=103; //Configurar BAUD Rate para 9600
	UCSR0A=(0<<U2X0);
	UCSR0B=(1<<RXEN0)|(0<<UCSZ02) ;  //Habilita receptor
	UCSR0C=(0<<UMSEL01)|(0<<UMSEL00) //Modo assíncrono
		  |(1<<UPM01)|(0<<UPM00)     //Habilita paridade par
		  | (0<<USBS0)			     //1 bit de stop
		  |(1<<UCSZ01)|(1<<UCSZ00);  //Frames de 8 bits
	
    while(1)
    {
		while((UCSR0A & (1<<RXC0)) == 0); //esperar uma mensagem chegar
        uint8_t tReceivedByte = UDR0;
		if(tReceivedByte == 200)
		{
			PORTB |= (1<<PORTB0);
		}
		
		else
		{
			PORTB = 0;
		}
    }
}