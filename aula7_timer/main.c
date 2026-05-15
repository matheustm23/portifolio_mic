/*
 * main.c
 *
 * Created: 5/15/2026 2:49:47 PM
 *  Author: Matheus T Machado
 */ 
#define F_CPU 8000000
#include <xc.h>
#include "avr/interrupt.h"

ISR(TIMER0_COMPA_vect)
{
	PORTB |= (1<<PORTB0); //set PB0
}

ISR(TIMER0_COMPB_vect)
{
	PORTB &= ~(1<<PORTB0); //reset PB0
}

int main(void)
{
	DDRB = (1<<DDB0);
	TCCR0A = (1<<WGM01)|(0<<WGM00); //Modo CTC
	TCCR0B = (1<<WGM02)|(0<<CS02)|(1<<CS01)|(0<<CS00); //Prescaler de 8
	OCR0A = 249; //Contagem até 250us, assumindo clock de 1MHz 
	OCR0B = 99; //transição da onda, razão de 40%
	TIMSK0 = (1<<OCIE0A)|(1<<OCIE0B); //Habilita interrupção A e B de comparção de saída
	sei();
	
    while(1)
    {
        
    }
}