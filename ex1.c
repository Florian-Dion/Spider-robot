#include <tinyprintf.h>
#include <stm32f4/src/usart.c>

int main(void) {
    printf("Initialisation...\n");
    stm32f4_usart1_init();  // Initialiser l'USART
    printf("USART1 initialise!\n");
    configure_hc06();       // Configurer le HC-06
    printf("HC-06 configuré!\n");

    while (1) {
        if (rx_complete) {  // Une ligne complète a été reçue
            printf("Received: %s\n", rx_buffer);  // Afficher les données reçues
            rx_complete = 0;
        }
    }
}
