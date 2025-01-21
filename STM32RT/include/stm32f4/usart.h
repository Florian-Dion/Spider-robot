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
#include <string.h>


// Définitions pour le périphérique et les registres
#define USART1_BASE 0x40011000U // Base address de USART1
#define USART1_IOREG(o)	_IOREG(USART1_BASE, o)


#define USART_SR USART1_IOREG(0x00)
#define USART_DR USART1_IOREG(0x04)
#define USART_BRR USART1_IOREG(0x08)
#define USART_CR1 USART1_IOREG(0x0C)
#define USART_CR2 USART1_IOREG(0x10)
#define USART_CR3 USART1_IOREG(0x14)
#define USART_GTPR USART1_IOREG(0x18)

// Constantes système
#define HSI_VALUE 16000000U // Fréquence de HSI à 16 MHz

// Interrupts
#define USART1_IRQ  37


// USART_SR Register
#define USART_SR_PE       (1 << 0)  // Bit 0: Parity error
#define USART_SR_FE       (1 << 1)  // Bit 1: Framing error
#define USART_SR_NF       (1 << 2)  // Bit 2: Noise flag
#define USART_SR_ORE      (1 << 3)  // Bit 3: Overrun error
#define USART_SR_IDLE     (1 << 4)  // Bit 4: Idle line detected
#define USART_SR_RXNE     (1 << 5)  // Bit 5: Read data register not empty
#define USART_SR_TC       (1 << 6)  // Bit 6: Transmission complete
#define USART_SR_TXE      (1 << 7)  // Bit 7: Transmit data register empty
#define USART_SR_LBD      (1 << 8)  // Bit 8: LIN break detection flag
#define USART_SR_CTS      (1 << 9)  // Bit 9: CTS flag

// USART_CR1 Register
#define USART_CR1_SBK      (1 << 0)  // Bit 0: Send Break
#define USART_CR1_RWU      (1 << 1)  // Bit 1: Receiver Wakeup
#define USART_CR1_RE       (1 << 2)  // Bit 2: Receiver Enable
#define USART_CR1_TE       (1 << 3)  // Bit 3: Transmitter Enable
#define USART_CR1_IDLEIE   (1 << 4)  // Bit 4: IDLE Interrupt Enable
#define USART_CR1_RXNEIE   (1 << 5)  // Bit 5: RXNE Interrupt Enable
#define USART_CR1_TCIE     (1 << 6)  // Bit 6: Transmission Complete Interrupt Enable
#define USART_CR1_TXEIE    (1 << 7)  // Bit 7: TXE Interrupt Enable
#define USART_CR1_PEIE     (1 << 8)  // Bit 8: PE Interrupt Enable
#define USART_CR1_PS       (1 << 9)  // Bit 9: Parity Selection
#define USART_CR1_PCE      (1 << 10) // Bit 10: Parity Control Enable
#define USART_CR1_WAKE     (1 << 11) // Bit 11: Wakeup method
#define USART_CR1_M        (1 << 12) // Bit 12: Word length
#define USART_CR1_UE       (1 << 13) // Bit 13: USART Enable
#define USART_CR1_OVER8    (1 << 15) // Bit 15: Oversampling mode

// USART_CR2 Register
#define USART_CR2_ADD      (1 << 0)  // Bits 0–3: Address of the USART node
#define USART_CR2_LBDL     (1 << 5)  // Bit 5: LIN Break Detection Length
#define USART_CR2_LBDIE    (1 << 6)  // Bit 6: LIN Break Detection Interrupt Enable
#define USART_CR2_LBCL     (1 << 8)  // Bit 8: Last Bit Clock pulse
#define USART_CR2_CPHA     (1 << 9)  // Bit 9: Clock Phase
#define USART_CR2_CPOL     (1 << 10) // Bit 10: Clock Polarity
#define USART_CR2_CLKEN    (1 << 11) // Bit 11: Clock Enable
#define USART_CR2_STOP     (1 << 12) // Bits 12–13: STOP bits
#define USART_CR2_LINEN    (1 << 14) // Bit 14: LIN Mode Enable

// USART_CR3 Register
#define USART_CR3_EIE      (1 << 0)  // Bit 0: Error Interrupt Enable
#define USART_CR3_IREN     (1 << 1)  // Bit 1: IrDA mode Enable
#define USART_CR3_IRLP     (1 << 2)  // Bit 2: IrDA Low-Power
#define USART_CR3_HDSEL    (1 << 3)  // Bit 3: Half-Duplex Selection
#define USART_CR3_NACK     (1 << 4)  // Bit 4: Smartcard NACK Enable
#define USART_CR3_SCEN     (1 << 5)  // Bit 5: Smartcard mode Enable
#define USART_CR3_DMAR     (1 << 6)  // Bit 6: DMA Enable Receiver
#define USART_CR3_DMAT     (1 << 7)  // Bit 7: DMA Enable Transmitter
#define USART_CR3_RTSE     (1 << 8)  // Bit 8: RTS Enable
#define USART_CR3_CTSE     (1 << 9)  // Bit 9: CTS Enable
#define USART_CR3_CTSIE    (1 << 10) // Bit 10: CTS Interrupt Enable
#define USART_CR3_ONEBIT   (1 << 11) // Bit 11: One sample bit method Enable

// USART GTPR Register
#define USART_GTPR_PSC      (1 << 0)  // Bits 0–7: Prescaler value
#define USART_GTPR_GT       (1 << 8)  // Bits 8–15: Guard time value



/**********************************************************************//**
 * @name Prototypes
 **************************************************************************/
/**@{*/
void stm32f4_usart1_init(void);

#endif //STM32F4_USART_H
