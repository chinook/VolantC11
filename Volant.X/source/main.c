

#include "ChinookLib.h"

#include "Peripherals.h"
#include "CAN_Driver.h"
#include "Display.h"

// Private function declarations
void state_machine_exec();


void state_init();
void state_standby();
void state_acq();


void EnableInterrupts();

UINT8 CheckSwitches();
void ProcessSwitches();


UINT8 mem_switches[12];

// Private definitions
typedef struct SWITCH_DECL_
{
  UINT16 ports[12];
  UINT16 bits[12];
}
SWITCH_DECL;
SWITCH_DECL switches =
{
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

UINT32 swi_to_sw[12] =
{
 SW1, SW2, SW3, SW4, SW5, SW6, SW7, SW8, SW9, SW10, SW11, SW12
};

// Private variable declarations
enum STATES
{
 STATE_INIT,
 STATE_STANDBY,
 STATE_ACQ,

 NUM_STATES
};
UINT32 state_machine_val;



UINT8 CheckSwitches()
{
  UINT8 sw_changed;
  for (int i = 0; i < 12; ++i)
  {
    UINT8 sw_status = PORTReadBits(switches.ports[i], switches.bits[i]);
    if (sw_status != mem_switches[i])
    {
      mem_switches[i] = sw_status;
      sw_changed = 1;
    }
  }

  return sw_changed;
}

UINT8 CheckSwitch(UINT32 sw)
{
  if (swi_to_sw[sw - 1] != 1)
  {
    return 1;
  }
  return 0;
}

UINT8 CheckSwitchPressedOnce(UINT32 sw)
{
  if (swi_to_sw[sw - 1] != 1 && mem_switches[sw])
  {
    for(i = 0; i < 1000; ++i);
    mem_switches[sw] = 1;
    return 1;
  }
  else if (swi_to_sw[sw - 1] == 1 && mem_switches[sw])
  {
    mem_switches[sw] = 0;
  }
  return 0;
}

void ProcessSwitches()
{
  // Display 1 mode
  if (CheckSwitchPressedOnce(5))
    disp1 = (disp1 + 1) & 4;

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
    CAN_SendData(0x7A, 0x01);
  }
  // Pitch right
  if (CheckSwitch(10))
  {
    CAN_SendData(0x7A, 0x200);
  }
  if (!CheckSwitch(1) && !CheckSwitch(10))
  {
    CAN_SendData(0x7A, 0x00);
  }

  if (CheckSwitch(2))
  {
    CAN_SendFloat(0x7B, 10.0f);
  }
  if (CheckSwitch(9))
  {
    CAN_SendFloat(0x7B, -10.0f);
  }
  if (!CheckSwitch(2) && !CheckSwitch(9))
    CAN_SendFloat(0x7B, 0.0f);

  // Mast Mode
  if (CheckSwitchPressedOnce(3))
  {
    static UINT8 mode = MAST_MODE_MANUAL;
    CAN_SendByte(0x6B, mode);
    mode ^= 1;
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

void EnableInterrupts()
{
  PeripheralsEnableInterrupts();
  CAN_EnableInterrupts();

  INTConfigureSystem(INT_SYSTEM_CONFIG_MULT_VECTOR);
  INTEnableInterrupts();
}


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

  default:
  {
    state_machine_val = STATE_INIT;
    break;
  }
  }
}

void state_init()
{
  INTDisableInterrupts();
  
  InitPeripherals();
  CAN_Init();

  EnableInterrupts();

  DisplayInit();

  disp1 = 0;
  disp2 = 0;
  disp3 = 0;

  memset(&mem_switches[0], 0, sizeof(UINT8) * 12);

  // TODO: Send Byte on CAN BUS
  CAN_SendByte(0x70, 0x42);
}

void state_standby()
{
  if (flags.flag_50ms)
  {
    flags.flag_50ms = 0;

    DisplayData();
  }

  if (CheckSwitches())
  {
    state_machine_val = STATE_ACQ;
  }
}

void state_acq()
{
  ProcessSwitches();
  
  state_machine_val = STATE_STANDBY;
}

void main(void)
{
  state_machine_val = STATE_INIT;
  
  while (1)
  {
    state_machine_exec();
    
    for (int i = 0; i < 2000; ++i)
    {
      ;
    }
  }
}
