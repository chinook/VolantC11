/*
 * Peripherals.h
 *
 *  Created on: June 11, 2023
 *      Author: Marc
 */

#ifndef _PERIPHERALS_H_
#define _PERIPHERALS_H_

/* ********************** Public function declarations ********************** */

/**
 * @brief     Initializes all peripherals
 * 
 * @details   Timers, SPI, ADC and ports are initialized
*/
void InitPeripherals();

/**
 * @brief     Enables all interrupts
 * 
 * @details   Timer and ADC interrupts are enabled
*/
void PeripheralsEnableInterrupts();


#endif // _PERIPHERALS_H_