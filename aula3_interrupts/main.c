/*
 * main.c
 * Created: 3/13/2026 2:22:41 PM
 *  Author: Matheus T Machado
 */ 
#define F_CPU 16000000
#include <xc.h>
#include "avr/interrupt.h"
#include "util/delay.h"

int gLedFlag = 0; //variável global contador
int gPD2State = 0;
int gPD3State = 0;

ISR(INT0_vect)
{
	gLedFlag =1;
}

ISR(INT1_vect)
{
	gLedFlag =1;
}

ISR(PCINT2_vect)
{
	if((PIND & (1<<PIND2)) != 0)
	{
		//Pino D2 está 
	}
}

void EXTINT_config()
{
	EICRA = (0<<ISC01)|(1<<ISC00) //INT0 configurado pra ambas as bordas
	| (1<<ISC11)|(1<<ISC10); //INT1 configurado pra borda de subida
	EIMSK = (1<<INT1)|(1<<INT0); //INT1 habilitada, INT0 desabilitada
}

void PCINT_config()
{
	PCMSK2 |= (1<<PCINT18)|(1<<PCINT19); //Habilita PCINT18 e PCINT19 (equivale a pinos PD2 e PD3)
	PCICR |= (1<<PCIE2); //Habilita grupo 2 (equivale porta D)
	
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