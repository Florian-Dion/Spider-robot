#include <stm32f4/usart.h>
#include <stm32f4/src/init.c>
#include <stm32f4/nvic.h>
#include <stm32f4/tim.h>
#include <stm32f4/gpio.h>
#include <stm32f4/rcc.h>
#include <stm32f4/io.h>

volatile int motor1A = 900;
volatile int motor1B = 1800;
volatile int motor1C = 700;

volatile int motor2A = 0;
volatile int motor2B = 0;
volatile int motor2C = 0;

volatile int motor3A = 0;
volatile int motor3B = 0;
volatile int motor3C = 0;

volatile int motor4A = 0;
volatile int motor4B = 0;
volatile int motor4C = 0;

int motor1_done = 0;
int motor2_done = 0;
int motor3_done = 0;

/**
 * @brief Cette fonction est appelé chaque fois que le timer 13 génère une interruption SI SEULEMENT, le module HC-06 a envoyé le message correspondant
 */
void handler_lever_patte1(){
    TIM13_SR = 0;
    NVIC_ICPR(TIM13_IRQ >> 5) = 1 << (TIM13_IRQ & 0x1F);  // Effacer le flag d'interruption
    printf("PROCEDURE DE MOUVEMENT DE LA PATTE 1...\n");

    if (motor1A < 1400){
        motor1A = motor1A + 20;
        set_servo1A(motor1A);
    }
    else if (motor1A > 1460){
        motor1A = motor1A - 20;
        set_servo1A(motor1A);
    }
    else{ motor1_done = 1;}

    if (motor1B < 900){
        motor1B = motor1B + 20;
        set_servo1B(motor1B);
    }
    else if (motor1B > 960){
        motor1B = motor1B - 20;
        set_servo1B(motor1B);
    }
    else{ motor2_done = 1;}

    if (motor1C < 1200){
        motor1C = motor1C + 20;
        set_servo1C(motor1C);
    }
    else if (motor1C > 1260){
        motor1C = motor1C - 20;
        set_servo1C(motor1C);
    }
    else{ motor3_done = 1;}

    if (motor1_done && motor2_done && motor3_done){
        printf("FIN DE LA PROCEDURE DE MOUVEMENT DE LA PATTE 1\n");
        DISABLE_IRQS;
        motor1_done = 0;
        motor2_done = 0;
        motor3_done = 0;
        NVIC_ISER(TIM13_IRQ >> 5) = 0 << (TIM13_IRQ & 0x1F); // Desactiver l'interruption sur TIM13
        NVIC_ISER(USART1_IRQ >> 5) = 1 << (USART1_IRQ & 0x1F);  // Activer les IRQ sur l'USART1
        ENABLE_IRQS;
    }
}

/**
 * @brief Cette fonction est appelé chaque fois que le timer 13 génère une interruption SI SEULEMENT, le module HC-06 a envoyé le message correspondant
 */
void handle_set_idle(){
    TIM13_SR = 0;
    NVIC_ICPR(TIM13_IRQ >> 5) = 1 << (TIM13_IRQ & 0x1F);  // Effacer le flag d'interruption
    printf("PROCEDURE DE MISE AU REPOS DU ROBOT...\n");

    if (motor1A < 900){
        motor1A = motor1A + 20;
        set_servo1A(motor1A);
    }
    else if (motor1A > 960){
        motor1A = motor1A - 20;
        set_servo1A(motor1A);
    }
    else{ motor1_done = 1;}

    if (motor1B < 1800){
        motor1B = motor1B + 20;
        set_servo1B(motor1B);
    }
    else if (motor1B > 1860){
        motor1B = motor1B - 20;
        set_servo1B(motor1B);
    }
    else{ motor2_done = 1;}

    if (motor1C < 700){
        motor1C = motor1C + 20;
        set_servo1C(motor1C);
    }
    else if (motor1C > 760){
        motor1C = motor1C - 20;
        set_servo1C(motor1C);
    }
    else{ motor3_done = 1;}

    if (motor1_done && motor2_done && motor3_done){
        printf("FIN DE LA PROCEDURE DE MISE AU REPOS DU ROBOT\n");
        DISABLE_IRQS;
        motor1_done = 0;
        motor2_done = 0;
        motor3_done = 0;
        NVIC_ISER(TIM13_IRQ >> 5) = 0 << (TIM13_IRQ & 0x1F); // Desactiver l'interruption sur TIM13
        NVIC_ISER(USART1_IRQ >> 5) = 1 << (USART1_IRQ & 0x1F);  // Activer les IRQ sur l'USART1
        ENABLE_IRQS;
    }
}