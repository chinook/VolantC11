/*
 * main.c
 *
 *  Created on: June 11, 2023
 *      Author: Marc
 */

/* ******************************* Includes ********************************* */

#include "ChinookLib.h"

#include "main.h"
#include "Peripherals.h"
#include "CAN_Driver.h"
#include "Display.h"

/* ********************* Private function declarations ********************** */

UINT8 CheckSwitches();
UINT8 CheckSwitch(UINT32 sw);
UINT8 CheckSwitchPressedOnce(UINT32 sw);
void ProcessSwitches();

void EnableInterrupts();

void state_machine_exec();

void state_init();
void state_standby();
void state_acq();

/* ************************** Private definitions *************************** */

// Struct of switches so that we can refer to them in chronological order 
// (1,2,3...) instead of by their name (RE1, RE3, RE7...)
typedef struct SWITCH_DECL_
{
  UINT16 ports[12];   // Ports of switches
  UINT16 bits[12];    // Bits of switches (status)
}
SWITCH_DECL;

SWITCH_DECL switches =
{
 // Array for the ports
 {
  IOPORT_E,
  IOPORT_E,
  IOPORT_E,
  IOPORT_D,
  IOPORT_D,
  IOPORT_E,
  IOPORT_D,
  IOPORT_D,
  IOPORT_D,
  IOPORT_D,
  IOPORT_D,
  IOPORT_D,
 },
 // Array for the bits
 {
  BIT_0,
  BIT_1,
  BIT_3,
  BIT_7,
  BIT_6,
  BIT_2,
  BIT_11,
  BIT_9,
  BIT_8,
  BIT_10,
  BIT_4,
  BIT_5,
 }
};

// Array to convert switch number (1,2,3...) to switch name (PORTXbits.RXx...)
UINT32 swi_to_sw[12] =
{
 SW1, SW2, SW3, SW4, SW5, SW6, SW7, SW8, SW9, SW10, SW11, SW12                  // Error element not constant ???
};

/* ********************* Private variable declarations ********************** */

// States of the state machine
enum STATES
{
 STATE_INIT,
 STATE_STANDBY,
 STATE_ACQ,

 // Number of states
 NUM_STATES
};

// State machine variable
UINT32 state_machine_val;

// Switches memory (last status)
UINT8 mem_switches[12];

/* ********************** Private function definitions ********************** */


/**
 * @brief      Check if switches have been pressed, like a scanning radar
 * @return     1 if any switches has been pressed, 0 otherwise
 * 
 * @details    This function will loop through all switches and check if their
 *             status has changed since the last time we read it. If it has, it
 *             means the switch has been pressed. Used in the state machine to
 *             check if a switch has been pressed. Does not return which switch
 *             has been pressed.
 * 
 * @details    The status of the switches in PORTXbits.RXx are inverted 
 *             (0 = pressed, 1 = not pressed)
*/
UINT8 CheckSwitches()
{
  UINT8 sw_changed;				// Flag to indicate if a switch has been pressed
  int i;                  // Loop counter

  // Loop through all switches
  for (i = 0; i < 12; ++i)
  {
		// Read switch status
    UINT8 sw_status = PORTReadBits(switches.ports[i], switches.bits[i]);

		// If sw_status is different from the last time we read it, it means the 
    // switch has been pressed
    if (sw_status != mem_switches[i])
    {
			// Store last switch status
      mem_switches[i] = sw_status;

			// If the switch is pressed, set the flag
      sw_changed = 1;
    }
  }

	// Return the flag
  return sw_changed;
}

/**
 * @brief      Check status of a specific switch at a specific instant
 * @param[in]  sw    Switch to check
 * @return     1 if the switch is pressed, 0 otherwise
 * @note       If press & hold, the following function will be executed 
 *             indefinitely.
 * 
 * @details    sw starts at 1. Will be converted to 0 in the function.
 *             This function will check the status of a specific switch at a 
 *             specific instant. Does not determine if the switch has been
 *             pressed or not (no memory of last state).
 * 
 * @details    The status of the switches in PORTXbits.RXx are inverted 
 *             (0 = pressed, 1 = not pressed)
*/
UINT8 CheckSwitch(UINT32 sw)
{
  // If status of switch in swi_to_sw is 0, it means the switch is pressed
  if (swi_to_sw[sw - 1] != 1)
  {
    // Return 1 when the switch is pressed
    return 1;
  }

  // Return 0 when the switch is not pressed
  return 0;
}

/**
 * @brief      Check if a switch has been pressed once, compared to last state
 * @param[in]  sw    Switch to check
 * @return     1 if the switch has been pressed once (compared to last state), 
 *             0 otherwise
 * @note       If press & hold, the following function will be executed only
 *             once.
 * 
 * @details    sw starts at 1. Will be converted to 0 in the function.
 *             This function will check if a switch has been pressed once by 
 *             comparing its status to the last time we read it. If it has, it
 *             means the switch has been pressed once.
 * 
 * @details    The status of the switches in PORTXbits.RXx are inverted 
 *             (0 = pressed, 1 = not pressed)
*/
UINT8 CheckSwitchPressedOnce(UINT32 sw)
{
  // If status of switch in swi_to_sw is 0 AND compared to last state
  // aka If switch has been pressed once
  if (swi_to_sw[sw - 1] != 1 && mem_switches[sw])
  {
    int i;  // Loop counter
    // Wait a delay to make sure switch has settled
    for(i = 0; i < 1000; ++i);

    // Store the new state of the switch
    mem_switches[sw] = 1;

    // Return 1 because switch has been pressed once
    return 1;
  }
  // Else, if status of switch in swi_to_sw is 1 AND compared to last state
  // aka If switch has been released once
  else if (swi_to_sw[sw - 1] == 1 && mem_switches[sw])
  {
    // Reset the state of the switch
    mem_switches[sw] = 0;
  }
  // Then return 0 because switch has not been pressed once
  return 0;
}

