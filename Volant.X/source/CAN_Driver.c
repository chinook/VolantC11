/*
 * CAN_Driver.c
 *
 *  Created on: June 11, 2023
 *      Author: Marc
 */

/* ******************************* Includes ********************************* */

#include "CAN_Driver.h"
#include "main.h"

/* ************************** Private definitions *************************** */

#define CAN_NB_CHANNELS    17
#define CAN_BUFFER_SIZE    8

#define CAN1_INTERRUPT_PRIORITY          4
#define CAN1_INTERRUPT_SUBPRIORITY       3

/* ********************* Private variable declarations ********************** */

INT8 Can1MessageFifoArea[CAN_NB_CHANNELS * CAN_BUFFER_SIZE * 
                                                  CAN_TX_RX_MESSAGE_SIZE_BYTES];

/* ********************* Private function declarations ********************** */

UINT8 CAN_CheckChannel(UINT32 channel, UINT32 channel_event, UINT32* data);

/* *********************** Public function definitions ********************** */

/**
 * @brief     Initializes CAN
 * 
 * @details   CAN1 is initialized
*/
void CAN_Init()
{
  Can.Initialize(CAN1, Can1MessageFifoArea, CAN_NB_CHANNELS, CAN_BUFFER_SIZE, 
                                                                         FALSE);

  // CAN1 Interrupt
  Can.ConfigInterrupt(CAN1, CAN1_INTERRUPT_PRIORITY, CAN1_INTERRUPT_SUBPRIORITY);
}

/**
 * @brief     Enables CAN interrupts
 * 
 * @details   CAN1 interrupts are enabled
*/
void CAN_EnableInterrupts()
{
  Can.EnableInterrupt(CAN1);
}

/**
 * @brief     Sends a byte on CAN
 * @param[in] id: CAN message ID
 * @param[in] data: byte to send
 * 
*/
void CAN_SendByte(UINT32 id, UINT8 data)
{
  Can.SendByte(CAN1, id, data);
}

/**
 * @brief     Sends a float on CAN
 * @param[in] id: CAN message ID
 * @param[in] data: float to send
 * 
*/
void CAN_SendFloat(UINT32 id, float data)
{
  Can.SendFloat(CAN1, id, data);
}

/**
 * @brief     Sends an int on CAN
 * @param[in] id: CAN message ID
 * @param[in] data: int to send
 * 
 * @details   This function does not exist in the ChinookLib
*/
/* void CAN_SendInt(UINT32 id, INT32 data)
{
  Can.SendInt(CAN1, id, data);
} */

/**
 * @brief     Sends an unsigned int on CAN
 * @param[in] id: CAN message ID
 * @param[in] data: unsigned int to send
 * 
 * @details   This function does not exist in the ChinookLib
*/
/* void CAN_SendUInt(UINT32 id, UINT32 data)
{
  Can.SendUInt(CAN1, id, data);
} */

/**
 * @brief     Sends a string on CAN
 * @param[in] id: CAN message ID
 * @param[in] data: string to send
 * 
*/
void CAN_SendData(UINT32 id, UINT8 data[4])
{
  // TODO
}


/* ********************** Private function definitions ********************** */

/**
 * @brief     Checks if a CAN channel has received a message
 * @param[in] channel: CAN channel to check
 * @param[in] channel_event: CAN event to check
 * @param[out] data: data received
 * @return    1 if a message has been received, 0 otherwise
 * 
*/
UINT8 CAN_CheckChannel(UINT32 channel, UINT32 channel_event, UINT32* data)
{
  if (CANGetPendingEventCode(CAN1) == channel_event)
  {
    CANEnableChannelEvent(CAN1, channel, CAN_RX_CHANNEL_NOT_EMPTY, FALSE);
    CAN_RX_MSG_SID sid;
    CANRxMessageBuffer* message;
    message = CANGetRxMessage(CAN1, channel);

    // flags.flag_can = 1;

    // Ecrire le data
    *data = *((UINT32*)(&message->data[0]));
    *(data+1) = *((UINT32*)(&message->data[4]));

    CANUpdateChannel(CAN1, channel);
    CANEnableChannelEvent(CAN1, channel, CAN_RX_CHANNEL_NOT_EMPTY, TRUE);

    return 1;
  }
  return 0;
}

