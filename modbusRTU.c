/*
 * modbusRTU.c
 *
 *  Created on: 26 Aðu 2021
 *      Author: @GALACICEK
 */

#include "global.h"

modbus_t mb_rx, mb_tx;
Flag_t Flg;
volatile uint8_t mb_data_counter =0;

extern uint8_t RX_Counter;


void MB_Init(void){

    MB_CreateVariable(&mb_rx);
    MB_CreateVariable(&mb_tx);

    //my device is slave and wait to request
    Flg.Bits.MB_TX_Start=0;
    Flg.Bits.MB_RX_Start=1;
}

/****************************************************************
 * @fn          MB_Request_Task
 *
 * @brief
 *
 * @param
 *
 *  hercules : $01$03$03$F2$00$03$A4$7C
 *
 * Request: [01] [03] [03F2] [0003] [A47C]
 *            |    |    |      |      |-> CRC16 (2 bytes)
 *            |    |    |      |
 *            |    |    |      |-> Number Of Registers (2 bytes)
 *            |    |    |
 *            |    |    |-> Register Offset (2 bytes)  startreg: MB_ADDR_REG_VAL10
 *            |    |    |
 *            |    | -> Function Code (1 byte)
 *            |
 *            |-> Slave ID (1 byte)
 *

 * @return     none
 *
 */
void MB_Request_Task(void){

    if(MB_Check_RXBuffer_Complete()){

        MB_RX_INT_DISABLE;

        Flg.Bits.MB_TX_Start=0;  //request doðru geldi responce oluþturma çalýþmasý baþladý
        Flg.Bits.MB_RX_Start=0;

        mb_rx.FunctCode     = mb_rx.Buffer[1];

        //acoording to function code send function

        switch (mb_rx.FunctCode) {
            case Read_Holding_Registers:
                ReadHolding_RegisterHandler();

                break;

            case Write_Single_Register:
                WriteSingle_RegisterHandler();

                break;

            case Write_Multiple_Registers:
                WriteMultiple_RegisterHandler();

                break;

            case Mask_Write_Register:
                MaskWrite_RegisterHandler();

                break;

            case ReadWrite_Multiple_Registers:
                ReadWriteMultiple_RegisterHandler();

                break;

            default:
                MB_ErrorHandler(MODBUS_ERROR_CODE_01);
                break;
        }


        mb_rx.FunctCode=0;
        //errorcodes based mb_rx.buffer , maybe dont erase buffer ???????
        ERASE_BUFFER(&mb_rx.Buffer[0], 10);

        MODBUS_RX_Enable;

        //flagler ile interrupt kontrol etmek yerine interrupt kapatýp açmayý dene
        Flg.Bits.MB_TX_Start=0;
        Flg.Bits.MB_RX_Start=1;
    }else {

        RX_Counter=0;
        ERASE_BUFFER(&mb_rx.Buffer[0],254);



    }


}


/*******************************************************************************
 *   @fn         MB_Responce_Task
 *
 *   @brief      parameters
 *
 *
 *
 *   @param      none
 *
 *
 *   @return     none
 */

void MB_Responce_Task(void){

    uint16_t crcvalue = 0;

    crcvalue = MB_CRC16(&mb_tx.Buffer[0], mb_data_counter);    //son sayýnýn sýfýr gelmesi durumunda??
    mb_tx.Buffer[mb_data_counter]= MSB2to1byte(crcvalue);
    mb_tx.Buffer[mb_data_counter+1]= LSB2to1byte(crcvalue);

    Flg.Bits.MB_TX_Start=1; //transmit baþladý
    Flg.Bits.MB_RX_Start=0;

    MB_Transmit_Buffer(&mb_tx.Buffer[0], (mb_data_counter+2));
//    LED1_TOGGLE;    //transmit ok

    //transmit ok
    ERASE_BUFFER(&mb_tx.Buffer[0], (mb_data_counter+3));
    mb_data_counter=0;

//    MODBUS_RX_Enable;
    MB_RX_INT_ENABLE;
    Flg.Bits.MB_TX_Start=0; //wait to receive
    Flg.Bits.MB_RX_Start=1;

}



