/*
 * main.c
 *
 * Created: 3/13/2026 2:22:41 PM
 *  Author: Matheus T Machado
 */ 
#define F_CPU 16000000
#include <xc.h>
#include "avr/interrupt.h"
#include "util/delay.h"

ISR(INT0_vect) 
{
	PORTC ^=(1<<PORTC0); //Alterna Led
	_delay_ms(100);
	PORTC=0;
}

int main(void)
{
	DDRC =(1<<DDC0); //configura pino PC0 como saída;
	EICRA = (1<<ISC01)|(1<<ISC00); //configurando a solicitação de interrupção: borda de subida
	EIMSK = (0<<INT1)|(1<<INT0); //INT0 habilitada, INT1 desabilitada
	sei(); //habilita as interrupções globais
	
    while(1)
    {
        //TODO:: Please write your application code 
    }
}