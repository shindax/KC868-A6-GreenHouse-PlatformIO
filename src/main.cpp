#include "defines.h"

constexpr byte RS485_TX = 27;
constexpr byte RS485_RX = 14;
// constexpr byte I2C_SDA = 4;
// constexpr byte I2C_SCL = 15;
constexpr byte analogInputPins[] = { 36, 39, 34, 35 };  // Analog inputs
constexpr byte s2buttonPin = 0;                         // S2 Button
constexpr byte PCF8574_IN_ADDRESS = 0x22;
constexpr byte PCF8574_OUT_ADDRESS = 0x24;

RTC_DS1307 rtc;
DateTime now;
HT16K33 HT( 0x70, &Wire );
FM24 fm24;

PCF8574 pcfIn(PCF8574_IN_ADDRESS, &Wire);
PCF8574 pcfOut(PCF8574_OUT_ADDRESS, &Wire);
char daysOfTheWeek[7][4] = { "SUN", "MON", "TUE", "WED", "THU", "FRI", "SAT" };
char monthNames[12][4] = { "JAN", "FEB", "MAR", "APR", "MAY", "JUN", "JUL", "AUG", "SEP", "OCT", "NOV", "DEC" };

float temperature = 0, prev_temperature = 0;
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE, I2C_SCL, I2C_SDA);

uint8_t digitalInputs = 0;
uint8_t digitalOutputs = 0;

SemaphoreHandle_t i2cMutex = 0;
SemaphoreHandle_t minutesCheckSemaphore = 0;
SemaphoreHandle_t nightSemaphore = 0;

void stackSizeCalc( void )
{
    UBaseType_t uxHighWaterMark = uxTaskGetStackHighWaterMark(NULL);
    Serial.print("stack Watermark: ");
    Serial.print( uxHighWaterMark );
    Serial.print(" in words ");
    Serial.println( uxHighWaterMark * 4 );
    vTaskDelay(5000);
}

void vDotTask( void * parameter ) 
{
  while(1){
    Serial.print(".");
    prev_temperature = temperature;
    temperature += 0.01;
    vTaskDelay(5000);
  }
  vTaskDelete(NULL);
}// vDotTask


void loop(void) 
{
}  // void loop( void )