/*******************************************************************************
 *   @fn         ReadHolding_RegisterHandler
 *
 *   @brief      parameters
 *              Request:
 *                  Function code     :     1 Byte      0x03
 *                  Starting Address  :     2 Bytes     0x0000 to 0xFFFF
 *                  Quantity of Registers:  2 Bytes     1 to 125 (0x7D)
 *
 *              Response:
 *                  Function code     :       1 Byte    0x03
 *                  Byte count        :       1 Byte    2 x N*
 *                  Register value    :       N* x 2 Bytes
 *
 *              Error:
 *                  Error code        :       1 Byte    0x83
 *                  Exception code    :       1 Byte    01 or 02 or 03 or 04
 *
 *  EXAMPLE      hercules : $01$03$03$F2$00$03$7C$A4
 *
 *   @param      none
 *
 *   @return     none
 */
void ReadHolding_RegisterHandler(void){

    uint16_t startaddress = 0;
    uint16_t regqty =0;


    startaddress  = MSB1to2byte(mb_rx.Buffer[2]) | LSB1to2byte(mb_rx.Buffer[3]);
    regqty        = MSB1to2byte(mb_rx.Buffer[4]) | LSB1to2byte(mb_rx.Buffer[5]);


    if(regqty>=0x0001 && regqty<=0x007D){

        if(startaddress>=MB_ADDR_REG_VAL0 && (startaddress+regqty)<=MB_ADDR_REG_VAL20){    //okuma registerlarý arasýnda deðer geldiyse fonksiyonu çalýþtýr

            mb_tx.Buffer[1] = mb_rx.FunctCode;
            mb_tx.Buffer[2] = regqty*2;
            mb_data_counter=3;

            MB_Read_Responce(startaddress,regqty);

        }else
        {MB_ErrorHandler(MODBUS_ERROR_CODE_02);}

    }else
    {MB_ErrorHandler(MODBUS_ERROR_CODE_03);}



}

/*******************************************************************************
 *   @fn         WriteSingle_RegisterHandler
 *
 *   @brief      parameters
 *                Request:
 *                  Function code     :     1 Byte      0x06
 *                  Register Address  :     2 Bytes     0x0000 to 0xFFFF
 *                  Register Value    :     2 Bytes     0x0000 to 0xFFFF
 *
 *
 *              Response:
 *                  Function code     :       1 Byte    0x06
 *                  Register Address  :       2 Byte    0x0000 to 0xFFF
 *                  Register Value    :       2 Bytes   0x0000 to 0xFFFF
 *
 *              Error:
 *                  Error code        :       1 Byte    0x86
 *                  Exception code    :       1 Byte    01 or 02 or 03 or 04
 *
 *
 *  EXAMPLE      hercules             : $01$06$04$01$00$23$E3$98
 *
 *   @param      none
 *
 *   @return     none
 */

void WriteSingle_RegisterHandler(void){

    uint16_t writeaddress = 0;
    uint16_t writevalue = 0;


    writeaddress  = MSB1to2byte(mb_rx.Buffer[2]) | LSB1to2byte(mb_rx.Buffer[3]);
    writevalue    = MSB1to2byte(mb_rx.Buffer[4]) | LSB1to2byte(mb_rx.Buffer[5]);

    if((writevalue>=0x0000) && (writevalue<=0xFFFF)){

        if((writeaddress >= MB_ADDW_REG_VAL1) && (writeaddress <= MB_ADDW_REG_VAL20)){    //yazma registerlarý arasýnda deðer geldiyse fonksiyonu çalýþtýr

            mb_tx.Buffer[1] = mb_rx.FunctCode;
            mb_tx.Buffer[2] = mb_rx.Buffer[2];
            mb_tx.Buffer[3] = mb_rx.Buffer[3];
            mb_tx.Buffer[4] = mb_rx.Buffer[4];
            mb_tx.Buffer[5] = mb_rx.Buffer[5];

            mb_data_counter = 6;

            MB_Write_Responce(writeaddress, writevalue);

        }else
        {MB_ErrorHandler(MODBUS_ERROR_CODE_02);}

    }else
    {MB_ErrorHandler(MODBUS_ERROR_CODE_03);}



}

