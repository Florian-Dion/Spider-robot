/* Embedded Systems - Exercise 14 */

#include <tinyprintf.h>
#include <stm32f4/rcc.h>
#include <stm32f4/gpio.h>
#include <stm32f4/nvic.h>
#include <stm32f4/exti.h>
#include <stm32f4/syscfg.h>
#include <stm32f4/tim.h>
#include <stm32f4/adc.h>
//#include <stdlib.h>

#include <stm32f4/src/init.c>

#define MAX 4095

// GPIOC

// GPIOA
#define POTENT 4


void init_photo_res(){
	GPIOA_MODER = REP_BITS(GPIOA_MODER, POTENT*2, 2, GPIO_MODER_ANA);
	ADC1_SQR3 = POTENT;
	ADC1_CR1 = ADC_12b | ADC_SCAN;
	ADC1_CR2 = ADC_ADON;
	ADC1_CR2 |= (1<<1);
}


int main() {
	printf("\nStarting...\n");
	

	printf("Initialisation...\n");
    init_servo();           // Initialiser les servo
    //stm32f4_usart1_init();  // Initialiser l'USART
    printf("USART1 initialise!\n");

	// RCC init
	RCC_APB2ENR |= RCC_ADC1EN;

	// initialization
	init_photo_res();

	// main loop
	ADC1_CR2 |= ADC_SWSTART;
	printf("Endless loop!\n");
	while(1) {
		while (!(ADC1_SR & ADC_EOC));
		int x = ADC1_DR;
		//printf("ADC1_DR = %d\n", x);
		x = x/3 + 217;
		//printf("ADC1_DR / 3 = %d\n", x);
		//set_servo4C(x);
		
	}

}