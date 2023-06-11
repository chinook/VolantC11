

#include "ChinookLib.h"
#include "Display.h"
#include "main.h"

// Defines
#define MAX_REG_NOOP             0x00
#define MAX_REG_DECODE_MODE      0x01
#define MAX_REG_GLOBAL_INTENSITY 0x02
#define MAX_REG_SCAN_LIMIT       0x03
#define MAX_REG_CONFIGURATION    0x04
#define MAX_REG_DISPLAY_TEST     0x05
#define MAX_REG_DIGIT_TYPE       0x06


#define MAX_REG_INTENSITY10      0x10
#define MAX_REG_INTENSITY32      0x11
#define MAX_REG_INTENSITY54      0x12
#define MAX_REG_INTENSITY76      0x13
#define MAX_REG_INTENSITY10a     0x14
#define MAX_REG_INTENSITY32a     0x15
#define MAX_REG_INTENSITY54a     0x16
#define MAX_REG_INTENSITY76a     0x17

#define MAX_DIGIT1    0x20
#define MAX_DIGIT2    0x28
#define MAX_DIGIT3    0x21
#define MAX_DIGIT4    0x29
#define MAX_DIGIT5    0x22
#define MAX_DIGIT6    0x2A
#define MAX_DIGIT7    0x23
#define MAX_DIGIT8    0x2B
#define MAX_DIGIT9    0x24
#define MAX_DIGIT10   0x2C
#define MAX_ARRAY1    0x25
#define MAX_ARRAY2    0x2D

#define BLANK         0x10

#define MINUS_7SEG    0x01
#define DP_7SEG       0x80


// Private variables and definitions
typedef struct
{
  UINT32 num_digits;
  UINT32 _7seg_displays[4];
} LedDisplay;
LedDisplay display1, display2, display3;



void MAX_Init();
void MAX_Write(UINT16 reg, UINT8 data);

void PrintFloat(LedDisplay* display, float value);
void PrintFloatFixed(LedDisplay* display, float value);
void PrintInt(LedDisplay* display, int value);
void PrintDigits(LedDisplay* display, char digits[4], int decimal_location);




void MAX_Init()
{
  // First 10 digits in decode mode and 11/12 digits in non-decode mode
  MAX_Write(MAX_REG_DECODE_MODE, 0x1F);

  MAX_Write(MAX_REG_SCAN_LIMIT, 0x05); // Limits scanning to 12 digits
  MAX_Write(MAX_REG_CONFIGURATION, 0x11);
  MAX_Write(MAX_GLOBAL_INTENSITY, 0x07);
  MAX_Write(MAX_DIGIT_TYPE, 0x00);

  // TODO: 0x07 reg en define
  MAX_Write(0x07, 0x01);
  while (!flags.flag_500ms);
  flags.flag_500ms = 0;
  MAX_Write(0x07, 0x00);
}

void MAX_Write()
{
  UINT16 data = (REG << 8 | DATA) << 1;
  
  while (SpiChnIsBusy(SPI3+1));
  SPI_CS = 0;

  Spi.SendCharacter(SPI3, data);
  while (SpiChnIsBusy(SPI3+1));

  SPI_CS = 1;
}


void PrintFloat(LedDisplay* display, float value)
{
  float position = pow(10, (int)(log(value)/log(10.0f)));
  float valueToRemove = 0;
  int decimal_position = -1;
  int decimal_set = 0;
    
  // Store the digits in an array
  char digits[display->numDigits];
    
  int i;
  for(i = 0; i < display->numDigits; ++i)
  {
    char digit = (int)((value - valueToRemove) / position);
            
    digits[i] = digit;
        
    // Advance the position
    valueToRemove += (float)digit * position;
    position /= 10.0f;
        
    if(position < 1.0f && !decimal_set)
    {
      decimal_position = i;
      decimal_set = 1;
    }
  }
  
  // Perform the print using the digits
  PrintDigits(display, digits, decimal_position);
}

void PrintFloatFixed(LedDisplay* display, float value, int decimal_position)
{
  if(value < 0)
    value *= -1;
  float position = pow(10.0f, (float)decimal_position);
    
  int i;
  float valueToRemove = 0;
    
  // Store the digits in an array
  char digits[display->numDigits];
    
  for(i = 0; i < display->numDigits; ++i)
  {
    char digit = (char)((value - valueToRemove) / position);
    digits[i] = digit;
        
    // Advance the position
    valueToRemove += (float)digit * position;
    position /= 10.0f;
  }
    
  // Perform the print using the digits
  PrintDigits(display, digits, decimal_position);
}

