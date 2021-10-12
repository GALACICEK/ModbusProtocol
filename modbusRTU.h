/*
 * modbusRTU.h
 *
 *  Created on: 26 Aðu 2021
 *      Author: @GALACICEK
 */

#ifndef MODBUSRTU_H_
#define MODBUSRTU_H_

#include "modbus_reg.h"

//Haberleþme half dublex olduðu için data alýrken gönderme yapmamasý adýna flg tanýmlanmýþtýr.




/*----------------------------------------------------------------*/
#define modbusSlaveId   01

//Gönderilecek Datalar
#define modbusdata0         0xAABB
#define modbusdata1         0xBBCC
#define modbusdata2         0xCCDD
#define modbusdata3         0xEEFF
#define modbusdata4         0x1234
#define modbusdata5         0x0AB0
#define modbusdata6         0x0A0B
#define modbusdata7         0x1CBA
#define modbusdata8         0xFACB
#define modbusdata9         0x0009
#define modbusdata10        0x0010
#define modbusdata11        0x0011
#define modbusdata12        0x1200
#define modbusdata13        0x1300
#define modbusdata14        0x1400
#define modbusdata15        0x0015
#define modbusdata16        0x0016
#define modbusdata17        0x0017
#define modbusdata18        0x1008
#define modbusdata19        0x1009
#define modbusdata20        0x2000


/*----------------------------------------------------------------*/

#define WRONG_SLAVE_ADDRESS     0XA0 // this value was chosen randomly. this is used only by this software, not real protocol value.
#define WRONG_CRC_VALUE         0XA1 // this value was chosen randomly. this is used only by this software, not real protocol value.
#define MODBUS_DATA_NOT_READY   0xA2 // this value was chosen randomly. this is used only by this software, not real protocol value.
#define MODBUS_DATA_READY       0xA3 // this value was chosen randomly. this is used only by this software, not real protocol value.

#define MAX_MODBUS_BUFFER_SIZE              256
#define MB_DELAY_TIME                       200

/*-----------------------MODBUS function codes-------------------------------*/

/*------bit access-----*/
//#define  Read_Coils                               0x01
//#define  Read_Discrete_Inputs                     0x02
//#define  Write_Single_Coil                        0x05
//#define  Write_Multiple_Coils                     0x0F

/*------16 bit access-----*/
#define  Read_Holding_Registers                   0x03
#define  Read_Input_Registers                     0x04
#define  Write_Single_Register                    0x06
#define  Write_Multiple_Registers                 0x10
#define  Mask_Write_Register                      0x16
#define  ReadWrite_Multiple_Registers             0x17
#define  Read_FIFO_Queue                          0x18

/*------File record access-----*/
//#define  Read_File_Record                         0x14
//#define  Write_File_Record                        0x15

/*---------Diagnostics--------*/
//#define  Read_Exception_Status                    0x07
//#define  Diagnostics                              0x08
//#define  Get_Comm_Event_Counter                   0x0B
//#define  Get_Comm_Event_Log                       0x0C
//#define  Report_Server_ID                         0x11
//#define  Read_Device_Identification               0x2B



//MODBUS except/error codes

#define MODBUS_ERROR_CODE_01    0x01    //ILLEGAL_FUNCTION Function code is not supported
#define MODBUS_ERROR_CODE_02    0x02    //ILLEGAL_DATA_ADDRESS Register address is not allowed or write-protected
#define MODBUS_ERROR_CODE_03    0x03    //ILLEGAL_DATA_VALUE Some data values are out of range, invalid number of register
#define MODBUS_ERROR_CODE_04    0x04    //SERVER_DEVICE_FAILURE An unrecoverable error occurred while the slave was attempting to perform the requested action.
#define MODBUS_ERROR_CODE_05    0x05    //ACKNOWLEDGE
#define MODBUS_ERROR_CODE_06    0x06    // SERVER_DEVICE_BUSY Device can not handle the request at the moment. Repeat the request.
#define MODBUS_ERROR_CODE_08    0x08    //MEMORY_PARITY_ERROR
#define MODBUS_ERROR_CODE_0A    0x0A    //GATEWAY_PATH_UNAVAILABLE
#define MODBUS_ERROR_CODE_0B    0x0B    //GATEWAY_TARGET_DEVICE_FAILED_TO_RESPOND

/*----------------------------------------------------------------*/


typedef struct _mb_struct{

    uint8_t         FunctCode;
    uint8_t         Buffer[MAX_MODBUS_BUFFER_SIZE];

}modbus_t;


extern modbus_t mb_rx, mb_tx;

/*----------------------------------------------------------------*/

extern  void        MB_CreateVariable(modbus_t * Var);
extern  uint8_t     MB_CheckSlaveID(void);

extern  void        MB_Init(void);
extern  void        MB_Request_Task(void);
extern  void        MB_Responce_Task(void);

extern  uint8_t     MB_Check_RXBuffer_Complete(void);
//16bit Data access Functions
//extern  void        ReadInput_RegisterHandler(void);
extern  void        ReadHolding_RegisterHandler(void);
extern  void        WriteSingle_RegisterHandler(void);
extern  void        WriteMultiple_RegisterHandler(void);
extern  void        ReadWriteMultiple_RegisterHandler(void);
extern  void        MaskWrite_RegisterHandler(void);



extern  void        MB_ErrorHandler(uint8_t errorCode);
extern  uint16_t    MB_CRC16(uint8_t * Buff,uint8_t bsize);
extern  void        MB_Transmit_Buffer(uint8_t * Buff,  uint8_t bsize);
extern  void        ERASE_BUFFER(uint8_t * Buff, uint8_t bsize);
extern uint8_t      SizeofArray(uint8_t * Buff);

#endif /* MODBUSRTU_H_ */
