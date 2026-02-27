//Autor: Matheus
#define F_CPU 16000000
#include "gpio.c"
#include <xc.h>
#include "util/delay.h"

void GPIO_initialize();
{
	DDRB = (1<<DDB0); //configura o pino PB0 como saida
}

void GPIO_blinked();
{
	PORTB |= (1<<PORTB0); //aciona PB0
	_delay_ms(300);
	PORTB &= ~(1<<PORTB0); //desaciona PB0
	_delay_ms(700);
}
