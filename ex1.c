#include <tinyprintf.h>
#include <stm32f4/src/usart.c>

int main(void) {
    printf("Initialisation...\n");
    init_servo();           // Initialiser les servo
    stm32f4_usart1_init();  // Initialiser l'USART
    printf("USART1 initialise!\n");
    
    while (1) {
    }
}
