/*
 * periph_init.c
 *
 *  Created on: 26 Aðu 2021
 *      Author: @GALACICEK


 * ACLK = ~9.4kHz
 * SMCLK = MCLK = 8MHz
 *
 *
 * 1 cycles 125ns
 *      USCI_A0 9600 baud using BRCLK = 32768Hz.
 *
 *
 *   P3.6 (TX/RX_ENABLE) output as RE/DE [RS485](Recieve/Driver Enable)  pins
 *   P2.0 (TX_DATA,UCA0TXD) output  as DI [RS485](Driver Input) pins
 *   P2.1 (RX_DATA,UCA0RXD) input  as R0 [RS485](Recieve Out) pins
 *
 *
 *   P4.2 LED2  
 *   P4.7 LED1
 *
 */

#include"global.h"

void Perip_Init(){

    WDT_A_hold(WDT_A_BASE);

    SFRIE1 &= ~(OFIE);                      // Disable osc interrupt

    Perip_Init_GPIO();
    Perip_Init_CLK();
    Perip_Init_TIMA();
    Perip_Init_UARTA();         			//for RS85 Config
    __enable_interrupt();                   // Enable the global interrupt


}

void Perip_Init_GPIO(){

///* Set all GPIO to output low to reduce power consumption */
/*--------------------------------------------------*/
    P1DIR |=  All_BITS ;
    P1OUT = 0;

/*--------------------------------------------------
 *  Configure RS485 pins----------------------------
 *
 *      P2.0  TX_DATA pins OUTPUT  as DI [RS485](Driver Input)
 *      P2.1  RX_DATA pins INPUT as RO [RS485](Recieve Output)
 *
 */

    P2DIR |=  All_BITS ;
    P2OUT = 0;

    P2DIR &= ~BIT1; //INPUT
    P2DIR |= BIT0;  //OUTPUT
    //primary module
    P2SEL0  |= (BIT0 | BIT1);
    P2SEL1 &= ~ (BIT0 | BIT1);


/*--------------------------------------------------
 *
 *    P3.6  TX/RX_ENABLE   as RE/DE [RS485](Recieve/Driver Enable)
 * */
    P3DIR |=  All_BITS ;
    P3OUT = 0;

/*--------------------------------------------------
 *
 * P4.7 LED1
 * P4.2 LED2
 *
 *
 */

    P4DIR |=  All_BITS ;
    P4OUT = 0;

    P4DIR |= BIT2 | BIT7;  //OUTPUT

/*--------------------------------------------------*/

    P5DIR |=  All_BITS ;
    P5OUT = 0;

/*--------------------------------------------------*/

    P6DIR |=  All_BITS ;
    P6OUT = 0;

 /*--------------------------------------------------*/

    P7DIR |=  All_BITS ;
    P7OUT = 0;
/*--------------------------------------------------*/

    P9DIR |=  All_BITS ;
    P9OUT = 0;

/*--------------------------------------------------*/

    PJDIR |=  All_BITS ;
    PJOUT = 0;

    PJSEL0 = BIT4 | BIT5;                             // For XT1

    PMM_unlockLPM5();


}

/*CLOCK CONFÝGURATÝON----------------------------------------------------------------------
 * ACLK = ~37.5KHz
 * SMCLK = MCLK = 8MHz
 */
void Perip_Init_CLK(){

//    unsigned int xt1_setting_timeout;

    // Clock System Setup
     CSCTL0_H = CSKEY >> 8;                    // Unlock CS registers
     CSCTL1 = DCOFSEL_6;                       // Set DCO to 8MHz
     CSCTL2 = SELA__LFXTCLK | SELS__DCOCLK | SELM__DCOCLK;
     CSCTL3 = DIVA__1 | DIVS__1 | DIVM__1;     // Set all dividers to 1
     CSCTL4  &= ~LFXTOFF;
     do
       {
         CSCTL5 &= ~LFXTOFFG;                    // Clear XT1 fault flag
         SFRIFG1 &= ~OFIFG;
       }while (SFRIFG1&OFIFG);                   // Test oscillator fault flag
       CSCTL0_H = 0;     						// Lock CS registers


}

//TIMA0 CONFÝGURATÝON----------------------------------------------------------------------
//  time = TIM_PERIODE/ CLK
//
void Perip_Init_TIMA(){

     TA0CCTL0 = CCIE;                          // TACCR0 interrupt enabled
     TA0CCR0 = TIM_PERIODE;
     TA0CTL = TASSEL__ACLK | MC__UP | ID_1;          // ACLK, UP mode, divider=1

}


//UART CONFÝGURATÝON----------------------------------------------------------------------
/*
*	USCI_A0 UART echo at 9600 baud using BRCLK = 32768Hz.
*	Data Size 8
*	Party NONE 
*/
void Perip_Init_UARTA(){

    // Configure UART
    UCA0CTLW0 |= UCSWRST;
    UCA0CTLW0 = UCSSEL__ACLK;                  // Set ACLK = 32768 as UCBRCLK

    UCA0BR0 = UART_BR0;  // 9600 baud
    UCA0BR1 = UART_BR1;
    UCA0MCTLW |= UART_BRS|UART_BRF|UART_UCOS16;                      // 32768/9600 - INT(32768/9600)=0.41
                                                // UCBRSx value = 0x53 (See UG)
//    UCA0CTLW0 |= UCPEN | UCPAR;               // Parity enabled / Even parity
    UCA0CTL1 &= ~UCSWRST;                     // release from reset
    UCA0IE |= UCRXIE;                         // Enable USCI_A0 RX interrupt



}




