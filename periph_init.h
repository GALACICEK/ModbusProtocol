/*
 * periph_init.h
 *
 *  Created on: 26 Aðu 2021
 *      Author: @GALACICEK
 */

#ifndef PERIPH_INIT_H_
#define PERIPH_INIT_H_



//LIBS--------------------------------------------------
#include "driverlib.h"

//DEFINES-----------------------------------------------
#define MCLK_FREQ_MHZ        8                    // MCLK = 8MHz

#define TIM_PERIODE          328   //CLK = 32768Hz periode:16--~1ms   periode:328   --10ms              // CLK= 1MHz periode:1000--1ms
#define All_BITS             (BIT0 | BIT1 | BIT2 | BIT3 | BIT4 | BIT5 | BIT6 | BIT7 | BIT8 | BIT9 | BITA | BITB | BITC | BITD | BITE | BITF)

#if defined(UART_BAUDRATE_9600)	//BRCLK = 32768 HZ Cyristal

#define UART_BR0            3
#define UART_BR1            0x00
#define UART_BRS            0x5300
#define UART_BRF            UCBRF_0
#define UART_UCOS16         0x0000
#endif

#if defined(UART_BAUDRATE_57600)    //BRCLK = 8MHz.

#define UART_BR0            8
#define UART_BR1            0x00
#define UART_BRS            0xF700
#define UART_BRF            UCBRF_10
#define UART_UCOS16         UCOS16
#endif

#if defined(UART_BAUDRATE_38400)    //BRCLK = 8MHz.

#define UART_BR0            13
#define UART_BR1            0x00
#define UART_BRS            0x8400
#define UART_BRF            UCBRF_1
#define UART_UCOS16         UCOS16
#endif


//Functions---------------------------------------------
extern void     Perip_Init(void);
extern void     Perip_Init_CLK(void);

extern void     Perip_Init_GPIO(void);
extern void     Perip_Init_TIMA(void);
extern void     Perip_Init_UARTA(void);

#endif /* PERIPH_INIT_H_ */
