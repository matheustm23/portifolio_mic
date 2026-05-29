/*
 * main.c
 *
 * Created: 5/15/2026 2:49:47 PM
 *  Author: Matheus T Machado
 */

#define F_CPU 8000000
#include <xc.h>
#include "avr/interrupt.h"
#include "util/delay.h"

uint8_t gPWMa = 0;
uint8_t gPWMb = 255;

int main(void)
{
	DDRD = (1<<DDD6)|(1<<DDD5);
	TCCR0A = (0<<COM0A0)|(1<<COM0A1) //OC0A PWM não-inversor
		   | (0<<COM0B0)|(1<<COM0B1) //0C0B PWM não-inversor
		   | (1<<WGM01)|(1<<WGM00); //Modo Fast-PWM (modo 7) com TOP=OCR0A
	TCCR0B = (0<<WGM02)|(0<<CS02)|(1<<CS01)|(0<<CS00); //Prescaler de 8
	OCR0A = 99; //período de 100us
	
    while(1)
    {
		gPWM++;
		if(gPWM>99) gPWM=0;
		OCR0B = gPWMa;
		_delay_ms(10);
    }
}