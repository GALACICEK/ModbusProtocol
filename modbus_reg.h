/*
 * modbus_reg.h
 *
 *  Created on: 26 Aðu 2021
 *      Author: @GALACICEK
 *
 *      0x = Coil = 00001-09999
 *      1x = Discrete Input = 10001-19999
 *      3x = Input Register = 30001-39999
 *      4x = Holding Register = 40001-49999
 *
 */

#ifndef MODBUS_REG_H_
#define MODBUS_REG_H_

#define SPECIAL_REGISTER_START_ADD 0
#define BASE_DATA_START_ADD 1000U



//special register area
#define MB_ADDW_DEVICE_ID                   (SPECIAL_REGISTER_START_ADD + 10)   //
#define MB_ADDW_SERIAL_NUMBER               (SPECIAL_REGISTER_START_ADD + 11)
#define MB_ADDW_SOFTWARE_VERSION            (SPECIAL_REGISTER_START_ADD + 13)
#define MB_ADDW_HARDWARE_VERSION            (SPECIAL_REGISTER_START_ADD + 14)
#define MB_ADDW_BOOTLOADER_VERSION          (SPECIAL_REGISTER_START_ADD + 15)
#define MB_ADDW_FABRICATION_DATE            (SPECIAL_REGISTER_START_ADD + 16)
#define MB_ADDW_CALIBRATION_DATE            (SPECIAL_REGISTER_START_ADD + 18)

/*--------------------------USER REGISTERS----------------------------------*/

//read registers
#define MB_ADDR_REG_VAL0                        (BASE_DATA_START_ADD + 0)
#define MB_ADDR_REG_VAL1                        (BASE_DATA_START_ADD + 1)
#define MB_ADDR_REG_VAL2                        (BASE_DATA_START_ADD + 2)
#define MB_ADDR_REG_VAL3                        (BASE_DATA_START_ADD + 3)
#define MB_ADDR_REG_VAL4                        (BASE_DATA_START_ADD + 4)
#define MB_ADDR_REG_VAL5                        (BASE_DATA_START_ADD + 5)
#define MB_ADDR_REG_VAL6                        (BASE_DATA_START_ADD + 6)
#define MB_ADDR_REG_VAL7                        (BASE_DATA_START_ADD + 7)
#define MB_ADDR_REG_VAL8                        (BASE_DATA_START_ADD + 8)
#define MB_ADDR_REG_VAL9                        (BASE_DATA_START_ADD + 9)
#define MB_ADDR_REG_VAL10                       (BASE_DATA_START_ADD + 10)
#define MB_ADDR_REG_VAL11                       (BASE_DATA_START_ADD + 11)
#define MB_ADDR_REG_VAL12                       (BASE_DATA_START_ADD + 12)
#define MB_ADDR_REG_VAL13                       (BASE_DATA_START_ADD + 13)
#define MB_ADDR_REG_VAL14                       (BASE_DATA_START_ADD + 14)
#define MB_ADDR_REG_VAL15                       (BASE_DATA_START_ADD + 15)
#define MB_ADDR_REG_VAL16                       (BASE_DATA_START_ADD + 16)
#define MB_ADDR_REG_VAL17                       (BASE_DATA_START_ADD + 17)
#define MB_ADDR_REG_VAL18                       (BASE_DATA_START_ADD + 18)
#define MB_ADDR_REG_VAL19                       (BASE_DATA_START_ADD + 19)
#define MB_ADDR_REG_VAL20                       (BASE_DATA_START_ADD + 20)

#define MB_MAX_READ_REG                         (MB_ADDR_REG_VAL20-MB_ADDR_REG_VAL0)

