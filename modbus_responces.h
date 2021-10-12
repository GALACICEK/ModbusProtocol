/*
 * modbus_responces.h
 *
 *  Created on: 1 Eyl 2021
 *      Author: @GALACICEK
 */

#ifndef MODBUS_RESPONCES_H_
#define MODBUS_RESPONCES_H_

#include "modbusRTU.h"

//istenilen adreslere göre responce
extern  void    MB_Read_Responce(uint16_t startadress,uint16_t quantity);
extern  void    MB_Write_Responce(uint16_t regadress,uint16_t value);

#endif /* MODBUS_RESPONCES_H_ */
