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

volatile int motor2A = 1200;
volatile int motor2B = 1600;
volatile int motor2C = 400;

volatile int motor3A = 1800;
volatile int motor3B = 900;
volatile int motor3C = 900;

volatile int motor4A = 200;
volatile int motor4B = 1100;
volatile int motor4C = 1200;

int motor1_done = 0;
int motor2_done = 0;
int motor3_done = 0;

int motor4_done = 0;
int motor5_done = 0;
int motor6_done = 0;

int motor7_done = 0;
int motor8_done = 0;
int motor9_done = 0;

int motor10_done = 0;
int motor11_done = 0;
int motor12_done = 0;

/**
 * @brief Cette fonction est appelé chaque fois que le timer 13 génère une interruption SI SEULEMENT, le module HC-06 a envoyé le message correspondant
 */
void handler_lever_patte1(){
    TIM13_SR = 0;
    NVIC_ICPR(TIM13_IRQ >> 5) = 1 << (TIM13_IRQ & 0x1F);  // Effacer le flag d'interruption
    printf("PROCEDURE DE MOUVEMENT DE LA PATTE 1...\n");

    if (motor1A < 200){
        motor1A = motor1A + 50;
        set_servo1A(motor1A);
    }
    else if (motor1A > 290){
        motor1A = motor1A - 50;
        set_servo1A(motor1A);
    }
    else{ motor1_done = 1;}

    if (motor1B < 1800){
        motor1B = motor1B + 500;
        set_servo1B(motor1B);
    }
    else if (motor1B > 1890){
        motor1B = motor1B - 50;
        set_servo1B(motor1B);
    }
    else{ motor2_done = 1;}

    if (motor1C < 100){
        motor1C = motor1C + 50;
        set_servo1C(motor1C);
    }
    else if (motor1C > 190){
        motor1C = motor1C - 50;
        set_servo1C(motor1C);
    }
    else{ motor3_done = 1;}

    ////////////////////////////// PATTE 2 //////////////////////////////////////////////////

    if (motor2A < 1800){
        motor2A = motor2A + 50;
        set_servo2A(motor2A);
    }
    else if (motor2A > 1890){
        motor2A = motor2A - 50;
        set_servo2A(motor2A);
    }
    else{ motor4_done = 1;}

    if (motor2B < 1600){
        motor2B = motor2B + 50;
        set_servo2B(motor2B);
    }
    else if (motor2B > 1690){
        motor2B = motor2B - 50;
        set_servo2B(motor2B);
    }
    else{ motor5_done = 1;}

    if (motor2C < 1100){
        motor2C = motor2C + 50;
        set_servo2C(motor2C);
    }
    else if (motor2C > 1190){
        motor2C = motor2C - 50;
        set_servo2C(motor2C);
    }
    else{ motor6_done = 1;}


    if (motor1_done && motor2_done && motor3_done && motor4_done && motor5_done && motor6_done){
        printf("FIN DE LA PROCEDURE DE MOUVEMENT DE LA PATTE 1\n");
        DISABLE_IRQS;
        motor1_done = 0;
        motor2_done = 0;
        motor3_done = 0;
        motor4_done = 0;
        motor5_done = 0;
        motor6_done = 0;
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
        motor1A = motor1A + 50;
        set_servo1A(motor1A);
    }
    else if (motor1A > 990){
        motor1A = motor1A - 50;
        set_servo1A(motor1A);
    }
    else{ motor1_done = 1;}

    if (motor1B < 1800){
        motor1B = motor1B + 50;
        set_servo1B(motor1B);
    }
    else if (motor1B > 1890){
        motor1B = motor1B - 50;
        set_servo1B(motor1B);
    }
    else{ motor2_done = 1;}

    if (motor1C < 700){
        motor1C = motor1C + 50;
        set_servo1C(motor1C);
    }
    else if (motor1C > 790){
        motor1C = motor1C - 50;
        set_servo1C(motor1C);
    }
    else{ motor3_done = 1;}

    /////////////////////////////////PATTE 2//////////////////////////////////////////
    if (motor2A < 1200){
        motor2A = motor2A + 50;
        set_servo2A(motor2A);
    }
    else if (motor2A > 1290){
        motor2A = motor2A - 50;
        set_servo2A(motor2A);
    }
    else{ motor4_done = 1;}

    if (motor2B < 1600){
        motor2B = motor2B + 50;
        set_servo2B(motor2B);
    }
    else if (motor2B > 1690){
        motor2B = motor2B - 50;
        set_servo2B(motor2B);
    }
    else{ motor5_done = 1;}

    if (motor2C < 400){
        motor2C = motor2C + 50;
        set_servo2C(motor2C);
    }
    else if (motor2C > 490){
        motor2C = motor2C - 50;
        set_servo2C(motor2C);
    }
    else{ motor6_done = 1;}

    //////////////////////////////PATTE 3//////////////////////////////////////////////

    if (motor3A < 1800){
        motor3A = motor3A + 50;
        set_servo3A(motor3A);
    }
    else if (motor3A > 1890){
        motor3A = motor3A - 50;
        set_servo3A(motor3A);
    }
    else{ motor1_done = 1;}

    if (motor3B < 900){
        motor3B = motor3B + 50;
        set_servo3B(motor3B);
    }
    else if (motor3B > 990){
        motor3B = motor3B - 50;
        set_servo3B(motor3B);
    }
    else{ motor2_done = 1;}

    if (motor3C < 900){
        motor3C = motor3C + 50;
        set_servo3C(motor3C);
    }
    else if (motor3C > 990){
        motor3C = motor3C - 50;
        set_servo3C(motor3C);
    }
    else{ motor3_done = 1;}

    //////////////////////////////PATTE 4//////////////////////////////////////////////

    if (motor4A < 200){
        motor4A = motor4A + 50;
        set_servo4A(motor4A);
    }
    else if (motor4A > 290){
        motor4A = motor4A - 50;
        set_servo4A(motor4A);
    }
    else{ motor4_done = 1;}

    if (motor4B < 1100){
        motor4B = motor4B + 50;
        set_servo4B(motor4B);
    }
    else if (motor4B > 1190){
        motor4B = motor4B - 50;
        set_servo4B(motor4B);
    }
    else{ motor5_done = 1;}

    if (motor4C < 1200){
        motor4C = motor4C + 50;
        set_servo4C(motor4C);
    }
    else if (motor4C > 1290){
        motor4C = motor4C - 50;
        set_servo4C(motor4C);
    }
    else{ motor6_done = 1;}

    if (motor1_done && motor2_done && motor3_done && motor4_done && motor5_done && motor6_done && motor7_done && motor8_done && motor9_done && motor10_done && motor11_done && motor12_done){
        printf("FIN DE LA PROCEDURE DE MISE AU REPOS DU ROBOT\n");
        DISABLE_IRQS;
        motor1_done = 0;
        motor2_done = 0;
        motor3_done = 0;
        motor4_done = 0;
        motor5_done = 0;
        motor6_done = 0;
        motor7_done = 0;
        motor8_done = 0;
        motor9_done = 0;
        motor10_done = 0;
        motor11_done = 0;
        motor12_done = 0;
        NVIC_ISER(TIM13_IRQ >> 5) = 0 << (TIM13_IRQ & 0x1F); // Desactiver l'interruption sur TIM13
        NVIC_ISER(USART1_IRQ >> 5) = 1 << (USART1_IRQ & 0x1F);  // Activer les IRQ sur l'USART1
        ENABLE_IRQS;
    }
}