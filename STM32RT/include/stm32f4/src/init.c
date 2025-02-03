#include <tinyprintf.h>
#include <stm32f4/rcc.h>
#include <stm32f4/gpio.h>
#include <stm32f4/nvic.h>
#include <stm32f4/exti.h>
#include <stm32f4/syscfg.h>
#include <stm32f4/tim.h>

#define SERVO_PSC 14
#define SERVO_PERIOD 60000
#define SERVO_05MS 1200
#define SERVO_1MS 2400


void set_servo1A(int n){TIM2_CCR2 = SERVO_05MS + (n*(SERVO_1MS/900));}
void set_servo1B(int n){TIM2_CCR4 = SERVO_05MS + (n*(SERVO_1MS/900));}
void set_servo1C(int n){TIM2_CCR3 = SERVO_05MS + (n*(SERVO_1MS/900));}


void set_servo2A(int n){TIM4_CCR1 = SERVO_05MS + (n*(SERVO_1MS/900));}
void set_servo2B(int n){TIM4_CCR3 = SERVO_05MS + (n*(SERVO_1MS/900));}
void set_servo2C(int n){TIM4_CCR4 = SERVO_05MS + (n*(SERVO_1MS/900));}


void set_servo3A(int n){TIM3_CCR2 = SERVO_05MS + (n*(SERVO_1MS/900));}
void set_servo3B(int n){TIM3_CCR1 = SERVO_05MS + (n*(SERVO_1MS/900));}
void set_servo3C(int n){TIM4_CCR2 = SERVO_05MS + (n*(SERVO_1MS/900));}

void set_servo4A(int n){TIM3_CCR3 = SERVO_05MS + (n*(SERVO_1MS/900));}
void set_servo4B(int n){TIM3_CCR4 = SERVO_05MS + (n*(SERVO_1MS/900));}
void set_servo4C(int n){TIM1_CCR1 = SERVO_05MS + (n*(SERVO_1MS/900));}

void set_servo5A(int n){TIM1_CCR4 = SERVO_05MS + (n*(SERVO_1MS/900));}
void set_servo5B(int n){TIM1_CCR3 = SERVO_05MS + (n*(SERVO_1MS/900));}
void set_servo5C(int n){TIM1_CCR2 = SERVO_05MS + (n*(SERVO_1MS/900));}

void set_servo6A(int n){TIM8_CCR1 = SERVO_05MS + (n*(SERVO_1MS/900));}
void set_servo6B(int n){TIM8_CCR2 = SERVO_05MS + (n*(SERVO_1MS/900));}
void set_servo6C(int n){TIM8_CCR4 = SERVO_05MS + (n*(SERVO_1MS/900));}

/**
 * Position de base du robot version 3 pattes
 */
void stand(){

    set_servo1A(1000);
    set_servo1B(600);
    set_servo1C(200);

    set_servo3A(500);
    set_servo3B(600);
    set_servo3C(200);

    set_servo5A(100);
    set_servo5B(600);
    set_servo5C(200);
}

