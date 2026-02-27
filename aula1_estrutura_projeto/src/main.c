//Autor: Matheus
#include "gpio.h"
#include <xc.h>
#include "usart.h"

int main(void)
{
	//Inicialização dos periféricos
	GPIO_initialize();
	USART_initialize();
	while(1)
	{
		GPIO_blinked();
		USAR_send();
	}
}