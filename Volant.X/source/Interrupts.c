/*
 * Interrupts.c
 *
 *  Created on: June 11, 2023
 *      Author: Marc
 */

/* ******************************* Includes ********************************* */

#include "ChinookLib.h"
#include "main.h"

/* ************************ Interrupts definitions ************************** */

/**
 * @brief     Timer 1 interrupt handler
 * 
 * @details   500 us interrupt
*/
void __ISR(_TIMER_1_VECTOR, T1_INTERRUPT_PRIORITY) Timer1InterruptHandler(void)
{
  // Clear the interrupt flag
  mT1ClearIntFlag();
}

/**
 * @brief     Timer 2 interrupt handler
 * 
 * @details   50 ms interrupt
*/
void __ISR(_TIMER_2_VECTOR, T2_INTERRUPT_PRIORITY) Timer2InterruptHandler(void)
{
  // Clear the interrupt flag
  mT2ClearIntFlag();

  // Set internal flag
  flag_50ms = 1;
}

/**
 * @brief     Timer 4 interrupt handler
 * 
 * @details   500 ms interrupt
*/
void __ISR(_TIMER_4_VECTOR, T4_INTERRUPT_PRIORITY) Timer4InterruptHandler(void)
{
  // Clear the interrupt flag
  mT4ClearIntFlag();

  // Set internal flag
  flag_500ms = 1;
}

/**
 * @brief     ADC interrupt handler
 * 
 * @details   ADC interrupt
*/
void __ISR(_ADC_VECTOR, ADC_INTERRUPT_PRIO) AdcInterruptHandler(void)
{
  // Read ADC value
  Adc.Read();

  // Clear the interrupt flag
  INTClearFlag(INT_AD1);

  // Set internal flag
  flag_rotary_encoder = 1;
}



