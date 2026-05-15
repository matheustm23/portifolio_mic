/*
 * main.c
 *
 * Created: 5/15/2026 2:49:47 PM
 *  Author: Matheus T Machado
 */ 
#define F_CPU 8000000
#include <xc.h>
#include "avr/interrupt.h"

ISR(TIMER0_OVF_vect)
{
	PORTB ^= (1<<PORTB0); //Alterna PB0
}

int main(void)
{
	DDRB = (1<<DDB0);
	TCCR0A = (1<<WGM01)|(0<<WGM00); //Modo CTC
	TCCR0B = (1<<WGM02)|(0<<CS02)|(1<<CS01)|(0<<CS00); //Prescaler de 8
	OCR0A = 249; //Contagem até 250us, assumindo clock de 1MHz 
	TIMSK0 = (1<<TOIE0); //Habilita interrupção de overflow do timer 0
	sei();
	
    while(1)
    {
        
    }
}