/*******************************************************************************
 *   @fn         WriteMultiple_RegisterHandler
 *
 *   @brief      parameters
 *                Request:
 *                  Function code     :     1 Byte      0x10
 *                  Starting Address  :     2 Bytes     0x0000 to 0xFFFF
 *                  Quantity of Registers:  2 Bytes     0x0001 to 0x007B
 *                  Byte count        :     1 Byte      2 x N*
 *                  Register value    :     N* x 2 Bytes value
 *
 *
 *              Response:
 *                  Function code     :       1 Byte    0x06
 *                  Starting Address  :       2 Byte    0x0000 to 0xFFF
 *                  Quantity of Registers:    2 Byte    1 to 123 (0x7B)
 *
 *              Error:
 *                  Error code        :       1 Byte    0x90
 *                  Exception code    :       1 Byte    01 or 02 or 03 or 04
 *
 *
 *  EXAMPLE      hercules             : $01$10$04$05$00$03$06$00$09$00$10$00$11$68$FE
 *                                      Start address: MB_ADDW_REG_VAL9
 *                                      Quantity of Registers : 0003
 *                                      Byte count :06
 *
 *
 *   @param      none
 *
 *   @return     none
 */

void    WriteMultiple_RegisterHandler(void){

    uint16_t startaddress = 0;
    uint16_t regqty = 0;
    uint8_t  count = 0;



    startaddress  = MSB1to2byte(mb_rx.Buffer[2]) | LSB1to2byte(mb_rx.Buffer[3]);
    regqty        = MSB1to2byte(mb_rx.Buffer[4]) | LSB1to2byte(mb_rx.Buffer[5]);
    count         = mb_rx.Buffer[6];


    if((regqty>=0x0001 && regqty<=0x007B) && (count == regqty*2)){

       if((startaddress>=MB_ADDW_REG_VAL1) && (startaddress+regqty)<=MB_ADDW_REG_VAL20){    //okuma registerlarý arasýnda deðer geldiyse fonksiyonu çalýþtýr

            mb_tx.Buffer[1] = mb_rx.FunctCode;
            mb_tx.Buffer[2] = mb_rx.Buffer[2];
            mb_tx.Buffer[3] = mb_rx.Buffer[3];
            mb_tx.Buffer[4] = mb_rx.Buffer[4];
            mb_tx.Buffer[5] = mb_rx.Buffer[5];

            mb_data_counter = 6;

            uint16_t value=0;
            uint8_t i;
            for(i=0; i<regqty ; i++){

                value = MSB1to2byte(mb_rx.Buffer[mb_data_counter+1]) | LSB1to2byte(mb_rx.Buffer[mb_data_counter+2]);


                MB_Write_Responce(startaddress+i,value);

                mb_data_counter+=2;

            }

            mb_data_counter = 6;
            MB_Responce_Task();


        }else
        {MB_ErrorHandler(MODBUS_ERROR_CODE_02);}

    }else
    {MB_ErrorHandler(MODBUS_ERROR_CODE_03);}



}

