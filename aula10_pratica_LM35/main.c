/*
 * main.c
 *
 * Created: 6/5/2026 2:02:07 PM
 *  Author: Matheus T Machado
 */

/*Objetivo: Realizar leituras do LM35 com ADC, com taxa de amostragem de 4 Hz, utilizando o TMR1 como fonte de disparo do ADC (modo auto trigger)
Obs: Utilizar Vref interno*/

#define F_CPU 16000000
#include <xc.h>
#include <avr/interrupt.h>

uint16_t gTemperatura = 0;

ISR(ADC_vect)
{
	 uint16_t tResultado = ADC;
	 //LM35: 10 mV/°C, Vref = 1,1V (1100 mV)
	 // T(°C) = (tResult * 1100) / (1024 * 10)
	 gTemperatura = ((uint32_t)tResultado * 1100) / 1024 / 10;
}

int main(void)
{
	DDRB |= (1<<DDB4); //Define o PB4 como saída
	PORTB |= (1<<PORTB4); //Acende lampada
	
	ADMUX = (1<<REFS1)|(1<<REFS0) //Vref = interno (1,1V)
		  | (0<<MUX3)|(1<<MUX2)|(0<<MUX1)|(1<<MUX0); //ADC5
	
	ADCSRA  = (1<<ADEN) //Habilita ADC
			|(1<<ADATE)	//Habilita auto trigger
			|(1<<ADIE) //Habilita interrupção
			|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);  //Prescaler = 128 (fadc = 125 kHz)
	
	//Configuração da fonte do auto trigger (timer 1) tabela 23-6 datasheet
	ADCSRB = (1<<ADTS2)
			|(0<<ADTS1)
			|(1<<ADTS0);
	
	DIDR0 = (1<<ADC5D); // Desabilitar entrada digital no A5
	
	 //Configuração do Timer1 (CTC, 4 Hz)
	 TCCR1A = 0;
	 TCCR1B = (1<<WGM12) // Modo CTC, topo em OCR1A
	 | (1<<CS12)|(0<<CS11)|(1<<CS10);  // Prescaler = 1024
	 OCR1A  = 3905;  //4Hz
	 OCR1B  = 3905;  //Necessário para o trigger
	 TCNT1  = 0;
	 
	 sei(); //interrupções globais
	
    while(1)
    {
        
    }
}