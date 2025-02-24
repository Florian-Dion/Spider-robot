#include <tinyprintf.h>
#include <stm32f4/rcc.h>
#include <stm32f4/gpio.h>
#include <stm32f4/nvic.h>
#include <stm32f4/exti.h>
#include <stm32f4/syscfg.h>
#include <stm32f4/tim.h>
#include <stm32f4/adc.h>

/************************************PARAMETRE POUR LES TIMER DES SERVOMOTEURS****************************** */
#define SERVO_PSC (14-1)
#define SERVO_PERIOD (60000-1)
#define SERVO_05MS ((SERVO_PERIOD+1)/40)
#define SERVO_1MS ((SERVO_PERIOD+1)/20)
/********************************************************************************************************** */

/************************************PARAMETRE POUR TIMER 13*********************************************** */
#define PSC_20MS (14-1)
#define DELAY_20MS (60000-1)
/********************************************************************************************************** */

void set_servo1B(int n){TIM8_CCR1 = SERVO_05MS + (n*(SERVO_1MS/900));}

void set_servo3A(int n){TIM2_CCR2 = SERVO_05MS + (n*(SERVO_1MS/900));}
void set_servo4A(int n){TIM2_CCR3 = SERVO_05MS + (n*(SERVO_1MS/900));}
void set_servo4C(int n){TIM2_CCR4 = SERVO_05MS + (n*(SERVO_1MS/900));}


void set_servo3C(int n){TIM3_CCR1 = SERVO_05MS + (n*(SERVO_1MS/900));}
void set_servo3B(int n){TIM3_CCR2 = SERVO_05MS + (n*(SERVO_1MS/900));}
void set_servo1A(int n){TIM3_CCR3 = SERVO_05MS + (n*(SERVO_1MS/900));}
void set_servo4B(int n){TIM3_CCR4 = SERVO_05MS + (n*(SERVO_1MS/900));}


void set_servo2A(int n){TIM4_CCR1 = SERVO_05MS + (n*(SERVO_1MS/900));}
void set_servo2C(int n){TIM4_CCR2 = SERVO_05MS + (n*(SERVO_1MS/900));}
void set_servo1C(int n){TIM4_CCR3 = SERVO_05MS + (n*(SERVO_1MS/900));}
void set_servo2B(int n){TIM4_CCR4 = SERVO_05MS + (n*(SERVO_1MS/900));}



// TIM3 init on GPIOB PB3, PB10, PB11
void init_TIM2(){
    GPIOB_MODER = REP_BITS(GPIOB_MODER, 3*2, 2, GPIO_MODER_ALT);
    GPIOB_MODER = REP_BITS(GPIOB_MODER, 10*2, 2, GPIO_MODER_ALT);
    GPIOB_MODER = REP_BITS(GPIOB_MODER, 11*2, 2, GPIO_MODER_ALT);
    GPIOB_AFRL = REP_BITS(GPIOB_AFRL, 3 * 4, 4, 1);
    GPIOB_AFRH = REP_BITS(GPIOB_AFRH, (10-8) * 4, 4, 1);
    GPIOB_AFRH = REP_BITS(GPIOB_AFRH, (11-8) * 4, 4, 1);

    //TIM3 init
    TIM2_CCMR1 = TIM_OC2M_PWM1;
    TIM2_CCMR2 = TIM_OC3M_PWM1 | TIM_OC4M_PWM1;
    TIM2_CCER = TIM_CC2E | TIM_CC3E | TIM_CC4E;

    TIM2_CR1 = 0;
    TIM2_PSC = SERVO_PSC;
    TIM2_ARR = SERVO_PERIOD;
    TIM2_EGR = TIM_UG;
    TIM2_SR = 0;
    set_servo3A(1800);
    set_servo4A(200);
    set_servo4C(1200);
    TIM2_CR1 = TIM_CEN | TIM_ARPE;

    printf("TIM2 init done\n");
}


// TIM3 init on GPIOB PB4, PB5, PC8, PB1
void init_TIM3(){
    GPIOB_MODER = REP_BITS(GPIOB_MODER, 4*2, 2, GPIO_MODER_ALT);
    GPIOB_MODER = REP_BITS(GPIOB_MODER, 5*2, 2, GPIO_MODER_ALT);
    GPIOC_MODER = REP_BITS(GPIOC_MODER, 8*2, 2, GPIO_MODER_ALT);
    GPIOB_MODER = REP_BITS(GPIOB_MODER, 1*2, 2, GPIO_MODER_ALT);
    GPIOB_AFRL = REP_BITS(GPIOB_AFRL, 4 * 4, 4, 2);
    GPIOB_AFRL = REP_BITS(GPIOB_AFRL, 5 * 4, 4, 2);
    GPIOC_AFRH = REP_BITS(GPIOC_AFRH, (8-8) * 4, 4, 2);
    GPIOB_AFRL = REP_BITS(GPIOB_AFRL, 1 * 4, 4, 2);

    //TIM3 init
    TIM3_CCMR1 = TIM_OC1M_PWM1 | TIM_OC2M_PWM1;
    TIM3_CCMR2 = TIM_OC3M_PWM1 | TIM_OC4M_PWM1;
    TIM3_CCER = TIM_CC1E | TIM_CC2E | TIM_CC3E | TIM_CC4E;
    TIM3_CR1 = 0;
    TIM3_PSC = SERVO_PSC;
    TIM3_ARR = SERVO_PERIOD;
    TIM3_EGR = TIM_UG;
    TIM3_SR = 0;
    set_servo3C(900);
    set_servo3B(900);
    set_servo1A(900);
    set_servo4B(1100);
    TIM3_CR1 = TIM_CEN | TIM_ARPE;

    printf("TIM3 init done\n");
}

