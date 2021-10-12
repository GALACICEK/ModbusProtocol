/*
 * interrupts.c
 *
 *  Created on: 26 Aðu 2021
 *      Author: @GALACICEK
 */
#include "global.h"

volatile uint32_t timeTick;
volatile uint32_t MBCHECK_TimeRX;
uint8_t RX_Counter;


// Timer0_A0 interrupt service routine

#pragma vector = TIMER0_A0_VECTOR
__interrupt void Timer0_A0_ISR (void)
{
//Check to working correctly	interrupt 
//    LED1_TOGGLE;
    timeTick++;
   __bic_SR_register_on_exit(LPM3_bits);    // Wake up
}



//RS485  interrupt service routine
#pragma vector=USCI_A0_VECTOR
__interrupt void USCI_A0_ISR(void)

{
  switch(__even_in_range(UCA0IV,USCI_UART_UCTXCPTIFG))
  {
    case USCI_NONE: break;
    case USCI_UART_UCRXIFG:

        if(!Flg.Bits.MB_TX_Start && Flg.Bits.MB_RX_Start){

            mb_rx.Buffer[RX_Counter]=UART_RXBUF;

            if(RX_Counter>=MAX_MODBUS_BUFFER_SIZE){
                RX_Counter=0;
            }else{
                RX_Counter++;
                MBCHECK_TimeRX=timeTick;
            }

        }
//you can open commands to understand to entry inside interrupt
//     __no_operation();	
//__bic_SR_register_on_exit(LPM3_bits);
      break;
    case USCI_UART_UCTXIFG: break;
    case USCI_UART_UCSTTIFG: break;
    case USCI_UART_UCTXCPTIFG: break;
    default: break;
  }
}
