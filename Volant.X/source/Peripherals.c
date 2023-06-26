/*
 * Peripherals.c
 *
 *  Created on: June 11, 2023
 *      Author: Marc
 */

/* ******************************* Includes ********************************* */

#include "Peripherals.h"
#include "main.h"
#include "ChinookLib.h"

/* ************************** Private definitions *************************** */

// Timer interrupt priorities
#define TIMER1_INTERRUPT_PRIORITY       2
#define TIMER2_INTERRUPT_PRIORITY       3
#define TIMER4_INTERRUPT_PRIORITY       1

// Timer interrupt subpriorities
#define TIMER1_INTERRUPT_SUBPRIORITY    3
#define TIMER2_INTERRUPT_SUBPRIORITY    0
#define TIMER4_INTERRUPT_SUBPRIORITY    1

// SPI3 interrupt priorities and subpriorities
#define SPI3_INTERRUPT_PRIORITY         2
#define SPI3_INTERRUPT_SUBPRIORITY      1

// ADC interrupt priorities and subpriorities
#define ADC_INTERRUPT_PRIORITY          1
#define ADC_INTERRUPT_SUBPRIORITY       3

/* ********************* Private function declarations ********************** */

void InitTimers();
void InitSPI();
void InitADC();
void InitPorts();

/* *********************** Public function definitions ********************** */

/**
 * @brief     Initializes all peripherals
 * 
 * @details   Timers, SPI, ADC and ports are initialized
*/
void InitPeripherals()
{
  InitTimers();
  InitSPI();
  InitADC();
  InitPorts();
}

/**
 * @brief     Enables all interrupts
 * 
 * @details   Timer and ADC interrupts are enabled
*/
void PeripheralsEnableInterrupts()
{
  Timer.EnableInterrupt(TIMER_1);
  Timer.EnableInterrupt(TIMER_2);
  Timer.EnableInterrupt(TIMER_3);

  Adc.EnableInterrupts();
}

/* ********************** Private function definitions ********************** */

/**
 * @brief     Initializes timers
 * 
 * @details   Timers 1, 2 and 4 are initialized. Timer 3 is not used
 *            TIMER_1: 500 us period
 *            TIMER_2: 50 ms period
 *            TIMER_4: 500 ms period
*/
void InitTimers()
{
  // Set timer periods
  Timer.Open(TIMER_1, 500, SCALE_US);
  Timer.Open(TIMER_2, 50, SCALE_MS);
  // Timer.Open(TIMER_3, 5, SCALE_MS);
  Timer.Open(TIMER_4, 500, SCALE_MS);

  // Configure interrupts
  Timer.ConfigInterrupt(TIMER_1, TIMER1_INTERRUPT_PRIORITY, 
                                                  TIMER1_INTERRUPT_SUBPRIORITY);
  Timer.ConfigInterrupt(TIMER_2, TIMER2_INTERRUPT_PRIORITY, 
                                                  TIMER2_INTERRUPT_SUBPRIORITY);
  Timer.ConfigInterrupt(TIMER_4, TIMER4_INTERRUPT_PRIORITY, 
                                                  TIMER4_INTERRUPT_SUBPRIORITY);
}

/**
 * @brief     Initializes SPI3
 * 
 * @details   SPI3 is initialized as a master with 4 MHz clock
*/
void InitSPI()
{
  // SPI3 configuration
  SpiOpenFlags_t spi_flags =   SPI_MASTER_MODE
                             | SPI_16_BITS_CHAR
                             | SPI_ENHANCED_BUFFER_MODE
                             | SPI_TX_EVENT_BUFFER_SR_EMPTY
                             | SPI_RX_EVENT_BUFFER_NOT_EMPTY
                             | SPI_SAMPLE_END_CLK;

  // Enable SPI3 with 4 Mhz clock
  Spi.Open(SPI3, spi_flags, 4e6);
}

/**
 * @brief     Initializes ADC
 * 
 * @details   ADC is initialized with  us sampling clock
*/
void InitADC()
{
  // ADC configuration
  UINT32 sampling_clock = ADC_CLK_TMR;
  UINT32 config_hardware = ADC_VREF_AVDD_AVSS | ADC_SAMPLES_PER_INT_1;
  UINT32 config_port = ENABLE_AN2_ANA;
  UINT32 config_scan = SKIP_SCAN_AN0
                     | SKIP_SCAN_AN1
                     | SKIP_SCAN_AN3
                     | SKIP_SCAN_AN4
                     | SKIP_SCAN_AN5
                     | SKIP_SCAN_AN6
                     | SKIP_SCAN_AN7
                     | SKIP_SCAN_AN8
                     | SKIP_SCAN_AN9
                     | SKIP_SCAN_AN10
                     | SKIP_SCAN_AN11
                     | SKIP_SCAN_AN12
                     | SKIP_SCAN_AN13
                     | SKIP_SCAN_AN14
                     | SKIP_SCAN_AN15;

  // Enable ADC with  us sampling clock
  Adc.Open(sampling_clock, config_hardware, config_port, config_scan);

  // Configure interrupts
  Adc.ConfigInterrupt(ADC_INTERRUPT_PRIORITY, ADC_INTERRUPT_SUBPRIORITY);
}