void PrintInt(LedDisplay* display, int value)
{
  int neg = (value < 0) ? 1 : 0;
  if(neg)
  {
    value *= -1;
  }
  int position = pow((float)10, (float)display->numDigits-1);
  int valueToRemove = 0;
    
  // Store the digits in an array
  char digits[display->numDigits];
    
  int i = 0;
  for(i; i < display->numDigits; ++i)
  {
    unsigned digit = ((unsigned)value - (unsigned)valueToRemove) / (unsigned)position;
    digits[i] = (char)digit;
        
    // Advance the position
    valueToRemove += digit * position;
    position /= 10.0;
  }
    
  // Perform the print using the digits
  PrintDigits(display, digits, 4);
}

void PrintDigits(LedDisplay* display, char digits[4], int decimal_location)
{  
  int hadDigit = 0;
    
  int i = 0;
  for(i = 0; i < display->numDigits; ++i)
  {
    // Do not display leading zeros UNLESS its at position of the decimal place
    if(digits[i] == 255)
    {
      MAX_Write(display->_7seg_displays[i], 0x44);
      continue;
    }
    else if(digits[i] == 0 && i != decimal_location && !hadDigit)
    {
      MAX_Write(display->_7seg_displays[i], 0);
      continue;
    }
    
    // Check for the decimal dot
    int decimal = 0;
    if(decimal_location == i && i != display->numDigits-1 && decimal_location < display->numDigits-1)
    {
      decimal = DP_7SEG;
    }
    
    if(digits[i] != 0)
      hadDigit = 1;
    
    // Write the digit to the display
    MAX_Write(display->_7seg_displays[i], digits[i] + decimal);
  }
}



void DisplayInit()
{
  MAX_Init();

  display1.numDigits = 4;
  display1._7seg_displays[0] = 0x20;
  display1._7seg_displays[1] = 0x28;
  display1._7seg_displays[2] = 0x21;
  display1._7seg_displays[3] = 0x29;
  display2.numDigits = 2;
  display2._7seg_displays[0] = 0x22;
  display2._7seg_displays[1] = 0x2A;
  display3.numDigits = 4;
  display3._7seg_displays[0] = 0x23;
  display3._7seg_displays[1] = 0x2B;
  display3._7seg_displays[2] = 0x24;
  display3._7seg_displays[3] = 0x2C;
}

enum DISPLAY1_VALUES
{
 MAST_ANGLE,
 WIND_SPEED,
 WHEEL_RPM,
 POWER
};

enum DISPLAY2_VALUES
{
 EFFICIENCY
};

enum DISPLAY3_VALUES
{
  PITCH,
  WIND_DIR,
  TURB_RPM,
  TSR
};

void DisplayData()
{
  switch (disp1)
  {
  case MAST_ANGLE:
    // PrintFloatFixed(&display1, sensor_data.mast_angle, 3); // MAN.G
    PrintFloatFixed(&display1, 0.0f, 0);
    break;

  case WIND_SPEED:
    PrintFloatFixed(&display1, sensor_data.wind_speed, 2); // WS.PD
    break;

  case WHEEL_RPM:
    PrintFloatFixed(&display1, sensor_data.wheel_rpm, 3); // WRP.M
    break;

  case POWER:
    PrintFloatFixed(&display1, power, 3); // POW.E
    break;

  default:
    disp1 = 0;
    break;
  }

  switch (disp2)
  {
  case EFFICIENCY:
    PrintFloatFixed(&display2, efficiency, 2); // EF.
    break;

  default:
    disp2 = 0;
    break;
  }

  switch (disp3)
  {
  case PITCH:
    PrintFloatFixed(&display3, sensor_data.pitch, 2); // PI.TC
    break;

  case WIND_DIR:
    PrintFloatFixed(&display3, sensor_data.wind_direction, 3); // WDI.R
    break;

  case TURB_RPM:
    PrintFloatFixed(&display3, sensor_data.turbine_rpm, 3); // TRP.M
    break;

  case TSR:
    PrintFloatFixed(&display3, tsr, 3); // TSR.x
    break;

  default:
    disp3 = 0;
    break;
  }
}
