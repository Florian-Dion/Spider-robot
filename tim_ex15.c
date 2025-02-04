#include <tinyprintf.h>
#include <stm32f4/rcc.h>
#include <stm32f4/gpio.h>
#include <stm32f4/nvic.h>
#include <stm32f4/exti.h>
#include <stm32f4/syscfg.h>
#include <stm32f4/tim.h>
#include <stm32f4/adc.h>

#define SERVO_PSC 14
#define SERVO_PERIOD 60000
#define SERVO_05MS 1500
#define SERVO_1MS 3000

#define TIMER_PSC 1000
#define TIMER_DELAY APB1_CLK / TIMER_PSC / 50

volatile short s = 1;
volatile int i = 0;

void handle_TIM4(){
	TIM4_SR = 0;
	NVIC_ICPR(TIM4_IRQ >> 5) = 1 <<(TIM4_IRQ & 0x1f);
	set_servo(i);
	printf("%d",i);
	i= i+s*20;
	if (i>1800 || i<0)
		s=s*-1;
}

void init_TIM4(){
	TIM4_CR1 = 0;
	TIM4_PSC = TIMER_PSC-1;
	TIM4_ARR = TIMER_DELAY;
	TIM4_EGR = TIM_UG;
	TIM4_SR = 0;
	NVIC_ISER(TIM4_IRQ >> 5) = 1 << (TIM4_IRQ & 0x1f);
	TIM4_DIER=TIM_UIE;
	ENABLE_IRQS;
	TIM4_CR1 = TIM_CEN;
}

int main() {
	printf("\nStarting...\n");

	// RCC init
	RCC_AHB1ENR |= RCC_GPIOAEN;
	RCC_AHB1ENR |= RCC_GPIODEN;
	RCC_APB1ENR |= RCC_TIM3EN;
	RCC_APB1ENR |= RCC_TIM4EN;
	RCC_APB2ENR |= RCC_ADC1EN;

	// initialization

	DISABLE_IRQS;
	NVIC_ICER(TIM4_IRQ >> 5) = 1 << (TIM4_IRQ & 0x1f);
	NVIC_IRQ(TIM4_IRQ) = (uint32_t) handle_TIM4;
	NVIC_IPR(TIM4_IRQ) = 0;
	init_servo();
	init_TIM4();
	// main loop
	printf("Endless loop!\n");
	
	while(1) {		
	}
}
