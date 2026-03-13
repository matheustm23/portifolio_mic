/*
 * main.c
 * Created: 3/13/2026 2:22:41 PM
 *  Author: Matheus T Machado
 */ 
#define F_CPU 16000000
#include <xc.h>
#include "avr/interrupt.h"
#include "util/delay.h"

int gCount = 0;

ISR(INT0_vect) 
{
	PORTC ^=(1<<PORTC0);
	_delay_ms(100);
	PORTC=0;
}

ISR(INT1_vect)
{
	gCount++;
	if(gCount == 3)
	{
		PORTC ^=(1<<PORTC0);
		_delay_ms(100);
		PORTC=0;
		gCount=0;
	}
	
}

int main(void)
{
	DDRC =(1<<DDC0); //configura pino PC0 como saída;
	EICRA = (0<<ISC01)|(1<<ISC00) //INT0 configurado pra ambas as bordas
	      | (1<<ISC11)|(1<<ISC10); //INT1 configurado pra borda de subida
	EIMSK = (1<<INT1)|(1<<INT0); //INT1 habilitada, INT0 desabilitada
	sei(); //habilita as interrupções globais
	
    while(1)
    {
        //TODO:: Please write your application code 
    }
}