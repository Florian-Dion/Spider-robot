#include "usart.h"

/**
 * @brief Cette fonction est appelé chaque fois qu'un message est reçu sur le RX de l'USART1
 * Donc chaque fois que le module HC-06 communiquera avec la carte
 */
void handle_USART1()
{

}

void stm32f4_usart1_init(void){

    USART1->CR1->UE = 0;                // Disable the USART
    DISABLE_IRQS;                       // Disable IRQ

    // Activer l'horloge GPIO et USART
    RCC_AHB1ENR |= RCC_GPIOAEN;         // Activer GPIOA pour USART1 (PA9: TX, PA10: RX)
    RCC_APB2ENR |= RCC_USART1EN;        // Activer l'horloge pour l'USART1 (APB2)

    GPIOA_MODER = REP_BITS(GPIOA_MODER, 9 * 2, 2, GPIO_MODER_ALT);
    GPIOA_MODER = REP_BITS(GPIOA_MODER, 10 * 2, 2, GPIO_MODER_ALT);

    // Configurer PA9 (USART1_TX) en AF7 (USART1)
    GPIOA_AFRH = REP_BITS(GPIOA_AFRH, (9 - 8) * 4, 4, 0b0111);

    // Configurer PA10 (USART1_RX) en AF7 (USART1)
    GPIOA_AFRH = REP_BITS(GPIOA_AFRH, (10 - 8) * 4, 4, 0b0111);

    NVIC_ICER(USART1_IRQ >> 5) = 1 << (USART1_IRQ & 0x1F);
    NVIC_IRQ(USART1_IRQ) = (uint32_t)handle_USART1;
    NVIC_IPR(USART1_IRQ) = 0;

    NVIC_ICPR(USART1_IRQ >> 5) = 1 << (USART1_IRQ & 0x1F);


    uint32_t pclk2 = 16000000;          // HSI par défaut
    uint32_t apb2_prescaler = ((RCC_CFGGR_PPRE2_SET(RCC_CFGR, RCC_PPRE_DIV2)) == RCC_PPRE_DIV2) ? 2 : 1;
    pclk2 /= apb2_prescaler;

    uint32_t baudrate = 38400;
    uint32_t usartdiv = (pclk2 + (baudrate / 2)) / baudrate;  // Arrondi
    USART1->BRR->DIV_Mantissa = usartdiv >> 4;
    USART1->BRR->DIV_Fraction = usartdiv & 0xF;


    // Configuration du registre CR1
    USART1->CR1->M = 0;                 // Word length: 8 bits
    USART1->CR1->PCE = 0;               // Pas de contrôle de parité
    USART1->CR1->TE = 1;                // Activer l'émetteur
    USART1->CR1->RE = 1;                // Activer le récepteur
    USART1->CR1->OVER8 = 0;             // Oversampling par 16
  
    // Configuration du registre CR2
    USART1->CR2->STOP = 0x00000000U;    // 1 bit d'arrêt
    
    // Configfuration du registre CR3
    USART1->CR3->CTSE = 0;              // Désactiver le contrôle matériel CTS
    USART1->CR3->RTSE = 0;              // Désactiver le contrôle matériel RTS
    USART1->CR3->ONEBIT = 0;            // Méthode d'échantillonnage par 3 bits (par défaut)

    // Activer l'USART
    USART1->CR1->UE = 1;

    NVIC_ISER(USART1_IRQ >> 5) = 1 << (USART1_IRQ & 0x1F);  // Activer les IRQ

    USART1->CR1->RXNEIE = 1;            // Activer l'interruption RXNE

    ENABLE_IRQS;
}

char uart_receive_byte(void)
{
    while (USART1->SR->RXNE == 0);  // Attendre que des données soient reçues
    return (char)(USART1->DR->DR);  // Lire les données
}