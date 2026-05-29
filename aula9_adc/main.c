/*
 * main.c
 *
 * Created: 5/29/2026 4:41:41 PM
 *  Author: Matheus T Machado
 */ 

#define F_CPU 16000000
#include <xc.h>

//Objetivo: medir a tensão de uma bateria e acender um led amarelo se ela estiver abaixo de 3,0V ou um LED vermelho se ela estiver acima de 3,8 (carregando)
//Obs: bateria no pino ADC7

int main(void)
{
	ADMUX = (0<<REFS1)|(1<<REFS0)						//Utilizar vref=avcc (5V)
		  | (0<<MUX3)|(1<<MUX2)|(1<<MUX1)|(1<<MUX0);	//Bateria no pino ADC7
		  
	ADCSRA = (1<<ADEN)|(0<<ADATE)						//Ligar ADC, modo single conversion (sem auto trigger)
		   | (0<<ADIE)									//Desabilita interrupção
		   | (1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);			//Prescaler de 128 (fadc=125kHZ)
		   
	ADCSRB = 0;											//Ignorar, não estamos usando auto trigger
	
	DIDR0 = 0;											//Ignorar, não estamos usando portas ADC0-ADC5
	
	DDRB = (1<<DDB2)|(1<<DDB1)|(1<<DDB0);
    
	while(1)
    {
        ADCSRA |= (1<<ADSC); //Disparar conversão
		while(ADCSRA & (1<<ADSC)); //Esperar conclusão, ADCS retorna sozinho para 0
		uint16_t tResult = ADC; //Armazena resultado na variável tResult
		
		//Resultado vai estar entre 0 e 1023
		PORTB = 0; //Apagar todos os leds
		if(tResult < 614) //n=2^10 * 
		{
			PORTB |= (1<<PORTB0);//Acender LED amarelo (descarregamento)
		}
		
		else
		if(tResult > 778)
		{
			PORTB |= (1<<PORTB2);//Acender LED vermelho (carregamento)
		}
		
		else
		{
			PORTB |= (1<<PORTB1);//Acender LED verde
		}
		
    }
}