/*******************************************************************************
 *   @fn         ReadWriteMultiple_RegisterHandler
 *
 *   @brief      parameters
 *                Request:
 *                  Function code           :     1 Byte      0x17
 *                  Read  Starting Address  :     2 Bytes     0x0000 to 0xFFFF
 *                  Quantity to Read        :     2 Bytes     0x0001 to 0x007D
 *                  Write  Starting Address :     2 Bytes     0x0000 to 0xFFFF
 *                  Quantity to Write       :     2 Bytes     0x0001 to 0x0079
 *                  Write Byte count        :     1 Byte      2 x N*
 *                  Write Register value    :     N* x 2 Bytes value
 *
 *
 *              Response:
 *                  Function code     :       1 Byte    0x17
 *                  Byte count        :       1 Byte    2 x N*
 *                  Read Register value   :   N* x 2 Bytes
 *
 *              Error:
 *                  Error code        :       1 Byte    0x97
 *                  Exception code    :       1 Byte    01 or 02 or 03 or 04
 *
 *  EXAMPLE      hercules             : $01$17$03$ED$00$05$04$0D$00$08$00$AA$00$BB$00$CC$60$AF  ERROR RESPONCE TEST
 *                                    : $01$17$03$ED$00$05$04$0D$00$03$06$00$AA$00$BB$00$CC$49$06  GENERATED TRUE RESPONCE
 *                                      READ  ADDRESS :MB_ADDR_REG_VAL5  Qty : 0005
 *                                      WRITE ADDRESS :MB_ADDW_REG_VAL17 Qty : 0008 //hata kodu döncek 0008 hata kodu dönmemesi icin
 *
 *
 *   @param      none
 *
 *   @return     none
 */

void        ReadWriteMultiple_RegisterHandler(void){

    uint16_t readaddress = 0;
    uint16_t readqty = 0;
    uint16_t writeaddress = 0;
    uint16_t writeqty = 0;
    uint8_t  writecount = 0;

    readaddress   = MSB1to2byte(mb_rx.Buffer[2]) | LSB1to2byte(mb_rx.Buffer[3]);
    readqty       = MSB1to2byte(mb_rx.Buffer[4]) | LSB1to2byte(mb_rx.Buffer[5]);

    writeaddress   = MSB1to2byte(mb_rx.Buffer[6]) | LSB1to2byte(mb_rx.Buffer[7]);
    writeqty       = MSB1to2byte(mb_rx.Buffer[8]) | LSB1to2byte(mb_rx.Buffer[9]);
    writecount     = mb_rx.Buffer[10];


    if((writeqty>=0x0001 && writeqty<=0x0079)    &&
            (writecount == writeqty*2)           &&
            (readqty>=0x0001 && readqty<=0x007D)){

       if((writeaddress>=MB_ADDW_REG_VAL1)       &&  (writeaddress+writeqty)<=MB_ADDW_REG_VAL20 &&
               (readaddress>=MB_ADDR_REG_VAL0)   && (readaddress+readqty)<=MB_ADDR_REG_VAL20){


           mb_tx.Buffer[1] = mb_rx.FunctCode;
           mb_tx.Buffer[2] = readqty*2; //bit kaydýrma gerkebilir

           mb_data_counter= 10; //requesti okumak için

           uint16_t value=0;
           uint8_t i;

           for(i=0; i<writeqty ; i++){
               value = MSB1to2byte(mb_rx.Buffer[mb_data_counter+1]) | LSB1to2byte(mb_rx.Buffer[mb_data_counter+2]);
               MB_Write_Responce(writeaddress+i,value);
               mb_data_counter+=2;
           }

           mb_data_counter=3;   //responce oluþturmak için

           MB_Read_Responce(readaddress,readqty);   //okuyup responce oluþturacak þekilde fonksiyon

       }else
       {
           MB_ErrorHandler(MODBUS_ERROR_CODE_02);
       }

    }else
    {
        MB_ErrorHandler(MODBUS_ERROR_CODE_03);
    }





}

/*******************************************************************************
 *   @fn         MaskWrite_RegisterHandler
 *
 *   @brief      parameters
 *                Request:
 *                  Function code     :     1 Byte      0x16
 *                  Starting Address  :     2 Bytes     0x0000 to 0xFFFF
 *                  Quantity of Registers:  2 Bytes     0x0001 to 0x007B
 *                  Byte count        :     1 Byte      2 x N*
 *                  Register value    :     N* x 2 Bytes value
 *
 *
 *              Response:
 *                  Function code     :       1 Byte    0x06
 *                  Starting Address  :       2 Byte    0x0000 to 0xFFF
 *                  Quantity of Registers:    2 Byte    1 to 123 (0x7B)
 *
 *              Error:
 *                  Error code        :       1 Byte    0x90
 *                  Exception code    :       1 Byte    01 or 02 or 03 or 04
 *
 *
 *
 *
 *   @param      none
 *
 *   @return     none
 */
