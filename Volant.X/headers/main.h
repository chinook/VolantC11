/*
 * main.h
 *
 *  Created on: June 11, 2023
 *      Author: Marc
 */

#ifndef _MAIN_H_
#define _MAIN_H_

/* ******************************* Includes ********************************* */

#include "ChinookLib.h"


/* ****************************** Definitions ******************************* */

//==============================================================================
// Define OUTPUT LED
//==============================================================================

#define LED_STATUS        LATBbits.LATB15                                       // LAT used for ??
#define LED_ERROR         LATBbits.LATB14
#define LED_CAN           LATBbits.LATB13
#define LED_DEBG4         LATBbits.LATB12
#define LED_DEBG3         LATBbits.LATB11
#define LED_DEBG2         LATBbits.LATB10
#define LED_DEBG1         LATBbits.LATB9
#define LED_DEBG0         LATBbits.LATB8

//==============================================================================
// Define INPUT SWITCH
//==============================================================================

#define SW1               PORTEbits.RE0
#define SW2               PORTEbits.RE1
#define SW3               PORTEbits.RE3
#define SW4               PORTDbits.RD7
#define SW5               PORTDbits.RD6
#define SW6               PORTEbits.RE2
#define SW7               PORTDbits.RD11
#define SW8               PORTDbits.RD9
#define SW9               PORTDbits.RD8
#define SW10              PORTDbits.RD10
#define SW11              PORTDbits.RD4
#define SW12              PORTDbits.RD5

//==============================================================================
// Define SPI PINOUT
//==============================================================================

#define SPI_CS          LATDbits.LATD0
#define SPI_CLK         LATDbits.LATD1
#define SPI_I           LATDbits.LATD2
#define SPI_O           LATDbits.LATD3



/* ***************************** Declarations ******************************* */

// Display 1 modes
enum DISPLAY1_VALUES
{
 MAST_ANGLE,
 WIND_SPEED,
 WHEEL_RPM,
 POWER
};

// Display 2 modes
enum DISPLAY2_VALUES
{
 EFFICIENCY
};

// Display 3 modes
enum DISPLAY3_VALUES
{
  PITCH,
  WIND_DIR,
  TURB_RPM,
  TSR
};


/* *************************** Global variables ***************************** */

// Flags struct
typedef struct FlagsData_
{
  UINT8 flag_50ms;
  UINT8 flag_500ms;
  UINT8 flag_can;
  UINT8 flag_rotary_encoder;
}
FlagsData;
extern volatile FlagsData flags;

// Sensor data struct
typedef struct SensorData_
{
  INT8 gear;
  float pitch;
  float pitch_algo;
  INT8 mast_mode;
  INT8 pitch_mode;
  float mast_dir;
  float wind_turbine_rpm;
  float wind_speed;
  float wind_direction;
  float wheel_rpm;
  float backplane_voltage;
  float backplane_current;
  float loadcell;
  float torque;
}
SensorData;
extern volatile SensorData sensor_data;

// Displayed values mode
extern volatile disp1;
extern volatile disp2;
extern volatile disp3;


#endif // _MAIN_H_
