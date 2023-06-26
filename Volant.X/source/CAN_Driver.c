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

//#define CAN1_INTERRUPT_PRIORITY          4
//#define CAN1_INTERRUPT_SUBPRIORITY       3

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
  
  
  // Channel 1 - 0x23 would be the GEAR feeback value from a drive board
   Can.SetChannel(CAN1, CAN_CHANNEL1, 8, RX);
   //Can.SetChannelMask(CAN1, CAN_CHANNEL1, CAN_FILTER0, 0x23, CAN_FILTER_MASK0,0x7FF);
   Can.SetChannelMask(CAN1, CAN_CHANNEL1, CAN_FILTER0, 0x1, CAN_FILTER_MASK0,0x7FF);
   
   // Channel 2 - 0x13 would be the PITCH feeback value from a drive board
   Can.SetChannel(CAN1, CAN_CHANNEL2, 8, RX);
   //Can.SetChannelMask(CAN1, CAN_CHANNEL2, CAN_FILTER1, 0x13, CAN_FILTER_MASK0,0x7FF);
   Can.SetChannelMask(CAN1, CAN_CHANNEL2, CAN_FILTER1, 0x2, CAN_FILTER_MASK0,0x7FF);
   
   // Channel 3 - Mast Dir
   Can.SetChannel(CAN1, CAN_CHANNEL3, 8, RX);
   //Can.SetChannelMask(CAN1, CAN_CHANNEL3, CAN_FILTER2, 0x52, CAN_FILTER_MASK0,0x7FF);
   Can.SetChannelMask(CAN1, CAN_CHANNEL3, CAN_FILTER2, 0x3, CAN_FILTER_MASK0,0x7FF);
   
   // Channel 4 - 0x33 would be the MAST AUTO/MANUAL MODE feeback value from a MAST-drive board
   Can.SetChannel(CAN1, CAN_CHANNEL4, 8, RX);
   Can.SetChannelMask(CAN1, CAN_CHANNEL4, CAN_FILTER3, 0x55, CAN_FILTER_MASK0,0x7FF);
   //Can.SetChannelMask(CAN1, CAN_CHANNEL4, CAN_FILTER3, 0x4, CAN_FILTER_MASK0,0x7FF);
   
   // Channel 5 - Pitch Algo CAN
   Can.SetChannel(CAN1, CAN_CHANNEL5, 8, RX);
   Can.SetChannelMask(CAN1, CAN_CHANNEL5, CAN_FILTER4, 0x4, CAN_FILTER_MASK0,0x7FF);
   //Can.SetChannelMask(CAN1, CAN_CHANNEL5, CAN_FILTER4, 0x5, CAN_FILTER_MASK0,0x7FF);
   
   // Channel 6 - 0x21 would be the Wind Turbine RPM value from sensor board
   Can.SetChannel(CAN1, CAN_CHANNEL6, 8, RX);
   //Can.SetChannelMask(CAN1, CAN_CHANNEL6, CAN_FILTER5, 0x21, CAN_FILTER_MASK0,0x7FF);
   Can.SetChannelMask(CAN1, CAN_CHANNEL6, CAN_FILTER5, 0x43, CAN_FILTER_MASK0,0x7FF);
   
    // Channel 7 - 0x19 would be the Wind speed value from sensor board
   Can.SetChannel(CAN1, CAN_CHANNEL7, 8, RX);
   //Can.SetChannelMask(CAN1, CAN_CHANNEL7, CAN_FILTER6, 0x19, CAN_FILTER_MASK0,0x7FF);
   Can.SetChannelMask(CAN1, CAN_CHANNEL7, CAN_FILTER6, 0x46, CAN_FILTER_MASK0,0x7FF);
   
    // Channel 8 - 0x73 would be the Amp(I) value from the BackPlane
   Can.SetChannel(CAN1, CAN_CHANNEL8, 8, RX);
   //Can.SetChannelMask(CAN1, CAN_CHANNEL8, CAN_FILTER7, 0x73, CAN_FILTER_MASK0,0x7FF);
   Can.SetChannelMask(CAN1, CAN_CHANNEL8, CAN_FILTER7, 0x4B, CAN_FILTER_MASK0,0x7FF);
   
   // Channel 9 - 0x72 would be the Voltage value from the BackPlane
   Can.SetChannel(CAN1, CAN_CHANNEL9, 8, RX);
   //Can.SetChannelMask(CAN1, CAN_CHANNEL9, CAN_FILTER8, 0x72, CAN_FILTER_MASK0,0x7FF);
   Can.SetChannelMask(CAN1, CAN_CHANNEL9, CAN_FILTER8, 0x4A, CAN_FILTER_MASK0,0x7FF);
   
   // Channel 10 - 0x22 would be wheel RPM
   Can.SetChannel(CAN1, CAN_CHANNEL10, 8, RX);
   //Can.SetChannelMask(CAN1, CAN_CHANNEL10, CAN_FILTER9, 0x22, CAN_FILTER_MASK0,0x7FF);
   Can.SetChannelMask(CAN1, CAN_CHANNEL10, CAN_FILTER9, 0x44, CAN_FILTER_MASK0,0x7FF);
   
   // Channel 11 - Wind Dir
   Can.SetChannel(CAN1, CAN_CHANNEL11, 8, RX);
   Can.SetChannelMask(CAN1, CAN_CHANNEL11, CAN_FILTER10, 0x45, CAN_FILTER_MASK0, 0x7FF);
   
   // Loadcell
   Can.SetChannel(CAN1, CAN_CHANNEL14, 8, RX);
   Can.SetChannelMask(CAN1, CAN_CHANNEL14, CAN_FILTER11, 0x48, CAN_FILTER_MASK0, 0x7FF);
   
   // Torque
   Can.SetChannel(CAN1, CAN_CHANNEL15, 8, RX);
   Can.SetChannelMask(CAN1, CAN_CHANNEL15, CAN_FILTER12, 0x47, CAN_FILTER_MASK0, 0x7FF);
   
   // ROPS cmd = 0x37 from Senstel
   Can.SetChannel(CAN1, CAN_CHANNEL16, 8, RX);
   Can.SetChannelMask(CAN1, CAN_CHANNEL16, CAN_FILTER13, 0x37, CAN_FILTER_MASK0, 0x7FF);
   
   // Pitch mode feedback
   Can.SetChannel(CAN1, CAN_CHANNEL17, 8, RX);
   Can.SetChannelMask(CAN1, CAN_CHANNEL17, CAN_FILTER14, 0x4C, CAN_FILTER_MASK0, 0x7FF);
  
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
void CAN_SendInt(UINT32 id, INT32 data)
{
  Can.SendData(CAN1, id, (UINT64)data);
}

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
void CAN_SendData(UINT32 id, UINT64 data)
{
  Can.SendData(CAN1, id, data);
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
/*
void __attribute__((vector(_CAN_1_VECTOR), interrupt(ipl4auto), nomips16)) 
                                                      CAN1InterruptHandler(void)
{
  if ((CANGetModuleEvent(CAN1) & CAN_RX_EVENT) != 0)
  {
    UINT32 data[2];

    if (CAN_CheckChannel(CAN_CHANNEL1, CAN_CHANNEL1_EVENT, data))
      sensor_data.gear = (INT8)data;

    if (CAN_CheckChannel(CAN_CHANNEL2, CAN_CHANNEL2_EVENT, data))
      memcpy((void*)(&sensor_data.pitch), &data, 4);

    if (CAN_CheckChannel(CAN_CHANNEL3, CAN_CHANNEL3_EVENT, data))
      memcpy((void*)(&sensor_data.mast_dir), &data, 4);

    if (CAN_CheckChannel(CAN_CHANNEL4, CAN_CHANNEL4_EVENT, data))
       sensor_data.mast_mode = 0;//(message->data[1] << 8) | message->data[0];

    if (CAN_CheckChannel(CAN_CHANNEL5, CAN_CHANNEL5_EVENT, data))
      memcpy((void*)(&sensor_data.pitch_algo), &data, 4);

    if (CAN_CheckChannel(CAN_CHANNEL6, CAN_CHANNEL6_EVENT, data))
      memcpy((void*)(&sensor_data.wind_turbine_rpm), &data, 4);

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
*/

//================================================
// Configure the CAN1 interrupt handler
//================================================
void __attribute__((vector(_CAN_1_VECTOR), interrupt(ipl4auto), nomips16)) CAN1InterruptHandler(void)
{
  
    // Check if the source of the interrupt is RX_EVENT. This is redundant since
    // only this event is enabled in this example but this shows one scheme for
    // handling events
    if ((CANGetModuleEvent(CAN1) & CAN_RX_EVENT) != 0) {

        // Within this, you can check which channel caused the event by using
        // the CANGetModuleEvent() function which returns a code representing
        // the highest priority pending event.
        if (CANGetPendingEventCode(CAN1) == CAN_CHANNEL1_EVENT) {
            

            // This means that channel 1 caused the event.
            // The CAN_RX_CHANNEL_NOT_EMPTY event is persistent. You could either
            // read the channel in the ISR to clear the event condition or as done
            // here, disable the event source, and set an application flag to
            // indicate that a message has been received. The event can be
            // enabled by the application when it has processed one message.
            // Note that leaving the event enabled would cause the CPU to keep
            // executing the ISR since the CAN_RX_CHANNEL_NOT_EMPTY event is
            // persistent (unless the not empty condition is cleared.)

            CANEnableChannelEvent(CAN1, CAN_CHANNEL1, CAN_RX_CHANNEL_NOT_EMPTY, FALSE);
            CAN_RX_MSG_SID Sid;
            CANRxMessageBuffer *message;
            message = CANGetRxMessage(CAN1,CAN_CHANNEL1);

            flag_can = 1;
             
            // CAN_Gear = message->data[0];
            //Sid = message->msgSID;
            
            CANUpdateChannel(CAN1, CAN_CHANNEL1);
            CANEnableChannelEvent(CAN1, CAN_CHANNEL1, CAN_RX_CHANNEL_NOT_EMPTY, TRUE);
        }
        
        if (CANGetPendingEventCode(CAN1) == CAN_CHANNEL2_EVENT) 
        {
            
            CANEnableChannelEvent(CAN1, CAN_CHANNEL2, CAN_RX_CHANNEL_NOT_EMPTY, FALSE);
            CAN_RX_MSG_SID Sid;
            CANRxMessageBuffer *message;
            message = CANGetRxMessage(CAN1,CAN_CHANNEL2);
            
            flag_can = 1;
             
            
            memcpy((void *) &sensor_data.pitch, &message->data[0], 4);
            //CAN_Pitch = (message->data[1] << 8) | message->data[0];
           
            CANUpdateChannel(CAN1, CAN_CHANNEL2);
            CANEnableChannelEvent(CAN1, CAN_CHANNEL2, CAN_RX_CHANNEL_NOT_EMPTY, TRUE);


        }
        
        if (CANGetPendingEventCode(CAN1) == CAN_CHANNEL3_EVENT) 
        {
            
            CANEnableChannelEvent(CAN1, CAN_CHANNEL3, CAN_RX_CHANNEL_NOT_EMPTY, FALSE);
            CAN_RX_MSG_SID Sid;
            CANRxMessageBuffer *message;
            message = CANGetRxMessage(CAN1,CAN_CHANNEL3);
            
            flag_can = 1;
             
            // memcpy((void *) &CAN_MastDir, &message->data[0], 4);
            //memcpy();
           
            CANUpdateChannel(CAN1, CAN_CHANNEL3);
            CANEnableChannelEvent(CAN1, CAN_CHANNEL3, CAN_RX_CHANNEL_NOT_EMPTY, TRUE);
        }
        
        if (CANGetPendingEventCode(CAN1) == CAN_CHANNEL4_EVENT) 
        {
            
            CANEnableChannelEvent(CAN1, CAN_CHANNEL4, CAN_RX_CHANNEL_NOT_EMPTY, FALSE);
            CAN_RX_MSG_SID Sid;
            CANRxMessageBuffer *message;
            message = CANGetRxMessage(CAN1,CAN_CHANNEL4);
            
            flag_can = 1;
             
            // CAN_MastMode = (message->data[1] << 8) | message->data[0];
            
            // 1 = manual mode and 0 = auto mode
            
           
            CANUpdateChannel(CAN1, CAN_CHANNEL4);
            CANEnableChannelEvent(CAN1, CAN_CHANNEL4, CAN_RX_CHANNEL_NOT_EMPTY, TRUE);
        }
        
        if (CANGetPendingEventCode(CAN1) == CAN_CHANNEL5_EVENT) 
        {
            
            CANEnableChannelEvent(CAN1, CAN_CHANNEL5, CAN_RX_CHANNEL_NOT_EMPTY, FALSE);
            CAN_RX_MSG_SID Sid;
            CANRxMessageBuffer *message;
            message = CANGetRxMessage(CAN1,CAN_CHANNEL5);
            
            flag_can = 1;
             
            //CAN_MastCalib = (message->data[1] << 8) | message->data[0];
            memcpy((void*)&sensor_data.gear, &message->data[0], 4);
           
            CANUpdateChannel(CAN1, CAN_CHANNEL5);
            CANEnableChannelEvent(CAN1, CAN_CHANNEL5, CAN_RX_CHANNEL_NOT_EMPTY, TRUE);


        }
        
        if (CANGetPendingEventCode(CAN1) == CAN_CHANNEL6_EVENT) 
        {
            
            CANEnableChannelEvent(CAN1, CAN_CHANNEL6, CAN_RX_CHANNEL_NOT_EMPTY, FALSE);
            CAN_RX_MSG_SID Sid;
            CANRxMessageBuffer *message;
            message = CANGetRxMessage(CAN1,CAN_CHANNEL6);
            
            flag_can = 1;
            
            
            memcpy((void *) &sensor_data.wind_turbine_rpm, &message->data[0], 4);

           
            CANUpdateChannel(CAN1, CAN_CHANNEL6);
            CANEnableChannelEvent(CAN1, CAN_CHANNEL6, CAN_RX_CHANNEL_NOT_EMPTY, TRUE);

        }
        
        if (CANGetPendingEventCode(CAN1) == CAN_CHANNEL7_EVENT) 
        {
            
            CANEnableChannelEvent(CAN1, CAN_CHANNEL7, CAN_RX_CHANNEL_NOT_EMPTY, FALSE);
            CAN_RX_MSG_SID Sid;
            CANRxMessageBuffer *message;
            message = CANGetRxMessage(CAN1,CAN_CHANNEL7);
            
              
            
            flag_can = 1;
            
            
            memcpy((void *) &sensor_data.wind_speed, &message->data[0], 4);
            
               
           
            CANUpdateChannel(CAN1, CAN_CHANNEL7);
            CANEnableChannelEvent(CAN1, CAN_CHANNEL7, CAN_RX_CHANNEL_NOT_EMPTY, TRUE);


        }
        
        if (CANGetPendingEventCode(CAN1) == CAN_CHANNEL8_EVENT) 
        {
            
            CANEnableChannelEvent(CAN1, CAN_CHANNEL8, CAN_RX_CHANNEL_NOT_EMPTY, FALSE);
            CAN_RX_MSG_SID Sid;
            CANRxMessageBuffer *message;
            message = CANGetRxMessage(CAN1,CAN_CHANNEL8);
            
              
            
            flag_can = 1;
            
            
            memcpy((void *) &sensor_data.backplane_current, &message->data[0], 4);
            
               
           
            CANUpdateChannel(CAN1, CAN_CHANNEL8);
            CANEnableChannelEvent(CAN1, CAN_CHANNEL8, CAN_RX_CHANNEL_NOT_EMPTY, TRUE);


        }
        
         if (CANGetPendingEventCode(CAN1) == CAN_CHANNEL9_EVENT) 
        {
            
            CANEnableChannelEvent(CAN1, CAN_CHANNEL9, CAN_RX_CHANNEL_NOT_EMPTY, FALSE);
            CAN_RX_MSG_SID Sid;
            CANRxMessageBuffer *message;
            message = CANGetRxMessage(CAN1,CAN_CHANNEL9);
            
              
            
            flag_can = 1;
            
            
            memcpy((void *) &sensor_data.backplane_voltage, &message->data[0], 4);
            
               
           
            CANUpdateChannel(CAN1, CAN_CHANNEL9);
            CANEnableChannelEvent(CAN1, CAN_CHANNEL9, CAN_RX_CHANNEL_NOT_EMPTY, TRUE);


        }
        
        if (CANGetPendingEventCode(CAN1) == CAN_CHANNEL10_EVENT) 
        {
            
            CANEnableChannelEvent(CAN1, CAN_CHANNEL10, CAN_RX_CHANNEL_NOT_EMPTY, FALSE);
            CAN_RX_MSG_SID Sid;
            CANRxMessageBuffer *message;
            message = CANGetRxMessage(CAN1,CAN_CHANNEL10);
            
              
            
            flag_can = 1;
            
            
            memcpy((void *) &sensor_data.wheel_rpm, &message->data[0], 4);
            
               
           
            CANUpdateChannel(CAN1, CAN_CHANNEL10);
            CANEnableChannelEvent(CAN1, CAN_CHANNEL10, CAN_RX_CHANNEL_NOT_EMPTY, TRUE);


        }
        if (CANGetPendingEventCode(CAN1) == CAN_CHANNEL11_EVENT) 
        {
            
            CANEnableChannelEvent(CAN1, CAN_CHANNEL11, CAN_RX_CHANNEL_NOT_EMPTY, FALSE);
            CAN_RX_MSG_SID Sid;
            CANRxMessageBuffer *message;
            message = CANGetRxMessage(CAN1,CAN_CHANNEL11);
            
              
            
            flag_can = 1;
            
            
            memcpy((void *) &sensor_data.wind_direction, &message->data[0], 4);
            
               
           
            CANUpdateChannel(CAN1, CAN_CHANNEL11);
            CANEnableChannelEvent(CAN1, CAN_CHANNEL11, CAN_RX_CHANNEL_NOT_EMPTY, TRUE);


        }
        if (CANGetPendingEventCode(CAN1) == CAN_CHANNEL14_EVENT) 
        {
            
            CANEnableChannelEvent(CAN1, CAN_CHANNEL14, CAN_RX_CHANNEL_NOT_EMPTY, FALSE);
            CAN_RX_MSG_SID Sid;
            CANRxMessageBuffer *message;
            message = CANGetRxMessage(CAN1,CAN_CHANNEL14);
            
              
            
            flag_can = 1;
            
            
            memcpy((void *) &sensor_data.loadcell, &message->data[0], 4);
            
               
           
            CANUpdateChannel(CAN1, CAN_CHANNEL14);
            CANEnableChannelEvent(CAN1, CAN_CHANNEL14, CAN_RX_CHANNEL_NOT_EMPTY, TRUE);


        }
        if (CANGetPendingEventCode(CAN1) == CAN_CHANNEL15_EVENT) 
        {
            
            CANEnableChannelEvent(CAN1, CAN_CHANNEL15, CAN_RX_CHANNEL_NOT_EMPTY, FALSE);
            CAN_RX_MSG_SID Sid;
            CANRxMessageBuffer *message;
            message = CANGetRxMessage(CAN1,CAN_CHANNEL15);
            
            flag_can = 1;
            
            memcpy((void *) &sensor_data.torque, &message->data[0], 4);
            
            CANUpdateChannel(CAN1, CAN_CHANNEL15);
            CANEnableChannelEvent(CAN1, CAN_CHANNEL15, CAN_RX_CHANNEL_NOT_EMPTY, TRUE);
        }
        if (CANGetPendingEventCode(CAN1) == CAN_CHANNEL16_EVENT) 
        {
            
            CANEnableChannelEvent(CAN1, CAN_CHANNEL16, CAN_RX_CHANNEL_NOT_EMPTY, FALSE);
            CAN_RX_MSG_SID Sid;
            CANRxMessageBuffer *message;
            message = CANGetRxMessage(CAN1,CAN_CHANNEL16);
            
            flag_can = 1;
            
            struct
            {
              int brops;
              float drapeau_steps;
            } ROPS_data;
            memcpy((void *) &ROPS_data, &message->data[0], 8);
            //if(ROPS_data.brops)
            //    bROPS = 1;
            //else
            //    bROPS = 0;
            
            CANUpdateChannel(CAN1, CAN_CHANNEL16);
            CANEnableChannelEvent(CAN1, CAN_CHANNEL16, CAN_RX_CHANNEL_NOT_EMPTY, TRUE);
        }
        if (CANGetPendingEventCode(CAN1) == CAN_CHANNEL17_EVENT) 
        {
            
            CANEnableChannelEvent(CAN1, CAN_CHANNEL17, CAN_RX_CHANNEL_NOT_EMPTY, FALSE);
            CAN_RX_MSG_SID Sid;
            CANRxMessageBuffer *message;
            message = CANGetRxMessage(CAN1,CAN_CHANNEL17);
            
            flag_can = 1;
            memcpy((void *) &sensor_data.pitch_mode, &message->data[0], 4);
            
            CANUpdateChannel(CAN1, CAN_CHANNEL17);
            CANEnableChannelEvent(CAN1, CAN_CHANNEL17, CAN_RX_CHANNEL_NOT_EMPTY, TRUE);
        }
    }
    

    // The CAN1 Interrupt flag is  cleared at the end of the interrupt routine.
    // This is because the event source that could have caused this interrupt to
    // occur (CAN_RX_CHANNEL_NOT_EMPTY) is disabled. Attempting to clear the
    // CAN1 interrupt flag when the the CAN_RX_CHANNEL_NOT_EMPTY interrupt is
    // enabled will not have any effect because the base event is still present.
    INTClearFlag(INT_CAN1);
}