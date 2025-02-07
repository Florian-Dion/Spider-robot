#include <stm32f4/io.h>
#include <stm32f4/nvic.h>
#include <stm32f4/rcc.h>
#include <stm32f4/gpio.h>
#include <stm32f4/usart.h>
#include <stm32f4/tim.h>

volatile int motor2A = 0;
volatile int motor2B = 0;
volatile int motor2C = 0;

volatile int motor4A = 900;
volatile int motor4B = 1100;
volatile int motor4C = 0;

volatile int motor6A = 0;
volatile int motor6B = 0;
volatile int motor6C = 0;

int actionDone = 0;

void handler_avancer(){
    TIM13_SR = 0;
    NVIC_ICPR(TIM13_IRQ >> 5) = 1 << (TIM13_IRQ & 0x1F);  // Effacer le flag d'interruption
    /**
     * Implenter le code pour avancer
     */
    /*
    if (motor4B < 1400){
        set_servo4B(motor4B);
        motor4B = motor4B + 20;
    }
    etc ...
    quand on a fini de bouger :
    actionDone = 1;
    */
   if (actionDone){
        DISABLE_IRQS;
        actionDone = 0;
        NVIC_ISER(TIM13_IRQ >> 5) = 0 << (TIM13_IRQ & 0x1F); // Desactiver l'interruption sur TIM13
        NVIC_ISER(USART1_IRQ >> 5) = 1 << (USART1_IRQ & 0x1F); // Activer l'interruption sur USART1
        ENABLE_IRQS;
   }
}

void handler_reculer(){
    TIM13_SR = 0;
    NVIC_ICPR(TIM13_IRQ >> 5) = 1 << (TIM13_IRQ & 0x1F);  // Effacer le flag d'interruption
    /**
     * Implenter le code pour reculer
     */
    /*
    if (motor4B < 1400){
        set_servo4B(motor4B);
        motor4B = motor4B + 20;
    }
    etc ...
    quand on a fini de bouger :
    actionDone = 1;
    */
   if (actionDone){
        DISABLE_IRQS;
        actionDone = 0;
        NVIC_ISER(TIM13_IRQ >> 5) = 0 << (TIM13_IRQ & 0x1F); // Desactiver l'interruption sur TIM13
        NVIC_ISER(USART1_IRQ >> 5) = 1 << (USART1_IRQ & 0x1F); // Activer l'interruption sur USART1
        ENABLE_IRQS;
   }
}

void handler_tourner_gauche(){
    TIM13_SR = 0;
    NVIC_ICPR(TIM13_IRQ >> 5) = 1 << (TIM13_IRQ & 0x1F);  // Effacer le flag d'interruption
    /**
     * Implenter le code pour tourner à gauche
     */
    /*
    if (motor4B < 1400){
        set_servo4B(motor4B);
        motor4B = motor4B + 20;
    }
    etc ...
    quand on a fini de bouger :
    actionDone = 1;
    */
   if (actionDone){
        DISABLE_IRQS;
        actionDone = 0;
        NVIC_ISER(TIM13_IRQ >> 5) = 0 << (TIM13_IRQ & 0x1F); // Desactiver l'interruption sur TIM13
        NVIC_ISER(USART1_IRQ >> 5) = 1 << (USART1_IRQ & 0x1F); // Activer l'interruption sur USART1
        ENABLE_IRQS;
   }
}

void handler_tourner_droite(){
    TIM13_SR = 0;
    NVIC_ICPR(TIM13_IRQ >> 5) = 1 << (TIM13_IRQ & 0x1F);  // Effacer le flag d'interruption
    /**
     * Implenter le code pour tourner à droite
     */
    /*
    if (motor4B < 1400){
        set_servo4B(motor4B);
        motor4B = motor4B + 20;
    }
    etc ...
    quand on a fini de bouger :
    actionDone = 1;
    */
   if (actionDone){
        DISABLE_IRQS;
        actionDone = 0;
        NVIC_ISER(TIM13_IRQ >> 5) = 0 << (TIM13_IRQ & 0x1F); // Desactiver l'interruption sur TIM13
        NVIC_ISER(USART1_IRQ >> 5) = 1 << (USART1_IRQ & 0x1F); // Activer l'interruption sur USART1
        ENABLE_IRQS;
   }
}

void handler_repos(){
    TIM13_SR = 0;
    NVIC_ICPR(TIM13_IRQ >> 5) = 1 << (TIM13_IRQ & 0x1F);  // Effacer le flag d'interruption
    /**
     * Implenter le code pour adopter la position de repos
     */
    /*
    if (motor4B < 1400){
        set_servo4B(motor4B);
        motor4B = motor4B + 20;
    }
    etc ...
    quand on a fini de bouger :
    actionDone = 1;
    */
   if (actionDone){
        DISABLE_IRQS;
        actionDone = 0;
        NVIC_ISER(TIM13_IRQ >> 5) = 0 << (TIM13_IRQ & 0x1F); // Desactiver l'interruption sur TIM13
        NVIC_ISER(USART1_IRQ >> 5) = 1 << (USART1_IRQ & 0x1F); // Activer l'interruption sur USART1
        ENABLE_IRQS;
   }
}


void handle_TIM13(){
    TIM13_SR = 0;
    NVIC_ICPR(TIM13_IRQ >> 5) = 1 << (TIM13_IRQ & 0x1F);  // Effacer le flag d'interruption
    printf("handle tim13\n");
    if (motor4B > 900){
        set_servo4B(motor4B);
        motor4B = motor4B - 20;
    }
}