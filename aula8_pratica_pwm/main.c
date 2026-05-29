/*
 * main.c
 *
 * Created: 5/22/2026 2:32:43 PM
 *  Author: Matheus T Machado
 */
#define F_CPU 8000000

#include <xc.h>
#include <avr/io.h>         
#include <util/delay.h>

uint8_t gPWM = 50; // Variável do PWM iniciando em 50%

int main(void)
{
	DDRD |= (1<<DDD5); //PD5 como saída (PWM)
	
	DDRC &= ~((1<<DDC0) | (1<<DDC1)); //PC0 e PC1 como entrada (botões)

	TCCR0A =
	(1<<COM0B1) |	//Habilita PWM não inversor no canal OC0B
	(1<<WGM01)  |   //Configura modo Fast PWM
	(1<<WGM00);     //Configura modo Fast PWM

	TCCR0B =
	(1<<WGM02) |    //Completa configuração do modo Fast PWM com TOP em OCR0A
	(1<<CS01);      //Prescaler = 8

	OCR0A = 99; //Define TOP = 99 (frequência PWM ? 10 kHz)
	
	OCR0B = gPWM; // Define duty cycle inicial em 50%

	while (1)                
	{
		if (!(PINC & (1<<PINC0))) //Verifica se botão em PC0 foi pressionado
		{
			if (gPWM < 99) //Verifica se PWM ainda não chegou no máximo
			{
				gPWM++; //Incrementa PWM em 1%
				
				OCR0B = gPWM; //Atualiza duty cycle do PWM
			}
			_delay_ms(200);
		}

		if (!(PINC & (1<<PINC1))) //Verifica se botão em PC1 foi pressionado
		{
			if (gPWM > 0) //Verifica se PWM ainda não chegou no mínimo
			{
				gPWM--;  //Decrementa PWM em 1%
				
				OCR0B = gPWM; //Atualiza duty cycle do PWM
			}
			_delay_ms(200);
		}
	}
}