void        MaskWrite_RegisterHandler(void){

//    uint16_t writeaddress = 0;
//    uint16_t ANDmask      = 0;
//    uint16_t ORmask       = 0;


}


/*******************************************************************************
 *   @fn         MB_Check_RXBuffer_Complete
 *
 *   @brief      parameters
 *
 *
 *
 *   @param      none
 *               while bufsize = 0 , CRC_CAL calculate 0x4E55
 *
 *   @return     none
 */

uint8_t MB_Check_RXBuffer_Complete(void){

    uint16_t CRC_CAL=0;
    uint8_t bufsize=0;

    bufsize = SizeofArray(mb_rx.Buffer);

    if(bufsize!=0){
        bufsize = SizeofArray(mb_rx.Buffer);
        _no_operation();

        CRC_CAL = MB_CRC16(&mb_rx.Buffer[0], (uint8_t)(bufsize-2));

        if(IsOKCRC(CRC_CAL,mb_rx.Buffer[bufsize-2], mb_rx.Buffer[bufsize-1]) && MB_CheckSlaveID()){

            mb_tx.Buffer[0] = mb_rx.Buffer[0];

#warning crc deðerlerini eksik value gelmesi durumunda value olarak almamasý için siliyorum.
            mb_rx.Buffer[bufsize-2]='\0';
            mb_rx.Buffer[bufsize-1]='\0';

            return 1;
        }
    }

    return 0;

}

/*******************************************************************************
 *   @fn         MB_ErrorHandler
 *
 *   @brief      MODBUS except/error codes
 *
 *     ILLEGAL_FUNCTION                            0x01
 *     ILLEGAL_DATA_ADDRESS                        0x02
 *     ILLEGAL_DATA_VALUE                          0x03
 *     SERVER_DEVICE_FAILURE                       0x04
 *     ACKNOWLEDGE                                 0x05
 *     SERVER_DEVICE_BUSY                          0x06
 *     MEMORY_PARITY_ERROR                         0x08
 *     GATEWAY_PATH_UNAVAILABLE                    0x0A
 *     GATEWAY_TARGET_DEVICE_FAILED_TO_RESPOND     0x0B
 *
 *
 *
 *   @param      none
 *
 *   @return     none
 */

void MB_ErrorHandler(uint8_t errorCode) {   //tekrar kontrol et

    ERASE_BUFFER(&mb_tx.Buffer[0],SizeofArray(mb_tx.Buffer));//ERASE_BUFFER(&mb_tx.Buffer[0], (uint8_t)strlen((const char *)mb_tx.Buffer));

    mb_tx.Buffer[0] = mb_rx.Buffer[0];
    mb_tx.Buffer[1] = mb_rx.Buffer[1] | 0x80;
    mb_tx.Buffer[2] = errorCode;

    mb_tx.Buffer[3] = MSB2to1byte(MB_CRC16(&mb_tx.Buffer[0], 3));
    mb_tx.Buffer[4] = LSB2to1byte(MB_CRC16(&mb_tx.Buffer[0], 3));

    Flg.Bits.MB_TX_Start=1;
    Flg.Bits.MB_RX_Start=0;


    MB_Transmit_Buffer(&mb_tx.Buffer[0], 5);
    //errorcodes based mb_rx.buffer , maybe dont erase buffer ???????
    ERASE_BUFFER(&mb_rx.Buffer[0], SizeofArray(mb_rx.Buffer));


    //    MODBUS_RX_Enable;
        MB_RX_INT_ENABLE;
        Flg.Bits.MB_TX_Start=0; //wait to receive
        Flg.Bits.MB_RX_Start=1;

#if defined(Program_MODE)
    ERASE_BUFFER(&mb_tx.Buffer[0], 6);
#endif



}

