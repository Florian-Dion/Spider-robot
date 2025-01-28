/* Embedded Systems - Exercise 15 */

#include <tinyprintf.h>
#include <stm32f4/rcc.h>
#include <stm32f4/gpio.h>
#include <stm32f4/nvic.h>
#include <stm32f4/exti.h>
#include <stm32f4/syscfg.h>
#include <stm32f4/tim.h>
#include <stm32f4/adc.h>


// GPIOD
#define GREEN_LED	12
#define ORANGE_LED	13
#define RED_LED		14
#define BLUE_LED	15

// GPIODA
#define USER_MOT1	0
#define USER_MOT2	1
#define USER_MOT3	2

#define SERVO_PSC 14
#define SERVO_PERIOD 60000
#define SERVO_05MS 1200
#define SERVO_1MS 2400

#define TIMER_PSC 1000
#define TIMER_DELAY APB1_CLK / TIMER_PSC / 50

volatile short s1 = 1,s2 = 1,s3 = 1;
volatile int i1 = 0,i2 = 800,i3 = 1500;


void set_servo1(int n){
	TIM3_CCR1 = SERVO_05MS + (n*(SERVO_1MS/900));
}
void set_servo2(int n){
	TIM3_CCR2 = SERVO_05MS + (n*(SERVO_1MS/900));
}

void init_servo(){
	GPIOC_MODER = REP_BITS(GPIOC_MODER,2*6,2,GPIO_MODER_ALT);
	GPIOC_MODER = REP_BITS(GPIOC_MODER,2*7,2,GPIO_MODER_ALT);
	GPIOC_AFRL = REP_BITS(GPIOC_AFRL,6*4,4,2);
	GPIOC_AFRL = REP_BITS(GPIOC_AFRL,7*4,4,2);
	TIM3_CR1 = 0;
	TIM3_CCMR1 |= TIM_OC1M_PWM1 | TIM_OC2M_PWM1;
	TIM3_CCER |= TIM_CC1E | TIM_CC2E;
	TIM3_CCR1 = SERVO_1MS;
	TIM3_PSC = SERVO_PSC -1;
	TIM3_ARR = SERVO_PERIOD*2;
	TIM3_EGR = TIM_UG;
	TIM3_CR1 = TIM_CEN;
}

int main() {
	printf("\nStarting...\n");

	// RCC init
	RCC_AHB1ENR |= RCC_GPIOAEN;
	RCC_AHB1ENR |= RCC_GPIOCEN;
	RCC_AHB1ENR |= RCC_GPIODEN;
	RCC_APB1ENR |= RCC_TIM3EN;
	RCC_APB1ENR |= RCC_TIM4EN;
	RCC_APB2ENR |= RCC_ADC1EN;

	// initialization

	DISABLE_IRQS;
	init_servo();
	// main loop
	printf("Endless loop!\n");
	
	while(1) {
		for(int k = 0; k< 500000; k++) NOP;
		set_servo1(i1);
		set_servo2(i2);
		printf("%d ",i2);
		i1= i1+s1*6;
		if (i1>=1800 || i1<=0)
			s1=s1*-1;
		i2= i2+s2*6;
		if (i2>=1800 || i2<=0)
			s2=s2*-1;		
	}
}
