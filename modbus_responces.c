/*
 * modbus_responces.c
 *
 *  Created on: 1 Eyl 2021
 *      Author: @GALACICEK
 */

#include "global.h"

volatile uint16_t check_writevalue=0;
extern volatile uint8_t mb_data_counter;


void MB_Read_Responce(uint16_t startadress,uint16_t quantity){

    uint8_t buffsize=0;

    buffsize = mb_data_counter;

    if ((startadress == MB_ADDR_REG_VAL0) && (quantity > 0))
      {

        mb_tx.Buffer[buffsize] = MSB2to1byte(modbusdata0);  buffsize++;//  Hi
        mb_tx.Buffer[buffsize] = LSB2to1byte(modbusdata0);  buffsize++;//  Lo
        startadress++;
        quantity--;
      }
    if ((startadress == MB_ADDR_REG_VAL1) && (quantity > 0))
    {
        mb_tx.Buffer[buffsize] = MSB2to1byte(modbusdata1);  buffsize++;// Hi
        mb_tx.Buffer[buffsize] = LSB2to1byte(modbusdata1);  buffsize++;// Lo
        startadress++;
        quantity--;
    }
    if ((startadress == MB_ADDR_REG_VAL2) && (quantity > 0))
    {
        mb_tx.Buffer[buffsize] = MSB2to1byte(modbusdata2);   buffsize++; //Hi
        mb_tx.Buffer[buffsize] = LSB2to1byte(modbusdata2);;  buffsize++; // Lo
        startadress++;
        quantity--;
    }
    if ((startadress == MB_ADDR_REG_VAL3) && (quantity > 0))
    {
        mb_tx.Buffer[buffsize] = MSB2to1byte(modbusdata3);   buffsize++; // Hi
        mb_tx.Buffer[buffsize] = LSB2to1byte(modbusdata3);   buffsize++;//Lo
        startadress++;
        quantity--;
    }
    if ((startadress == MB_ADDR_REG_VAL4) && (quantity > 0))
    {
        mb_tx.Buffer[buffsize] = MSB2to1byte(modbusdata4);   buffsize++;//Hi
        mb_tx.Buffer[buffsize] = LSB2to1byte(modbusdata4);   buffsize++;//Lo
        startadress++;
        quantity--;
    }
    if ((startadress == MB_ADDR_REG_VAL5) && (quantity > 0))
    {
        mb_tx.Buffer[buffsize] = MSB2to1byte(modbusdata5);   buffsize++;  // Hi
        mb_tx.Buffer[buffsize] = LSB2to1byte(modbusdata5);   buffsize++; // Lo
        startadress++;
        quantity--;
    }
    if ((startadress == MB_ADDR_REG_VAL6) && (quantity > 0))
    {
        mb_tx.Buffer[buffsize] = MSB2to1byte(modbusdata6);   buffsize++;  // Hi
        mb_tx.Buffer[buffsize] = LSB2to1byte(modbusdata6);   buffsize++; // Lo
        startadress++;
        quantity--;
    }
    if ((startadress == MB_ADDR_REG_VAL7) && (quantity > 0))
    {
        mb_tx.Buffer[buffsize] = MSB2to1byte(modbusdata7);  buffsize++;  // Hi
        mb_tx.Buffer[buffsize] = LSB2to1byte(modbusdata7);  buffsize++;  // Lo
        startadress++;
        quantity--;
    }
    if ((startadress == MB_ADDR_REG_VAL8) && (quantity > 0))
    {
        mb_tx.Buffer[buffsize] = MSB2to1byte(modbusdata8);   buffsize++; // Hi
        mb_tx.Buffer[buffsize] = LSB2to1byte(modbusdata8);   buffsize++;// Lo
        startadress++;
        quantity--;
    }
    if ((startadress == MB_ADDR_REG_VAL9) && (quantity > 0))
    {
        mb_tx.Buffer[buffsize] = MSB2to1byte(modbusdata9);  buffsize++;  // Hi
        mb_tx.Buffer[buffsize] = LSB2to1byte(modbusdata9);  buffsize++;  // Lo
        startadress++;
        quantity--;
    }
    if ((startadress == MB_ADDR_REG_VAL10) && (quantity > 0))
    {
        mb_tx.Buffer[buffsize] = MSB2to1byte(modbusdata10);   buffsize++; // Hi
        mb_tx.Buffer[buffsize] = LSB2to1byte(modbusdata10);   buffsize++;// Lo
        startadress++;
        quantity--;
    }
    if ((startadress == MB_ADDR_REG_VAL11) && (quantity > 0))
    {
        mb_tx.Buffer[buffsize] = MSB2to1byte(modbusdata11);   buffsize++;// Hi
        mb_tx.Buffer[buffsize] = LSB2to1byte(modbusdata11);   buffsize++; // Lo
        startadress++;
        quantity--;
    }

    if ((startadress == MB_ADDR_REG_VAL12) && (quantity > 0))
    {
        mb_tx.Buffer[buffsize] = MSB2to1byte(modbusdata12);  buffsize++;// Hi
        mb_tx.Buffer[buffsize] = LSB2to1byte(modbusdata12);  buffsize++; // Lo
        startadress++;
        quantity--;
    }
    if ((startadress == MB_ADDR_REG_VAL13) && (quantity > 0))
    {
        mb_tx.Buffer[buffsize] = MSB2to1byte(modbusdata13);   buffsize++; // Hi
        mb_tx.Buffer[buffsize] = LSB2to1byte(modbusdata13);   buffsize++; // Lo
        startadress++;
        quantity--;
    }
    if ((startadress == MB_ADDR_REG_VAL14) && (quantity > 0))
    {
        mb_tx.Buffer[buffsize] = MSB2to1byte(modbusdata14);  buffsize++;// Hi
        mb_tx.Buffer[buffsize] = LSB2to1byte(modbusdata14); buffsize++;// Lo
        startadress++;
        quantity--;
    }
    if ((startadress == MB_ADDR_REG_VAL15) && (quantity > 0))
    {
        mb_tx.Buffer[buffsize] = MSB2to1byte(modbusdata15);  buffsize++;// Hi
        mb_tx.Buffer[buffsize] = LSB2to1byte(modbusdata15);  buffsize++;// Lo
        startadress++;
        quantity--;
    }
    if ((startadress == MB_ADDR_REG_VAL16) && (quantity > 0))
    {
        mb_tx.Buffer[buffsize] = MSB2to1byte(modbusdata16); buffsize++;// Hi
        mb_tx.Buffer[buffsize] = LSB2to1byte(modbusdata16);  buffsize++;// Lo
        startadress++;
        quantity--;
    }
    if ((startadress == MB_ADDR_REG_VAL17) && (quantity > 0))
    {
        mb_tx.Buffer[buffsize] = MSB2to1byte(modbusdata17);  buffsize++;// Hi
        mb_tx.Buffer[buffsize] = LSB2to1byte(modbusdata17); buffsize++;// Lo
        startadress++;
        quantity--;
    }
    if ((startadress == MB_ADDR_REG_VAL18) && (quantity > 0))
    {
        mb_tx.Buffer[buffsize] = MSB2to1byte(modbusdata18);   buffsize++;// Hi
        mb_tx.Buffer[buffsize] = LSB2to1byte(modbusdata18);  buffsize++;// Lo
        startadress++;
        quantity--;
    }
    if ((startadress == MB_ADDR_REG_VAL19) && (quantity > 0))
    {
        mb_tx.Buffer[buffsize] = MSB2to1byte(modbusdata19);  buffsize++;// Hi
        mb_tx.Buffer[buffsize] = LSB2to1byte(modbusdata19);  buffsize++;// Lo
        startadress++;
        quantity--;
    }
    if ((startadress == MB_ADDR_REG_VAL20) && (quantity > 0))
    {
        mb_tx.Buffer[buffsize] = MSB2to1byte(modbusdata20); buffsize++;// Hi
        mb_tx.Buffer[buffsize] = LSB2to1byte(modbusdata20); buffsize++;// Lo
        quantity--;

    }

    if (quantity >= 65535){
        MB_ErrorHandler(MODBUS_ERROR_CODE_04);

    }else {
        mb_data_counter = buffsize;
        MB_Responce_Task();
    }



}