/*******************************************************************************
  *   @fn         MB_CRC16
  *
  *   @brief      Calculate 2 bytes CRC Value
  *
  *              MSB   : (uint8_t)((CRC & 0xFF00) >> 8);
  *              LSB   : (uint8_t)(CRC & 0x00FF);
  *              Check Request CRC
  *              if ( (Buff[size-2]) ==  LSB) && (Buff[size-1]) ==  MSB)){
  *                 return 1;
  *             }else{
  *                  return 0;
  *                  }
  *
  *   @param      none
  *
  *   @return     uint16_t
  *
  */

uint16_t MB_CRC16(uint8_t * Buff, uint8_t bsize){

    uint16_t CRC = 0xFFFF;

    int i;
    for (i = 0; i < bsize; i++)
    {
        CRC ^=(uint16_t)*(Buff+i);
        int n;
        for (n = 0; n < 8; n++)
        {
            if (CRC & 0x0001){ // If the LSB was 1 Exclusive OR the CRC register with the polynomial value A001 hex (1010 0000 0000 0001)
                CRC >>= 1; //Shift the CRC register one bit to the right (toward the LSB)
                CRC &= 0x7FFF;      // zero–filling the MSB
                CRC ^= POLYNOMIAL; //XOR Polynomial value A001 hex (1010 0000 0000 0001)
            }else {                   //If the LSB was 0
                CRC >>= 1; //Shift the CRC register one bit to the right (toward the LSB)
                CRC &= 0x7FFF;      // zero–filling the MSB
            } //Repeat Steps 3 and 4 until 8 shifts have been performed.  When this is done, a complete 8–bit byte will have been processed.
        }
    }

    return CRC;
}

/*******************************************************************************
 *   @fn         MB_CheckSlaveID
 *
 *   @brief      parameters
 *
 *
 *
 *   @param      none
 *
 *   @return     none
 */
uint8_t MB_CheckSlaveID(void){


    if(mb_rx.Buffer[0]==modbusSlaveId){
        return 1;
    }
    else {
        return 0;
    }

}

/*******************************************************************************
 *   @fn         MB_CreateVariable
 *
 *   @brief      parameters
 *
 *               typedef struct _mb_struct{
 *                  uint8_t         FunctCode;
 *                  uint8_t         Buffer[256];
 *               }modbus_t;
 *
 *
 *   @param      none
 *
 *   @return     none
 */

void MB_CreateVariable(modbus_t * Var){

    ERASE_BUFFER((Var->Buffer), 254);
    Var->FunctCode=0;

}


/*******************************************************************************
 *   @fn         MB_Transmit_Buffer
 *
 *   @brief      parameters
 *
 *
 *
 *   @param      none
 *
 *   @return     none
 */
void  MB_Transmit_Buffer(uint8_t * Buff,  uint8_t bsize){

    MODBUS_TX_Enable;
    if(Flg.Bits.MB_TX_Start && !Flg.Bits.MB_RX_Start){

        while (--bsize < 255)
           {
               while(!(UART_IFG & UART_TXIFG));

               UCA0TXBUF = *Buff;
               Buff++;

       //       EUSCI_A_UART_transmitData(UART_BASE, *Buff);

           }

           while ((UCA0STATW & UCBUSY));

           RX_Counter=0;

    }



}

/*******************************************************************************
 *   @fn         ERASE_BUFFER
 *
 *   @brief      parameters
 *
 *
 *
 *   @param      none
 *
 *   @return     none
 */
void ERASE_BUFFER(uint8_t * Buff, uint8_t bsize){

    while(--bsize < 255){
        *Buff='\0';
        Buff++;
    }

}

/*******************************************************************************
 *   @fn         SizeofArray
 *
 *   @brief      Uint8_t
 *
 *
 *
 *   @param      none
 *
 *   @return     none
 */
uint8_t SizeofArray(uint8_t * Buff){

    uint8_t bsize=0;
    int i;
    for(i=0; i<252; i++){

        if( (*Buff == '\0') && (*(Buff+1) == '\0') && (*(Buff+2) == '\0')  && (*(Buff+3) == '\0') )    {
            break;
        }else{

            bsize++;
            Buff++;

        }
    }

    return bsize;
//     else{
//        bsize=255;
//        return bsize;
//    }


}