/* ************************ Interrupts definitions ************************** */

/**
 * @brief     CAN1 Interrupt Handler
 * 
 * @details   Handles CAN1 interrupts
*/
void __attribute__((vector(_CAN_1_VECTOR), interrupt(ipl4auto), nomips16)) 
                                                      CAN1InterruptHandler(void)
{
  if ((CANGetModuleEvent(CAN1) & CAN_RX_EVENT) != 0)
  {
    UINT32 data[2];

    if (CAN_CheckChannel(CAN_CHANNEL1, CAN_CHANNEL1_EVENT, data))
      sensor_data.gear = (UINT8)data;

    if (CAN_CheckChannel(CAN_CHANNEL2, CAN_CHANNEL2_EVENT, data))
      memcpy((void*)(&sensor_data.pitch), &data, 4);

    if (CAN_CheckChannel(CAN_CHANNEL3, CAN_CHANNEL3_EVENT, data))
      memcpy((void*)(&sensor_data.mast_direction), &data, 4);

    //if (CAN_CheckChannel(CAN_CHANNEL4, CAN_CHANNEL4_EVENT, &data))
      // sensor_data.mast_mode = (message->data[1] << 8) | message->data[0];

    if (CAN_CheckChannel(CAN_CHANNEL5, CAN_CHANNEL5_EVENT, data))
      memcpy((void*)(&sensor_data.pitch_algo), &data, 4);

    if (CAN_CheckChannel(CAN_CHANNEL6, CAN_CHANNEL6_EVENT, data))
      memcpy((void*)(&sensor_data.turbine_rpm), &data, 4);

    if (CAN_CheckChannel(CAN_CHANNEL7, CAN_CHANNEL7_EVENT, data))
      memcpy((void*)(&sensor_data.wind_speed), &data, 4);

    if (CAN_CheckChannel(CAN_CHANNEL8, CAN_CHANNEL8_EVENT, data))
      memcpy((void*)(&sensor_data.backplane_current), &data, 4);

    if (CAN_CheckChannel(CAN_CHANNEL9, CAN_CHANNEL9_EVENT, data))
      memcpy((void*)(&sensor_data.backplane_voltage), &data, 4);

    if (CAN_CheckChannel(CAN_CHANNEL10, CAN_CHANNEL10_EVENT, data))
      memcpy((void*)(&sensor_data.wheel_rpm), &data, 4);

    if (CAN_CheckChannel(CAN_CHANNEL11, CAN_CHANNEL11_EVENT, data))
      memcpy((void*)(&sensor_data.wind_direction), &data, 4);

    if (CAN_CheckChannel(CAN_CHANNEL14, CAN_CHANNEL14_EVENT, data))
      memcpy((void*)(&sensor_data.loadcell), &data, 4);

    if (CAN_CheckChannel(CAN_CHANNEL15, CAN_CHANNEL15_EVENT, data))
      memcpy((void*)(&sensor_data.torque), &data, 4);

    if (CAN_CheckChannel(CAN_CHANNEL16, CAN_CHANNEL16_EVENT, data))
    {
      // TODO: ROPS
    }

    if (CAN_CheckChannel(CAN_CHANNEL17, CAN_CHANNEL17_EVENT, data))
      memcpy((void*)(&sensor_data.pitch_mode), &data, 4);
  }

  // The CAN1 Interrupt flag is  cleared at the end of the interrupt routine.
  // This is because the event source that could have caused this interrupt to
  // occur (CAN_RX_CHANNEL_NOT_EMPTY) is disabled. Attempting to clear the
  // CAN1 interrupt flag when the the CAN_RX_CHANNEL_NOT_EMPTY interrupt is
  // enabled will not have any effect because the base event is still present.
  INTClearFlag(INT_CAN1);
}
