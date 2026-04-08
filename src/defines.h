#ifndef DEFINES_H
#define DEFINES_H

#define I2C_SDA         4
#define I2C_SCL         15

#define USE_DISPLAY
#define WIRE_BUS_CLOCK   100000UL
#define OLED_BUS_CLOCK  3400000UL
#define LM75_ADDR_ONE   0x4F
#define BUTTON_PIN      0

// Flags
#define MINUTE_PASSED_FLAG      1 << 0
#define MIDNIGHT_HAS_COME_FLAG  1 << 1
#define FLAG_2                  1 << 2
#define FLAG_3                  1 << 3
#define FLAG_4                  1 << 4
#define FLAG_5                  1 << 5
#define FLAG_6                  1 << 6
#define FLAG_7                  1 << 7

#define FLAG_8                  1 << 8
#define FLAG_9                  1 << 9
#define FLAG_10                 1 << 10
#define FLAG_11                 1 << 11
#define FLAG_12                 1 << 12
#define FLAG_13                 1 << 13
#define FLAG_14                 1 << 14
#define ALARM_FLAG              1 << 15

#define IN_0_FLAG               1 << 0
#define IN_1_FLAG               1 << 1
#define IN_2_FLAG               1 << 2
#define IN_3_FLAG               1 << 3
#define IN_4_FLAG               1 << 4
#define IN_5_FLAG               1 << 5
#define FLAG_22                 1 << 6
#define BUTTON_INPUT            1 << 7

#define OUT_0_FLAG              1 << 0
#define OUT_1_FLAG              1 << 1
#define OUT_2_FLAG              1 << 2
#define OUT_3_FLAG              1 << 3
#define OUT_4_FLAG              1 << 4
#define OUT_5_FLAG              1 << 5
#define FLAG_30                 1 << 6
#define FLAG_31                 1 << 7

#define USE_ALARM_OUTPUT

#ifdef USE_ALARM_OUTPUT
#define PORT_MASK               0x1F
#else
#define PORT_MASK               0x1F
#endif

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
void vWateringTask( void * );
void vBarrelTask( void * );

// FreeRTOS definitions

BaseType_t getMutex( SemaphoreHandle_t );
BaseType_t returnMutex( SemaphoreHandle_t );

EventBits_t waitFlag( EventBits_t );
EventBits_t getFlag( EventBits_t );
EventBits_t setFlag( EventBits_t );
EventBits_t resetFlag( EventBits_t );

EventBits_t setInputs( EventBits_t );
EventBits_t clearInputs( EventBits_t = 0x3F );
EventBits_t setOutputs( EventBits_t );
EventBits_t clearOutputs( EventBits_t  = PORT_MASK );
EventBits_t updateOutputs( EventBits_t );
EventBits_t getInputsOutputsState( void );

extern SemaphoreHandle_t i2cMutex;
extern EventGroupHandle_t eventGroup;
extern EventGroupHandle_t inputsOutputs;

// ----------------------------------------------

extern U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2;
extern RTC_DS1307 rtc;
extern DateTime now;
extern HT16K33 ht16k33;
extern char daysOfTheWeek[][4];
extern char monthNames[][4];
extern float temperature, prev_temperature;

extern PCF8574 pcfIn;
extern PCF8574 pcfOut;
extern FM24 fm24;

#endif