void MB_Write_Responce(uint16_t regadress,uint16_t value){

//    uint8_t buffsize = 0;
//
//    buffsize = mb_data_counter;

    switch (regadress) {
        case MB_ADDW_REG_VAL1:
            check_writevalue =value ;   //for check data write value

            break;
        case MB_ADDW_REG_VAL2:
            check_writevalue =value ;

            break;
        case MB_ADDW_REG_VAL3:
            check_writevalue =value ;

            break;
        case MB_ADDW_REG_VAL4:
            check_writevalue =value ;

            break;
        case MB_ADDW_REG_VAL5:
            check_writevalue =value ;

            break;
        case MB_ADDW_REG_VAL6:
            check_writevalue =value ;

            break;
        case MB_ADDW_REG_VAL7:
            check_writevalue =value ;

            break;
        case MB_ADDW_REG_VAL8:
            check_writevalue =value ;

            break;
        case MB_ADDW_REG_VAL9:
            check_writevalue =value ;

            break;
        case MB_ADDW_REG_VAL10:
            check_writevalue =value ;

            break;
        case MB_ADDW_REG_VAL11:
            check_writevalue =value ;

            break;
        case MB_ADDW_REG_VAL12:
            check_writevalue =value ;

            break;
        case MB_ADDW_REG_VAL13:
            check_writevalue =value ;

            break;
        case MB_ADDW_REG_VAL14:
            check_writevalue =value ;

            break;
        case MB_ADDW_REG_VAL15:
            check_writevalue =value ;

            break;
        case MB_ADDW_REG_VAL16:
            check_writevalue =value ;

            break;
        case MB_ADDW_REG_VAL17:
            check_writevalue =value ;

            break;
        case MB_ADDW_REG_VAL18:
            check_writevalue =value ;

            break;
        case MB_ADDW_REG_VAL19:
            check_writevalue =value ;

            break;
        case MB_ADDW_REG_VAL20:
            check_writevalue =value ;

            break;
        default:

            MB_ErrorHandler(MODBUS_ERROR_CODE_04);

            break;
    }

    if(mb_rx.FunctCode==Write_Single_Register){  //Write_Single_Register

        MB_Responce_Task();

    }




}


