#ifndef DEFINES_H
#define DEFINES_H

#define I2C_SDA         4
#define I2C_SCL         15

#define USE_DISPLAY
#define WIRE_BUS_CLOCK   100000UL
#define OLED_BUS_CLOCK  3400000UL
#define LM75_ADDR_ONE   0x4F
#define BUTTON_PIN      0

#define OUT_0         1
#define OUT_1         2
#define OUT_2         4
#define OUT_3         8
#define OUT_4         16
#define OUT_5         32

#define IN_0          1
#define IN_1          2
#define IN_2          4
#define IN_3          8
#define IN_4          16
#define IN_5          32

#include <Arduino.h>
#include <PCF8574.h>
#include <LM75.h>
#include <Wire.h>
#include <RTClib.h>
#include <U8g2lib.h>
#include <HT16K33.h>
#include <FM24.h>

void setup( void );
const char* getTimeString( void );
const char* getDateString( void );
float getTemperature( unsigned char );
void initModule( bool status, String startMsg, String okMsg, String faultMsg );
void OLEDClearAndPrint( int x, int y, String oldValue, String newValue, const unsigned char * font );

void vOLEDTask( void * );
void vPCFTask( void * );
void vRTCTask( void * );
void vDotTask( void * );

extern U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2;
extern RTC_DS1307 rtc;
extern DateTime now;
extern HT16K33 HT;
extern char daysOfTheWeek[][4];
extern char monthNames[][4];
extern float temperature, prev_temperature;

extern PCF8574 pcfIn;
extern PCF8574 pcfOut;
extern FM24 fm24;
extern SemaphoreHandle_t i2cMutex;

extern uint8_t digitalInputs;
extern uint8_t digitalOutputs;

#endif