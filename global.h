/*
 * global.h
 *
 *  Created on: 26 Aðu 2021
 *      Author: @GALACICEK
 */

#ifndef GLOBAL_H_
#define GLOBAL_H_



#include "stdio.h"
#include "stdlib.h"
#include "stdint.h"
#include "strings.h"

#include "defines.h"
#include "driverlib.h"
#include "periph_init.h"
#include "modbus_reg.h"
#include "modbusRTU.h"
#include "modbus_responces.h"

/*--------------------Macros-------------------------------------*/


#define MSB2to1byte(a)    ( ( uint8_t)((a & 0xFF00) >> 8 ) )
#define LSB2to1byte(a)    ( (uint8_t)(a & 0x00FF) )

#define MSB1to2byte(a)    ( ( uint16_t)((a & 0xFFFF) << 8 ) )
#define LSB1to2byte(a)    ( (uint16_t)(a & 0xFFFF) )

#define IsOKCRC(crc,bufmsb,buflsb)        ( (    (((uint8_t)((crc & 0xFF00) >> 8 ))== bufmsb)  &&   (((uint8_t)(crc & 0x00FF) )==buflsb)  ) ?1:0 )

/*----------------------------------------------------------------*/

extern volatile uint32_t timeTick;

extern uint8_t IsTimeEllapsed(uint32_t *LastCall,uint32_t Time);

/*----------------------------------------------------------------*/

extern volatile uint32_t MBCHECK_TimeRX;




typedef union {

    struct{
        uint8_t MB_RX_Start:1;  // rxflg 1 olursa txflg 0 olmalýdýr.
        uint8_t MB_TX_Start:1;
        uint8_t Flag3:1;  
        uint8_t Flag4:1;
        uint8_t Flag5:1;
        uint8_t Flag6:1;
        uint8_t Flag7:1;
        uint8_t Flag8:1;
    }Bits;
    uint8_t AllBits;

}Flag_t;

extern Flag_t Flg;

#endif /* GLOBAL_H_ */
