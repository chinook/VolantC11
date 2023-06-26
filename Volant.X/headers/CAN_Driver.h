/*
 * CAN_Driver.h
 *
 *  Created on: June 11, 2023
 *      Author: Marc
 */

#ifndef _CAN_DRIVER_H_
#define _CAN_DRIVER_H_

/* ******************************* Includes ********************************* */

#include "ChinookLib.h"

/* ********************** Public function declarations ********************** */

/**
 * @brief     Initializes CAN
 * 
 * @details   CAN1 is initialized
*/
void CAN_Init();

/**
 * @brief     Enables CAN interrupts
 * 
 * @details   CAN1 interrupts are enabled
*/
void CAN_EnableInterrupts();

/**
 * @brief     Sends a byte on CAN
 * @param[in] id: CAN message ID
 * @param[in] data: byte to send
 * 
*/
void CAN_SendByte(UINT32 id, UINT8 data);

/**
 * @brief     Sends a float on CAN
 * @param[in] id: CAN message ID
 * @param[in] data: float to send
 * 
*/
void CAN_SendFloat(UINT32 id, float data);

/**
 * @brief     Sends an int on CAN
 * @param[in] id: CAN message ID
 * @param[in] data: int to send
 * 
 * @details   This function does not exist in the ChinookLib
*/
// void CAN_SendInt(UINT32 id, INT32 data);

/**
 * @brief     Sends an unsigned int on CAN
 * @param[in] id: CAN message ID
 * @param[in] data: unsigned int to send
 * 
 * @details   This function does not exist in the ChinookLib
*/
// void CAN_SendUInt(UINT32 id, UINT32 data);

/**
 * @brief     Sends a string on CAN
 * @param[in] id: CAN message ID
 * @param[in] data: string to send
 * 
*/
void CAN_SendData(UINT32 id, UINT64 data);




#endif // _CAN_DRIVER_H_
