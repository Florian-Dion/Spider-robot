/**
 * Torpy - grid-follower wheeling and box delivering bot.
 *	Copyright (C) 2021  Université de Toulouse <floriandion8@gmail.com>
 *
 *	This program is free software: you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License as published by
 *	the Free Software Foundation, either version 3 of the License, or
 *	(at your option) any later version.
 *
 *	This program is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU General Public License for more details.
 */

/**
 * @file usart.h
 * @brief Universal synchronous asynchronous receiver transmitter (USART) HW driver header file.
 */

#ifndef STM32F4_USART_H
#define STM32F4_USART_H

#include "io.h"
#include <stdint.h>
#include <stdlib.h>
#include <stm32f4/nvic.h>
#include <stm32f4/rcc.h>
#include <stm32f4/gpio.h>


// Définitions pour le périphérique et les registres
#define USART1_BASE 0x40011000U // Base address de USART1

// Constantes système
#define HSI_VALUE 16000000U // Fréquence de HSI à 16 MHz

// Interrupts
#define USART1_IRQ  37



/**********************************************************************//**
 * @name IO Device: Universal synchronous asynchronous receiver transmitter (USART)
 **************************************************************************/
/**@{*/
/** USART SR Register prototype */
typedef volatile struct {
    uint32_t PE       : 1;  // Bit 0: Parity error
    uint32_t FE       : 1;  // Bit 1: Framing error
    uint32_t NF       : 1;  // Bit 2: Noise flag
    uint32_t ORE      : 1;  // Bit 3: Overrun error
    uint32_t IDLE     : 1;  // Bit 4: Idle line detected
    uint32_t RXNE     : 1;  // Bit 5: Read data register not empty
    uint32_t TC       : 1;  // Bit 6: Transmission complete
    uint32_t TXE      : 1;  // Bit 7: Transmit data register empty
    uint32_t LBD      : 1;  // Bit 8: LIN break detection flag
    uint32_t CTS      : 1;  // Bit 9: CTS flag
    uint32_t Reserved : 22; // Bits 10–31: Reserved
} USART_SR_t;


/** USART DR Register prototype */
typedef volatile struct {
    uint32_t DR       : 9;  // Bits 0–8: Data Register
    uint32_t Reserved : 23; // Bits 9–31: Reserved
} USART_DR_t;

/** USART BRR Register prototype */
typedef volatile struct {
    uint32_t DIV_Fraction : 4;  // Bits 0–3: Fraction of USART Divider
    uint32_t DIV_Mantissa : 12; // Bits 4–15: Mantissa of USART Divider
    uint32_t Reserved     : 16; // Bits 16–31: Reserved
} USART_BRR_t;

/** USART CR1 Register prototype */
typedef volatile struct {
    uint32_t SBK      : 1;  // Bit 0: Send Break
    uint32_t RWU      : 1;  // Bit 1: Receiver Wakeup
    uint32_t RE       : 1;  // Bit 2: Receiver Enable
    uint32_t TE       : 1;  // Bit 3: Transmitter Enable
    uint32_t IDLEIE   : 1;  // Bit 4: IDLE Interrupt Enable
    uint32_t RXNEIE   : 1;  // Bit 5: RXNE Interrupt Enable
    uint32_t TCIE     : 1;  // Bit 6: Transmission Complete Interrupt Enable
    uint32_t TXEIE    : 1;  // Bit 7: TXE Interrupt Enable
    uint32_t PEIE     : 1;  // Bit 8: PE Interrupt Enable
    uint32_t PS       : 1;  // Bit 9: Parity Selection
    uint32_t PCE      : 1;  // Bit 10: Parity Control Enable
    uint32_t WAKE     : 1;  // Bit 11: Wakeup method
    uint32_t M        : 1;  // Bit 12: Word length
    uint32_t UE       : 1;  // Bit 13: USART Enable
    uint32_t Reserved : 1; // Bits 16–31: Reserved
    uint32_t OVER8    : 1;  // Bit 15: Oversampling mode
    uint32_t Reserved2 : 16; // Bits 16–31: Reserved
} USART_CR1_t;


/** USART CR2 Register prototype */
typedef volatile struct {
    uint32_t ADD      : 4;  // Bits 0–3: Address of the USART node
    uint32_t Reserved : 1;  // Bit 4: Reserved
    uint32_t LBDL     : 1;  // Bit 5: LIN Break Detection Length
    uint32_t LBDIE    : 1;  // Bit 6: LIN Break Detection Interrupt Enable
    uint32_t Reserved2: 1;  // Bit 7: Reserved
    uint32_t LBCL     : 1;  // Bit 8: Last Bit Clock pulse
    uint32_t CPHA     : 1;  // Bit 9: Clock Phase
    uint32_t CPOL     : 1;  // Bit 10: Clock Polarity
    uint32_t CLKEN    : 1;  // Bit 11: Clock Enable
    uint32_t STOP     : 2;  // Bits 12–13: STOP bits
    uint32_t LINEN    : 1;  // Bit 14: LIN Mode Enable
    uint32_t Reserved3: 17; // Bits 15–31: Reserved
} USART_CR2_t;


/** USART CR3 Register prototype */
typedef volatile struct {
    uint32_t EIE      : 1;  // Bit 0: Error Interrupt Enable
    uint32_t IREN     : 1;  // Bit 1: IrDA mode Enable
    uint32_t IRLP     : 1;  // Bit 2: IrDA Low-Power
    uint32_t HDSEL    : 1;  // Bit 3: Half-Duplex Selection
    uint32_t NACK     : 1;  // Bit 4: Smartcard NACK Enable
    uint32_t SCEN     : 1;  // Bit 5: Smartcard mode Enable
    uint32_t DMAR     : 1;  // Bit 6: DMA Enable Receiver
    uint32_t DMAT     : 1;  // Bit 7: DMA Enable Transmitter
    uint32_t RTSE     : 1;  // Bit 8: RTS Enable
    uint32_t CTSE     : 1;  // Bit 9: CTS Enable
    uint32_t CTSIE    : 1;  // Bit 10: CTS Interrupt Enable
    uint32_t ONEBIT   : 1;  // Bit 11: One sample bit method Enable
    uint32_t Reserved : 20; // Bits 12–31: Reserved
} USART_CR3_t;


/** USART GTPR Register prototype */
typedef volatile struct {
    uint32_t PSC      : 8;  // Bits 0–7: Prescaler value
    uint32_t GT       : 8;  // Bits 8–15: Guard time value
    uint32_t Reserved : 16; // Bits 16–31: Reserved
} USART_GTPR_t;


/** USART Register prototype */
typedef volatile struct {
    USART_SR_t*   SR;   // Offset 0x00: Status Register
    USART_DR_t*   DR;   // Offset 0x04: Data Register
    USART_BRR_t*  BRR;  // Offset 0x08: Baud Rate Register
    USART_CR1_t*  CR1;  // Offset 0x0C: Control Register 1
    USART_CR2_t*  CR2;  // Offset 0x10: Control Register 2
    USART_CR3_t*  CR3;  // Offset 0x14: Control Register 3
    USART_GTPR_t* GTPR; // Offset 0x18: Guard Time and Prescaler Register
} USART_t;

/** USART1 module hardware access (#USART_t) */
#define USART1 ((USART_t*) (USART1_BASE))

/**********************************************************************//**
 * @name Prototypes
 **************************************************************************/
/**@{*/
void stm32f4_usart1_init(void);

#endif //STM32F4_USART_H