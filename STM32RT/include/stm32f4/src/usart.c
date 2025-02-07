#include <stm32f4/usart.h>
#include <stm32f4/src/init.c>
#include <stm32f4/src/handler_irq.c>

// Buffer pour stocker les données reçues
#define RX_BUFFER_SIZE 128
char rx_buffer[RX_BUFFER_SIZE];
uint16_t rx_index = 0;
uint8_t rx_complete = 0;


/**
 * @brief Cette fonction est appelé chaque fois qu'un message est reçu sur le RX de l'USART1
 * Donc chaque fois que le module HC-06 communiquera avec la carte
 * On suppose que l'utilisateur est bienveillant et qu'il envoie uniquement des messages connus
 */
void handle_USART1()
{
    printf("handle_USART1\n");
    if (USART_SR & USART_SR_RXNE) // Si des données sont disponibles
    {
        uint32_t received_data = USART_DR;
        USART_SR = REP_BITS(USART_SR, 3, 3, 0); // Effacer le flag RXNE

        if (GET_BITS(received_data, 0, 4) == 0b0011){ // AVANCER
            DISABLE_IRQS;
            NVIC_ICER(TIM13_IRQ >> 5) = 1 << (TIM13_IRQ & 0x1F);
            NVIC_IRQ(TIM13_IRQ) = (uint32_t)handler_avancer;
            NVIC_IPR(TIM13_IRQ) = 0;
            NVIC_ISER(TIM13_IRQ >> 5) = 1 << (TIM13_IRQ & 0x1F);    // Activer les IRQ
        }
        else if (GET_BITS(received_data, 0, 4) == 0b1000){ // RECULER
            DISABLE_IRQS;
            NVIC_ICER(TIM13_IRQ >> 5) = 1 << (TIM13_IRQ & 0x1F);
            NVIC_IRQ(TIM13_IRQ) = (uint32_t)handler_reculer;
            NVIC_IPR(TIM13_IRQ) = 0;
            NVIC_ISER(TIM13_IRQ >> 5) = 1 << (TIM13_IRQ & 0x1F);    // Activer les IRQ
        }
        else if (GET_BITS(received_data, 0, 4) == 0b0100){ // TOURNER GAUCHE
            DISABLE_IRQS;
            NVIC_ICER(TIM13_IRQ >> 5) = 1 << (TIM13_IRQ & 0x1F);
            NVIC_IRQ(TIM13_IRQ) = (uint32_t)handler_tourner_gauche;
            NVIC_IPR(TIM13_IRQ) = 0;
            NVIC_ISER(TIM13_IRQ >> 5) = 1 << (TIM13_IRQ & 0x1F);    // Activer les IRQ
        }
        else if (GET_BITS(received_data, 0, 4) == 0b1100){ // TOURNER DROITE
            DISABLE_IRQS;
            NVIC_ICER(TIM13_IRQ >> 5) = 1 << (TIM13_IRQ & 0x1F);
            NVIC_IRQ(TIM13_IRQ) = (uint32_t)handler_tourner_droite;
            NVIC_IPR(TIM13_IRQ) = 0;
            NVIC_ISER(TIM13_IRQ >> 5) = 1 << (TIM13_IRQ & 0x1F);    // Activer les IRQ
        }
        else if (GET_BITS(received_data, 0, 4) == 0b0000){ // REPOS
            DISABLE_IRQS;
            NVIC_ICER(TIM13_IRQ >> 5) = 1 << (TIM13_IRQ & 0x1F);
            NVIC_IRQ(TIM13_IRQ) = (uint32_t)handler_repos;
            NVIC_IPR(TIM13_IRQ) = 0;
            NVIC_ISER(TIM13_IRQ >> 5) = 1 << (TIM13_IRQ & 0x1F);    // Activer les IRQ
        }

        NVIC_ISER(USART1_IRQ >> 5) = 0 << (USART1_IRQ & 0x1F);  // Desactiver l'interruption sur l'usart1
    }
    NVIC_ICPR(USART1_IRQ >> 5) = 1 << (USART1_IRQ & 0x1F);  // Effacer le flag d'interruption
    ENABLE_IRQS;
}


// void usart_send_string(const char* str)
// {
//     while (*str)
//     {
//         // Attendre que le registre d'émission soit vide
//         while (!(USART_SR & USART_SR_TXE));
//        // Envoyer un caractère
//        USART_DR = REP_BITS(USART_DR, 0, 9, *str);
//         str++;
//     }
// }

// // Fonction pour envoyer une commande AT
// void send_at_command(const char *cmd) {
//     usart_send_string(cmd);
//     usart_send_string("\r\n");  // Les commandes AT terminent par CRLF
// }

// // Fonction pour configurer le HC-06
// void configure_hc06(void) {
//     // 1. Attente que le module soit prêt
//     send_at_command("AT");  // Vérifie si le HC-06 est en mode commande
//     while (!rx_complete);   // Attente de la réponse
//     rx_complete = 0;
//     if (strcmp(rx_buffer, "OK") != 0) {
//         // Si "OK" n'est pas reçu, le HC-06 n'est pas en mode commande
//         return;
//     }

//     // 2. Changer le nom
//     send_at_command("AT+NAMEHC06_BT");
//     while (!rx_complete);
//     rx_complete = 0;

//     // 3. Changer le baudrate
//     send_at_command("AT+BAUD4");  // 38400 bps
//     while (!rx_complete);
//     rx_complete = 0;

//     // 4. (Facultatif) Changer le PIN
//     send_at_command("AT+PIN1234");
//     while (!rx_complete);
//     rx_complete = 0;
// }

void stm32f4_usart1_init(void){

    //USART1->CR1->UE = 0;                // Disable the USART
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

/***************************************A CHANGER POUR UNE CLK A 84 MHZ*************************************** */
/***************************************SOIT 546.875********************************************************** */

    USART_BRR = REP_BITS(USART_BRR, 0, 4, 0b001010); // 9600 bps
    USART_BRR = REP_BITS(USART_BRR, 4, 12, 0b11010011010); // 9600 bps

    /**
     * Activer l'émetteur
     * Activer le récepteur
     * Activer l'interruption RXNE
     * Activer l'USART
     */
    USART_CR1 |= USART_CR1_TE | USART_CR1_RE;
    USART_CR1 &= ~USART_CR1_M; // 8 bits de données
    USART_CR1 &= ~USART_CR1_PCE; // Pas de parité
    USART_CR1 &= ~USART_CR1_OVER8; // Oversampling par 16

    //Configuration du registre CR2
    USART_CR2 = REP_BITS(USART_CR2, 12, 2, 0);


    // Configuration de l'interruption

    NVIC_ICER(USART1_IRQ >> 5) = 1 << (USART1_IRQ & 0x1F);
    NVIC_IRQ(USART1_IRQ) = (uint32_t)handle_USART1;
    NVIC_IPR(USART1_IRQ) = 0;

    NVIC_ICPR(USART1_IRQ >> 5) = 1 << (USART1_IRQ & 0x1F);

    USART_CR1 |= USART_CR1_RXNEIE; // Activer l'interruption RXNE
    USART_CR1 |= USART_CR1_UE; // Activer l'USART

    NVIC_ISER(USART1_IRQ >> 5) = 1 << (USART1_IRQ & 0x1F);  // Activer les IRQ

    ENABLE_IRQS;
}