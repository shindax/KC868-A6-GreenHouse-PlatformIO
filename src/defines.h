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
#define MINUTE_PASSED_FLAG      BIT0
#define MIDNIGHT_HAS_COME_FLAG  BIT1
#define BARREL_IS_FULL_FLAG     BIT2
#define ONBOARD_BUTTON_FLAG     BIT3
#define FLAG_4                  BIT4
#define FLAG_5                  BIT5
#define FLAG_6                  BIT6
#define FLAG_7                  BIT7

#define FLAG_8                  BIT8
#define FLAG_9                  BIT9
#define FLAG_10                 BIT10
#define FLAG_11                 BIT11
#define FLAG_12                 BIT12
#define FLAG_13                 BIT13
#define FLAG_14                 BIT14
#define FLAG_15                 BIT15

#define FLAG_16                 BIT16
#define FLAG_17                 BIT17
#define FLAG_18                 BIT18
#define FLAG_19                 BIT19
#define FLAG_20                 BIT20
#define FLAG_21                 BIT21
#define FLAG_22                 BIT22
#define ALARM_FLAG              BIT23

#define BARREL_FULL_SW          BIT0
#define IN_1                    BIT1
#define IN_2                    BIT2
#define IN_3                    BIT3
#define IN_4                    BIT4
#define IN_5                    BIT5
#define IN_6                    BIT6
#define IN_7                    BIT7

#define OUT_0                   BIT0
#define OUT_1                   BIT1
#define OUT_2                   BIT2
#define OUT_3                   BIT3
#define OUT_4                   BIT4
#define OUT_5                   BIT5
#define OUT_6                   BIT6
#define OUT_7                   BIT7

#define USE_ALARM_OUTPUT

#ifdef USE_ALARM_OUTPUT
#define PORT_MASK               0x1F
#else
#define PORT_MASK               0x3F
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

BaseType_t waitMutex( SemaphoreHandle_t );
BaseType_t returnMutex( SemaphoreHandle_t );

EventBits_t waitFlag( EventBits_t, BaseType_t = pdFALSE );
EventBits_t getFlag( EventBits_t );
EventBits_t setFlag( EventBits_t );
EventBits_t resetFlag( EventBits_t );

EventBits_t updateInputs( EventBits_t flag );

EventBits_t setOutputs( EventBits_t );
EventBits_t clearOutputs( EventBits_t  = PORT_MASK );
EventBits_t updateOutputs( EventBits_t );

EventBits_t getInputsOutputsState( void );

extern SemaphoreHandle_t i2cMutex;
extern SemaphoreHandle_t inputOutputMutex;
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