/*
 * defines.h
 *
 *  Created on: 26 Aðu 2021
 *      Author: @GALACICEK
 */

#ifndef DEFINES_H_
#define DEFINES_H_

/*---------------------------------------------------------------------*/

//#define     Program_MODE
/*---------------------------------------------------------------------*/

#define UART_BAUDRATE_9600     9600
//#define UART_BAUDRATE_57600    57600
//#define UART_BAUDRATE_38400    38400



/*---------------------------------------------------------------------*/
//RS485 UART A0 CONFIG
#define UART_RXBUF                       UCA0RXBUF
#define UART_IFG                         UCA0IFG
#define UART_TXIFG                       UCTXIFG
#define UART_BASE                        EUSCI_A0_BASE
#define UART_VECTOR                      UCA0IV

#define UART0_INTERRUPT_FLAG             UCA0IFG
#define UART_TRANSMIT_INTERRUPT_FLAG     UCTXIFG

/*---------------------------------------------------------------------*/

// UartA0 modbus interrupt enable/disable
#define MB_RX_INT_ENABLE             (UCA0IE |= UCRXIE) & (UCA0IFG |= UCRXIFG)
#define MB_RX_INT_DISABLE            (UCA0IE &= ~UCRXIE) & (UCA0IFG &=~UCRXIFG)


//halfwave sending data
#define MODBUS_TX_Enable               P3OUT |= BIT6
#define MODBUS_RX_Enable               P3OUT &=~ BIT6

/*---------------------------------------------------------------------*/

#define LED1_GPIO_PORT         GPIO_PORT_P4
#define LED1_GPIO_PIN          GPIO_PIN7
#define LED1_ON                P4OUT |=  BIT7
#define LED1_OFF               P4OUT &=~ BIT7
#define LED1_TOGGLE            P4OUT ^= ~ BIT7

#define LED2_GPIO_PORT         GPIO_PORT_P4
#define LED2_GPIO_PIN          GPIO_PIN2
#define LED2_ON                P4OUT &=~ BIT2
#define LED2_OFF               P4OUT |=  BIT2
#define LED2_TOGGLE            P4OUT ^= ~ BIT2

/*---------------------------------------------------------------------*/
//Polynomial Variable for MODBUS CRC calculations parameter
#define POLYNOMIAL                      0xA001
#define MAX_MODBUS_BUFFER_SIZE          256



#endif /* DEFINES_H_ */
