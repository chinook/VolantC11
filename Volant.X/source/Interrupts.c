

#include "ChinookLib.h"

#include "main.h"


void __ISR(_TIMER_1_VECTOR, T1_INTERRUPT_PRIORITY) Timer1InterruptHandler(void)
{
  mT1ClearIntFlag();
}

void __ISR(_TIMER_2_VECTOR, T2_INTERRUPT_PRIORITY) Timer1InterruptHandler(void)
{
  mT2ClearIntFlag();
  flags.flag_50ms = 1;
}


void __ISR(_TIMER_4_VECTOR, T4_INTERRUPT_PRIORITY) Timer1InterruptHandler(void)
{
  mT4ClearIntFlag();
  flags.flag_500ms = 1;
}


void __ISR(_ADC_VECTOR, ADC_INTERRUPT_PRIO) AdcInterruptHandler(void)
{
  Adc.Read();
  INTClearFlag(INT_AD1);
  flags.flag_rotary_encoder = 1;
}




