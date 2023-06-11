
#ifndef _CAN_DRIVER_H_
#define _CAN_DRIVER_H_

#include "ChinookLib.h"

void CAN_Init();
void CAN_EnableInterrupts();

void CAN_SendByte(UINT32 id, UINT8 data);
void CAN_SendFloat(UINT32 id, float data);
void CAN_SendInt(UINT32 id, INT32 data);
void CAN_SendUInt(UINT32 id, UINT32 data);

void CAN_SendData(UINT32 id, UINT8 data[4]);




#endif // _CAN_DRIVER_H_
