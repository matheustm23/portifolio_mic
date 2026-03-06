/*
 * main.c
 * Created: 3/6/2026 2:36:37 PM
 *  Author: Matheus Machado
 */ 

#define F_CPU 16000000
#include <xc.h>
#include "util/delay.h"

/* @brief O que este código faz:
Pisca um led ligado ao pino PC2 enquanto a 
chave ligada ao pino PD3 estiver pressionada
*/

void atividade1()
{
	DDRC |=(1<<DDC2); //Configurar o pino PC2 como saída
	DDRD &=(1<<DDD3); //Configura o pino PD3 como entrada
	
	while(1)
	{
		if((PIND & (1<<PIND3)) != 0) //Ler o valor do pino D3
		{
			//Chave pressionada
			PORTC |= (1<<PORTC2); //acende led
			_delay_ms(300);
			PORTC &= ~(1<<PORTC2); //apaga led
			_delay_ms(700);
		}
		
		
		else
		{
			//Chave aberta
			PORTC &= ~(1<<PORTC2); //apaga led
			_delay_ms(300);
		}
	}
}

/* @brief Controla 6 leds (PB0 a PB5) em 
uma logica de pinheirinho de natal */

void atividade2()
{
	//Configurando pinos PB0-PB5 como saida
	DDRB |= ((1<<DDB5) | (1<<DDB4) | (1<<DDB3) | (1<<DDB2) | (1<<DDB1) | (1<<DDB0));
	uint8_t tState =1; //Guarda estado de acionamento dos leds
	while(1)
	{
		tState = tState << 1;
		if(tState == 0b01000000)
		{
			tState=1;
		}
		
		if((PIND & (1<<PIND3))!=0)
		{
			PORTB =tState;
		}
		
		else
		{
			//Chave aberta
			PORTB =0;
		}
		_delay_ms(200);
	}
}

int main(void)
{
	atividade2();
}