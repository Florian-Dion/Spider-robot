#include <stm32f4/usart.h>
#include <stm32f4/src/handler_irq.c>

/**
 * @brief Cette fonction est appelé chaque fois qu'un message est reçu sur le RX de l'USART2
 * Donc chaque fois que le module HC-06 communiquera avec la carte
 */
void handle_USART1()
{
    printf("handle_USART1\n");
    if (USART1_SR & USART_SR_RXNE)                                                      // Si des données sont disponibles
    {
        uint32_t received_data = USART1_DR;
        USART1_SR = REP_BITS(USART1_SR, 3, 3, 0);                                       // Effacer le flag RXNE

        if (GET_BITS(received_data, 0, 4) == 0b0011){                                   // MOUVEMENT PATTE 1
            printf("INITIALISATION DU MOUVEMENT\n");

            DISABLE_IRQS;
            NVIC_ICER(TIM13_IRQ >> 5) = 1 << (TIM13_IRQ & 0x1F);
            NVIC_IRQ(TIM13_IRQ) = (uint32_t)handler_lever_patte1;
            NVIC_IPR(TIM13_IRQ) = 0;
            NVIC_ISER(TIM13_IRQ >> 5) = 1 << (TIM13_IRQ & 0x1F);                        // Activer les IRQ
        }
        else if (GET_BITS(received_data, 0, 4) == 0b1000){}

        NVIC_ISER(USART1_IRQ >> 5) = 0 << (USART1_IRQ & 0x1F);                          // Desactiver l'USART1
    }
    NVIC_ICPR(USART1_IRQ >> 5) = 1 << (USART1_IRQ & 0x1F);                              // Effacer le flag d'interruption
    ENABLE_IRQS;
}


/**
 * @brief Initialiser l'USART1
 */
void stm32f4_usart1_init(void){

    DISABLE_IRQS;                                                                       // Disable IRQ

    RCC_APB2ENR |= RCC_USART1EN;                                                        // Activer l'horloge pour l'USART1 (APB2)

    GPIOB_MODER = REP_BITS(GPIOB_MODER, 6 * 2, 2, GPIO_MODER_ALT);
    GPIOB_MODER = REP_BITS(GPIOB_MODER, 7 * 2, 2, GPIO_MODER_ALT);

    
    GPIOB_AFRL = REP_BITS(GPIOB_AFRL, 6 * 4, 4, 0b0111);                                // Configurer PB6 (USART1_TX) en AF7 (USART1)
    GPIOB_AFRL = REP_BITS(GPIOB_AFRL, 7 * 4, 4, 0b0111);                                // Configurer PB7 (USART1_RX) en AF7 (USART1)

    USART1_BRR = REP_BITS(USART1_BRR, 0, 4, 0b1010);                                    // 9600 bps
    USART1_BRR = REP_BITS(USART1_BRR, 4, 12, 0b11010011010);                            // 9600 bps


    USART1_CR1 |= USART_CR1_TE | USART_CR1_RE;                                          // Activer l'émetteur et le récepteur
    USART1_CR1 &= ~USART_CR1_M;                                                         // 8 bits de données
    USART1_CR1 &= ~USART_CR1_PCE;                                                       // Pas de parité
    USART1_CR1 &= ~USART_CR1_OVER8;                                                     // Oversampling par 16

    
    USART1_CR2 = REP_BITS(USART1_CR2, 12, 2, 0);                                        //Configuration du registre CR2

    NVIC_ICER(USART1_IRQ >> 5) = 1 << (USART1_IRQ & 0x1F);                              // Desactiver les IRQ
    NVIC_IRQ(USART1_IRQ) = (uint32_t)handle_USART1;
    NVIC_IPR(USART1_IRQ) = 0;

    NVIC_ICPR(USART1_IRQ >> 5) = 1 << (USART1_IRQ & 0x1F);

    USART1_CR1 |= USART_CR1_RXNEIE;                                                     // Activer l'interruption RXNE
    USART1_CR1 |= USART_CR1_UE;                                                         // Activer l'USART

    NVIC_ISER(USART1_IRQ >> 5) = 1 << (USART1_IRQ & 0x1F);                              // Activer les IRQ

    ENABLE_IRQS;
}