/**
 * @brief     Initializes ports
 * 
 * @details   LEDs on Port B
 *            Push buttons on Port D
*/
void InitPorts()
{
  Port.A.CloseBits  ( BIT_0  | BIT_1  | BIT_2  | BIT_3                          // RA8, RA11-13 non existent
                    | BIT_4  | BIT_5  | BIT_6  | BIT_7
                    | BIT_9  | BIT_10 | BIT_14 | BIT_15 );

  Port.B.CloseBits  ( BIT_0  | BIT_1  | BIT_2  | BIT_3
                    | BIT_4  | BIT_5  | BIT_6  | BIT_7
                    | BIT_8  | BIT_9  | BIT_10 | BIT_11
                    | BIT_12 | BIT_13 | BIT_14 | BIT_15 );

  Port.C.CloseBits  ( BIT_1  | BIT_2  | BIT_3  | BIT_4                          // RC0, RC5-11 non existent
                    | BIT_12 | BIT_13 | BIT_14 | BIT_15 );

  Port.D.CloseBits  ( BIT_0  | BIT_1  | BIT_2  | BIT_3
                    | BIT_4  | BIT_5  | BIT_6  | BIT_7
                    | BIT_8  | BIT_9  | BIT_10 | BIT_11
                    | BIT_12 | BIT_13 | BIT_14 | BIT_15 );

  Port.E.CloseBits  ( BIT_0  | BIT_1  | BIT_2  | BIT_3                          // RE10-15 non existent
                    | BIT_4  | BIT_5  | BIT_6  | BIT_7
                    | BIT_8  | BIT_9  );

  Port.F.CloseBits  ( BIT_0  | BIT_1  | BIT_2  | BIT_3                          // RF6-7, RF9-11, RF14-15 non existent
                    | BIT_4  | BIT_5  | BIT_8  | BIT_12
                    | BIT_13 );

  Port.G.CloseBits  ( BIT_0  | BIT_1  | BIT_2  | BIT_3                          // RG4-5, RG10-11 non existent
                    | BIT_6  | BIT_7  | BIT_8  | BIT_9
                    | BIT_12 | BIT_13 | BIT_14 | BIT_15 );

  // Setup IO LED
  Port.B.SetPinsDigitalOut(BIT_8);      // LED_DEBG0
  Port.B.SetPinsDigitalOut(BIT_9);      // LED_DEBG1
  Port.B.SetPinsDigitalOut(BIT_10);     // LED_DEBG2
  Port.B.SetPinsDigitalOut(BIT_11);     // LED_DEBG3
  Port.B.SetPinsDigitalOut(BIT_12);     // LED_DEBG4
  Port.B.SetPinsDigitalOut(BIT_13);     // LED_CAN
  Port.B.SetPinsDigitalOut(BIT_14);     // LED_ERROR
  Port.B.SetPinsDigitalOut(BIT_15);     // LED_STATUS
    
  // LED ON
  LED_STATUS  = 0;
  LED_CAN     = 0;
  LED_ERROR   = 0;
  LED_DEBG4   = 0;
  LED_DEBG3   = 0;
  LED_DEBG2   = 0;
  LED_DEBG1   = 0;
  LED_DEBG0   = 0;
    
    
  // Setup Input back switch
  Port.D.SetPinsDigitalIn(BIT_6);      // pushbutton 1 (back)
  Port.D.SetPinsDigitalIn(BIT_7);      // pushbutton 2 (back)

  
  // Setup Input front switch
  Port.D.SetPinsDigitalIn(BIT_6);      // pushbutton 3
  Port.D.SetPinsDigitalIn(BIT_7);      // pushbutton 4
  Port.D.SetPinsDigitalIn(BIT_8);      // pushbutton 5
  Port.D.SetPinsDigitalIn(BIT_9);      // pushbutton 6
  Port.D.SetPinsDigitalIn(BIT_10);     // pushbutton 7
  Port.D.SetPinsDigitalIn(BIT_11);     // pushbutton 8
  Port.E.SetPinsDigitalIn(BIT_0);      // pushbutton 9
  Port.E.SetPinsDigitalIn(BIT_1);      // pushbutton 10 
  Port.E.SetPinsDigitalIn(BIT_2);      // pushbutton 11
  Port.E.SetPinsDigitalIn(BIT_3);      // pushbutton 12


  // Setup SPI SCn
  Port.D.SetPinsDigitalIn(BIT_2);       // SDI
  Port.D.SetPinsDigitalOut(BIT_3);      // SD0
  Port.D.SetPinsDigitalOut(BIT_0);      // CS (?)
  Port.D.SetPinsDigitalOut(BIT_1);      // CLK
}


