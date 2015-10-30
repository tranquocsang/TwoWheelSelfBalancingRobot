/*
 * MyUart.h
 *
 *  Created on: Jul 22, 2015
 *      Author: Bach
 */

#ifndef MYUART_H_
#define MYUART_H_

//*****************************************************************************
//
// Prototypes for the APIs.
//
//*****************************************************************************
void  UART0_init(void);
void  UART1_init(void);
void  UART2_init(void);
void UARTPuts(uint32_t UART_Base, const char *s);
void UARTPutn(uint32_t UART_Base, long Num);

#endif /* MYUART_H_ */