// TIM4 init on GPIOD PD12, PD13, PD14, PD15
void init_TIM4(){
    GPIOD_MODER = REP_BITS(GPIOD_MODER, 12*2, 2, GPIO_MODER_ALT);
    GPIOD_MODER = REP_BITS(GPIOD_MODER, 13*2, 2, GPIO_MODER_ALT);
    GPIOD_MODER = REP_BITS(GPIOD_MODER, 14*2, 2, GPIO_MODER_ALT);
    GPIOD_MODER = REP_BITS(GPIOD_MODER, 15*2, 2, GPIO_MODER_ALT);
    GPIOD_AFRH = REP_BITS(GPIOD_AFRH, (12 - 8) * 4, 4, 2);
    GPIOD_AFRH = REP_BITS(GPIOD_AFRH, (13 - 8) * 4, 4, 2);
    GPIOD_AFRH = REP_BITS(GPIOD_AFRH, (14 - 8) * 4, 4, 2);
    GPIOD_AFRH = REP_BITS(GPIOD_AFRH, (15 - 8) * 4, 4, 2);

    //TIM4 init
    TIM4_CCMR1 = TIM_OC1M_PWM1 | TIM_OC2M_PWM1;
    TIM4_CCMR2 = TIM_OC3M_PWM1 | TIM_OC4M_PWM1;
    TIM4_CCER = TIM_CC1E | TIM_CC2E | TIM_CC3E | TIM_CC4E;
    TIM4_CR1 = 0;
    TIM4_PSC = SERVO_PSC;
    TIM4_ARR = SERVO_PERIOD;
    TIM4_EGR = TIM_UG;
    TIM4_SR = 0;
    set_servo2A(1200);
    set_servo2C(400);
    set_servo1C(700);
    set_servo2B(1600);
    TIM4_CR1 = TIM_CEN | TIM_ARPE;

    printf("TIM4 init done\n");
}


// TIM8 init on GPIOC PC6
void init_TIM8(){
    GPIOC_MODER = REP_BITS(GPIOC_MODER, 6*2, 2, GPIO_MODER_ALT);
    GPIOC_AFRL = REP_BITS(GPIOC_AFRL, 6 * 4, 4, 3);

    TIM8_CR1 = 0;
    TIM8_PSC = SERVO_PSC * 2;
    TIM8_ARR = SERVO_PERIOD;
    TIM8_CCMR1 |= TIM_OC1M_PWM1;
    TIM8_CCER |= TIM_CC1E;
    TIM8_BDTR |= TIM1_MOE;
    set_servo1B(1800);
    TIM8_CR1 |= TIM_CEN;

    printf("TIM8 init done\n");
}

/**
 * Initialiser les servomoteurs sur les timers ainsi que le timer qui va générer une interruption toutes les n ms
 */
void init_servo(){

    printf("Init Servo...\n");

    // RCC init
    RCC_AHB1ENR |= RCC_GPIOAEN;
    RCC_AHB1ENR |= RCC_GPIOBEN;
    RCC_AHB1ENR |= RCC_GPIOCEN;
    RCC_AHB1ENR |= RCC_GPIOEEN;
    RCC_AHB1ENR |= RCC_GPIODEN;

    RCC_APB2ENR |= RCC_TIM8EN;
    RCC_APB1ENR |= RCC_TIM3EN;
    RCC_APB1ENR |= RCC_TIM4EN;
    RCC_APB1ENR |= RCC_TIM2EN;
    RCC_APB1ENR |= RCC_TIM13EN;

    printf("RCC init done\n");

    DISABLE_IRQS;

    init_TIM3();
    init_TIM2();
    init_TIM4();
    init_TIM8();

    /**
     * Un timer qui va générer une interruption toutes les n ms pour update les servomoteurs
     */
    //
    TIM13_CR1 = 0;
    TIM13_PSC = PSC_20MS;
    TIM13_ARR = DELAY_20MS;
    TIM13_EGR = TIM_UG;
    TIM13_SR = 0;
    TIM13_DIER = TIM_UIE;
    TIM13_CR1 = TIM_CEN | TIM_ARPE;

    printf("End Init Servo\n");

}