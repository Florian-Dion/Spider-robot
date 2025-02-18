#include <tinyprintf.h>
#include <stm32f4/src/usart.c>

//#include <stm32f4/src/init.c>

#define MAX 4095

// GPIOC

// GPIOA
#define POTENT 4

void set_idle(){//position de base
    //groupe impair
    set_servo1A(900);
    set_servo1B(600);
    set_servo1C(600);
    set_servo3A(1300);
    set_servo3B(1400);
    set_servo3C(1200);
    //set_servo5A(1100);
    //set_servo5B(600);
    //set_servo5C(600);
    //groupe pair
    set_servo2A(1400);
    set_servo2B(1400);
    set_servo2C(600);
    set_servo4A(900);
    set_servo4B(600);
    set_servo4C(600);
    //set_servo6A(1100);
    //set_servo6B(1400);
    //set_servo6C(1200);
}

void init_photo_res(){
	GPIOA_MODER = REP_BITS(GPIOA_MODER, POTENT*2, 2, GPIO_MODER_ANA);
	ADC1_SQR3 = POTENT;
	ADC1_CR1 = ADC_12b | ADC_SCAN;
	ADC1_CR2 = ADC_ADON;
	ADC1_CR2 |= (1<<1);
}

int main(void) {
    printf("Initialisation...\n");
    init_servo();           // Initialiser les servo
    stm32f4_usart1_init();  // Initialiser l'USART
    printf("USART1 initialise!\n");
    //configure_hc06();       // Configurer le HC-06
    //printf("HC-06 configuré!\n");
    
    //set_idle();
    
    while (1) {
    }
}