/**
 * @brief      Process switches pressed to functions
 * 
 * @details    SW5:   Change display 1 mode
 *             SW6:   Change display 3 mode
 *             SW8:   Change pitch mode
 *             SW1:   Pitch left
 *             SW10:  Pitch right
 *             SW3:   Change mast mode
 *             SW2:   Mast left
 *             SW9:   Mast right
 *             SW7:   ROPS On
 *             SW4:   ROPS Off
*/
void ProcessSwitches()
{
  // Display 1 mode
  if (CheckSwitchPressedOnce(5))
    disp1 = (disp1 + 1) & 4;

  // Display 2 mode
  // if (CheckSwitchPressedOnce(12))
  //   disp3 = (disp2 + 1) & 4;

  // Display 3 mode
  if (CheckSwitchPressedOnce(6))
    disp3 = (disp3 + 1) & 4;


  // Pitch mode
  if (CheckSwitchPressedOnce(8))
  {
    static UINT64 mode = PITCH_MODE_MANUAL;
    Can_SendData(0x6A, mode);
    mode ^= 1;
  }

  // Pitch left
  if (CheckSwitch(1))
  {
    static UINT64 pitch_left_data = 0x01;
    CAN_SendData(0x7A, pitch_left_data);
  }
  // Pitch right
  if (CheckSwitch(10))
  {
    static UINT64 pitch_right_data = 0x200;
    CAN_SendData(0x7A, pitch_right_data);
  }
  // Pitch stop
  if (!CheckSwitch(1) && !CheckSwitch(10))
  {
    static UINT64 pitch_stop_data = 0x00;
    CAN_SendData(0x7A, pitch_stop_data);
  }

  // Mast Mode
  if (CheckSwitchPressedOnce(3))
  {
    static UINT8 mode = MAST_MODE_MANUAL;
    CAN_SendByte(0x6B, mode);
    mode ^= 1;
  }

  // Mast left
  if (CheckSwitch(2))
  {
    CAN_SendFloat(0x7B, 10.0f);
  }
  // Mast right
  if (CheckSwitch(9))
  {
    CAN_SendFloat(0x7B, -10.0f);
  }
  // Mast stop
  if (!CheckSwitch(2) && !CheckSwitch(9))
  {
    CAN_SendFloat(0x7B, 0.0f)
  }

  // ROPS
  if (CheckSwitchPressedOnce(7))
  {
    // ROPS on
    CAN_SendByte(0x18, 1);
  }
  if (CheckSwitchPressedOnce(4))
  {
    // ROPS off
    CAN_SendByte(0x18, 0);
  }
  
}

/**
 * @brief      Enable interrupts
 * 
 * @details    CAN interrupts
 *             Peripheral interrupts
 *             Configure System interrupts
*/
void EnableInterrupts()
{
  PeripheralsEnableInterrupts();
  CAN_EnableInterrupts();

  INTConfigureSystem(INT_SYSTEM_CONFIG_MULT_VECTOR);
  INTEnableInterrupts();
}

/**
 * @brief      The state machine
 * 
 * @details
*/
void state_machine_exec()
{
  switch (state_machine_val)
  {
  case STATE_INIT:
  {
    state_init();
    break;
  }

  case STATE_STANDBY:
  {
    state_standby();
    break;
  }

  case STATE_ACQ:
  {
    state_acq();
    break;
  }

  // When default, go back to init
  default:
  {
    state_machine_val = STATE_INIT;
    break;
  }
  }
}

/**
 * @brief      State init, called once, initialize everything
 * 
 * @details    Initialize peripherals, CAN, interrupts, display, etc.
*/
void state_init()
{
  INTDisableInterrupts();
  
  InitPeripherals();
  CAN_Init();

  EnableInterrupts();

  DisplayInit();

  // Set display mode to 0
  disp1 = 0;
  disp2 = 0;
  disp3 = 0;

  // Set all switches status memory to 0
  memset(&mem_switches[0], 0, sizeof(UINT8) * 12);

  // Tell Mario volant is ready
  CAN_SendByte(0x70, 0x42);                                                     // TODO: Send Byte on CAN BUS
}

/**
 * @brief      State standby, normal state of the volant
 * 
 * @details    Display data, check switches
*/
void state_standby()
{
  // Refresh the display every 50ms
  if (flags.flag_50ms)
  {
    // Reset the flag for the timer
    flags.flag_50ms = 0;

    DisplayData();
  }

  // Check switches
  if (CheckSwitches())
  {
    // If a switch has been pressed, go to acquisition state
    state_machine_val = STATE_ACQ;
  }
}

/**
 * @brief      State acquisition, called when a switch has been pressed
 * 
 * @details    Process switches, then go back to standby
*/
void state_acq()
{
  ProcessSwitches();
  
  state_machine_val = STATE_STANDBY;
}

/* ***************************** Main function ****************************** */

/**
 * @brief      Main function
 * 
 * @details    Initialize the state machine, then loop forever
*/
void main(void)
{
  // Initialize the state machine to init
  state_machine_val = STATE_INIT;
  
  // Loop forever
  while (1)
  {
    // Execute the state machine
    state_machine_exec();
    
    // Wait a bit
    for (int i = 0; i < 2000; ++i);
  }
}