void init_servo(){

    printf("Init Servo...\n");

    // RCC init
    RCC_AHB1ENR |= RCC_GPIOAEN;
    RCC_AHB1ENR |= RCC_GPIOBEN;
    RCC_AHB1ENR |= RCC_GPIOCEN;
    RCC_AHB1ENR |= RCC_GPIOEEN;

    RCC_APB2ENR |= RCC_TIM1EN;
    RCC_APB2ENR |= RCC_TIM8EN;
    RCC_APB1ENR |= RCC_TIM2EN;
    RCC_APB1ENR |= RCC_TIM3EN;
    RCC_APB1ENR |= RCC_TIM4EN;

    printf("RCC init done\n");

    DISABLE_IRQS;

    // TIM1 init on GPIOE PE9, PE11, PE13, PE14
    GPIOE_MODER = REP_BITS(GPIOE_MODER, 9*2, 2, GPIO_MODER_ALT);
    GPIOE_MODER = REP_BITS(GPIOE_MODER, 11*2, 2, GPIO_MODER_ALT);
    GPIOE_MODER = REP_BITS(GPIOE_MODER, 13*2, 2, GPIO_MODER_ALT);
    GPIOE_MODER = REP_BITS(GPIOE_MODER, 14*2, 2, GPIO_MODER_ALT);
    GPIOE_AFRH = REP_BITS(GPIOE_AFRH, (9 - 8) * 4, 4, 1);
    GPIOE_AFRH = REP_BITS(GPIOE_AFRH, (11 - 8) * 4, 4, 1);
    GPIOE_AFRH = REP_BITS(GPIOE_AFRH, (13 - 8) * 4, 4, 1);
    GPIOE_AFRH = REP_BITS(GPIOE_AFRH, (14 - 8) * 4, 4, 1);

    //TIM1 init
    TIM1_CCMR1 |= TIM_OC1M_PWM1 | TIM_OC2M_PWM1;
    TIM1_CCMR2 |= TIM_OC3M_PWM1 | TIM_OC4M_PWM1;
    TIM1_CCER = TIM_CC1E | TIM_CC2E | TIM_CC3E | TIM_CC4E;
    TIM1_CCR1 = SERVO_1MS;
    TIM1_CCR2 = SERVO_1MS;
    TIM1_CCR3 = SERVO_1MS;
    TIM1_CCR4 = SERVO_1MS;
    TIM1_CR1 = 0;
    TIM1_PSC = SERVO_PSC - 1;
    TIM1_ARR = SERVO_PERIOD * 2;
    TIM1_EGR = TIM_UG;
    TIM1_SR = 0;
    TIM1_CR1 = TIM_CEN | TIM_ARPE;

    printf("TIM1 init done\n");
    
    
    // TIM8 init on GPIOC PC6, PC7, PC8, PC9
    GPIOC_MODER = REP_BITS(GPIOC_MODER, 6*2, 2, GPIO_MODER_ALT);
    GPIOC_MODER = REP_BITS(GPIOC_MODER, 7*2, 2, GPIO_MODER_ALT);
    GPIOC_MODER = REP_BITS(GPIOC_MODER, 8*2, 2, GPIO_MODER_ALT);
    GPIOC_MODER = REP_BITS(GPIOC_MODER, 9*2, 2, GPIO_MODER_ALT);
    GPIOC_AFRL = REP_BITS(GPIOC_AFRL, 6 * 4, 4, 3);
    GPIOC_AFRL = REP_BITS(GPIOC_AFRL, 7 * 4, 4, 3);
    GPIOC_AFRH = REP_BITS(GPIOC_AFRH, (8-8) * 4, 4, 3);
    GPIOC_AFRH = REP_BITS(GPIOC_AFRH, (9-8) * 4, 4, 3);

    //TIM8 init
    TIM8_CCMR1 = TIM_OC1M_PWM1 | TIM_OC2M_PWM1;
    TIM8_CCMR2 = TIM_OC3M_PWM1 | TIM_OC4M_PWM1;
    TIM8_CCER = TIM_CC1E | TIM_CC2E | TIM_CC3E | TIM_CC4E;
    TIM8_CCR1 = SERVO_1MS;
    TIM8_CCR2 = SERVO_1MS;
    TIM8_CCR3 = SERVO_1MS;
    TIM8_CCR4 = SERVO_1MS;
    TIM8_CR1 = 0;
    TIM8_PSC = SERVO_PSC - 1;
    TIM8_ARR = SERVO_PERIOD * 2;
    TIM8_EGR = TIM_UG;
    TIM8_SR = 0;
    TIM8_CR1 = TIM_CEN | TIM_ARPE;

    printf("TIM8 init done\n");

    // TIM2 init on GPIOA PA15, PA1, PA2, PA3
    GPIOA_MODER = REP_BITS(GPIOA_MODER, 15*2, 2, GPIO_MODER_ALT);
    GPIOA_MODER = REP_BITS(GPIOA_MODER, 1*2, 2, GPIO_MODER_ALT);
    GPIOA_MODER = REP_BITS(GPIOA_MODER, 2*2, 2, GPIO_MODER_ALT);
    GPIOA_MODER = REP_BITS(GPIOA_MODER, 3*2, 2, GPIO_MODER_ALT);
    GPIOA_AFRH = REP_BITS(GPIOA_AFRH, (15 - 8) * 4, 4, 1);
    GPIOA_AFRL = REP_BITS(GPIOA_AFRL, 1 * 4, 4, 1);
    GPIOA_AFRL = REP_BITS(GPIOA_AFRL, 2 * 4, 4, 1);
    GPIOA_AFRL = REP_BITS(GPIOA_AFRL, 3 * 4, 4, 1);

    //TIM2 init
    TIM2_CCMR1 = TIM_OC1M_PWM1 | TIM_OC2M_PWM1;
    TIM2_CCMR2 = TIM_OC3M_PWM1 | TIM_OC4M_PWM1;
    TIM2_CCER = TIM_CC1E | TIM_CC2E | TIM_CC3E | TIM_CC4E;
    TIM2_CCR1 = SERVO_1MS;
    TIM2_CCR2 = SERVO_1MS;
    TIM2_CCR3 = SERVO_1MS;
    TIM2_CCR4 = SERVO_1MS;
    TIM2_CR1 = 0;
    TIM2_PSC = SERVO_PSC - 1;
    TIM2_ARR = SERVO_PERIOD * 2;
    TIM2_EGR = TIM_UG;
    TIM2_SR = 0;
    TIM2_CR1 = TIM_CEN | TIM_ARPE;

    printf("TIM2 init done\n");

    // TIM3 init on GPIOB PB4, PB5, PB0, PB1
    GPIOB_MODER = REP_BITS(GPIOB_MODER, 4*2, 2, GPIO_MODER_ALT);
    GPIOB_MODER = REP_BITS(GPIOB_MODER, 5*2, 2, GPIO_MODER_ALT);
    GPIOB_MODER = REP_BITS(GPIOB_MODER, 0*2, 2, GPIO_MODER_ALT);
    GPIOB_MODER = REP_BITS(GPIOB_MODER, 1*2, 2, GPIO_MODER_ALT);
    GPIOB_AFRL = REP_BITS(GPIOB_AFRL, 4 * 4, 4, 2);
    GPIOB_AFRL = REP_BITS(GPIOB_AFRL, 5 * 4, 4, 2);
    GPIOB_AFRL = REP_BITS(GPIOB_AFRL, 0 * 4, 4, 2);
    GPIOB_AFRL = REP_BITS(GPIOB_AFRL, 1 * 4, 4, 2);

    //TIM3 init
    TIM3_CCMR1 = TIM_OC1M_PWM1 | TIM_OC2M_PWM1;
    TIM3_CCMR2 = TIM_OC3M_PWM1 | TIM_OC4M_PWM1;
    TIM3_CCER = TIM_CC1E | TIM_CC2E | TIM_CC3E | TIM_CC4E;
    TIM3_CCR1 = SERVO_1MS;
    TIM3_CCR2 = SERVO_1MS;
    TIM3_CCR3 = SERVO_1MS;
    TIM3_CCR4 = SERVO_1MS;
    TIM3_CR1 = 0;
    TIM3_PSC = SERVO_PSC - 1;
    TIM3_ARR = SERVO_PERIOD * 2;
    TIM3_EGR = TIM_UG;
    TIM3_SR = 0;
    TIM3_CR1 = TIM_CEN | TIM_ARPE;

    printf("TIM3 init done\n");

    // TIM4 init on GPIOB PB6, PB7, PB8, PB9
    GPIOB_MODER = REP_BITS(GPIOB_MODER, 6*2, 2, GPIO_MODER_ALT);
    GPIOB_MODER = REP_BITS(GPIOB_MODER, 7*2, 2, GPIO_MODER_ALT);
    GPIOB_MODER = REP_BITS(GPIOB_MODER, 8*2, 2, GPIO_MODER_ALT);
    GPIOB_MODER = REP_BITS(GPIOB_MODER, 9*2, 2, GPIO_MODER_ALT);
    GPIOB_AFRL = REP_BITS(GPIOB_AFRL, 6 * 4, 4, 2);
    GPIOB_AFRL = REP_BITS(GPIOB_AFRL, 7 * 4, 4, 2);
    GPIOB_AFRH = REP_BITS(GPIOB_AFRH, (8 - 8) * 4, 4, 2);
    GPIOB_AFRH = REP_BITS(GPIOB_AFRH, (9 - 8) * 4, 4, 2);

    //TIM4 init
    TIM4_CCMR1 = TIM_OC1M_PWM1 | TIM_OC2M_PWM1;
    TIM4_CCMR2 = TIM_OC3M_PWM1 | TIM_OC4M_PWM1;
    TIM4_CCER = TIM_CC1E | TIM_CC2E | TIM_CC3E | TIM_CC4E;
    TIM4_CCR1 = SERVO_1MS;
    TIM4_CCR2 = SERVO_1MS;
    TIM4_CCR3 = SERVO_1MS;
    TIM4_CCR4 = SERVO_1MS;
    TIM4_CR1 = 0;
    TIM4_PSC = SERVO_PSC - 1;
    TIM4_ARR = SERVO_PERIOD * 2;
    TIM4_EGR = TIM_UG;
    TIM4_SR = 0;
    TIM4_CR1 = TIM_CEN | TIM_ARPE;

    printf("TIM4 init done\n");


    /**
     * Rajouter un timer qui va générer une interruption toutes les n ms pour update les servomoteurs
     */
    //

    ENABLE_IRQS;

    printf("End Init Servo\n");

}