//write registers
#define MB_ADDW_REG_VAL1                        (BASE_DATA_START_ADD + 21)
#define MB_ADDW_REG_VAL2                        (BASE_DATA_START_ADD + 22)
#define MB_ADDW_REG_VAL3                        (BASE_DATA_START_ADD + 23)
#define MB_ADDW_REG_VAL4                        (BASE_DATA_START_ADD + 24)
#define MB_ADDW_REG_VAL5                        (BASE_DATA_START_ADD + 25)
#define MB_ADDW_REG_VAL6                        (BASE_DATA_START_ADD + 26)
#define MB_ADDW_REG_VAL7                        (BASE_DATA_START_ADD + 27)
#define MB_ADDW_REG_VAL8                        (BASE_DATA_START_ADD + 28)
#define MB_ADDW_REG_VAL9                        (BASE_DATA_START_ADD + 29)
#define MB_ADDW_REG_VAL10                       (BASE_DATA_START_ADD + 30)
#define MB_ADDW_REG_VAL11                       (BASE_DATA_START_ADD + 31)
#define MB_ADDW_REG_VAL12                       (BASE_DATA_START_ADD + 32)
#define MB_ADDW_REG_VAL13                       (BASE_DATA_START_ADD + 33)
#define MB_ADDW_REG_VAL14                       (BASE_DATA_START_ADD + 34)
#define MB_ADDW_REG_VAL15                       (BASE_DATA_START_ADD + 35)
#define MB_ADDW_REG_VAL16                       (BASE_DATA_START_ADD + 36)
#define MB_ADDW_REG_VAL17                       (BASE_DATA_START_ADD + 37)
#define MB_ADDW_REG_VAL18                       (BASE_DATA_START_ADD + 38)
#define MB_ADDW_REG_VAL19                       (BASE_DATA_START_ADD + 39)
#define MB_ADDW_REG_VAL20                       (BASE_DATA_START_ADD + 40)

#define MB_MAX_WRITE_REG                        (MB_ADDW_REG_VAL20-MB_ADDW_REG_VAL1)

//read special Registers
#define MB_ADD_R_DEVICE_ID                       (BASE_DATA_START_ADD+ 3000 )
#define MB_ADD_R_SERIAL_NUMBER_BYTE1             (BASE_DATA_START_ADD+ 3001)
#define MB_ADD_R_SERIAL_NUMBER_BYTE2             (BASE_DATA_START_ADD+ 3002)
#define MB_ADD_R_SOFTWARE_VERSION_BYTE           (BASE_DATA_START_ADD+ 3003 )
#define MB_ADD_R_HARDWARE_VERSION_BYTE           (BASE_DATA_START_ADD+ 3004 )
#define MB_ADD_R_BOOTLOADER_VERSION_BYTE         (BASE_DATA_START_ADD+ 3005)
#define MB_ADD_R_MODBUS_TABLE_VERSION_BYTE       (BASE_DATA_START_ADD+ 3006)
#define MB_ADD_R_MEASUSREMENT_SYSTEM             (BASE_DATA_START_ADD+ 3007)
#define MB_ADD_R_FABRICATION_DATE_BYTE1          (BASE_DATA_START_ADD+ 3008)
#define MB_ADD_R_FABRICATION_DATE_BYTE2          (BASE_DATA_START_ADD+ 3009)
#define MB_ADD_R_CALIBRATION_DATE_BYTE1          (BASE_DATA_START_ADD+ 3010)
#define MB_ADD_R_CALIBRATION_DATE_BYTE2          (BASE_DATA_START_ADD+ 3011)



//Write Registers Start Addres
#define MB_ADD_RW_LANGUAGE_SELECTION            (BASE_DATA_START_ADD + 5000)
#define MB_ADD_RW_BACK_LIGHT_STATUS             (BASE_DATA_START_ADD + 5001)


#define MB_ADD_RW_RS485_ID                      (BASE_DATA_START_ADD + 5030)
#define MB_ADD_RW_RS485_BAUD                    (BASE_DATA_START_ADD + 5031)
#define MB_ADD_RW_RS485_STOP_BIT                (BASE_DATA_START_ADD + 5032)

#define MB_ADD_RW_RTC_TIME_STAMP                (BASE_DATA_START_ADD+ 5035) // uint32_t timestamp
#define MB_ADD_RW_DST_STATUS                    (BASE_DATA_START_ADD+ 5037) //
#define MB_ADD_RW_GMT_TIME_SELECTION            (BASE_DATA_START_ADD+ 5038)


#endif /* MODBUS_REG_H_ */
