#include <Arduino.h>
#include "defines.h"

constexpr byte RS485_TX = 27;
constexpr byte RS485_RX = 14;
constexpr byte I2C_SDA = 4;
constexpr byte I2C_SCL = 15;
constexpr byte analogInputPins[] = { 36, 39, 34, 35 };  // Analog inputs
constexpr byte s2buttonPin = 0;                         // S2 Button
constexpr byte PCF8574_IN_ADDRESS = 0x22;
constexpr byte PCF8574_OUT_ADDRESS = 0x24;

RTC_DS1307 rtc;
DateTime now;
HT16K33 HT( 0x70, &Wire );

PCF8574 pcfIn(PCF8574_IN_ADDRESS, &Wire);
PCF8574 pcfOut(PCF8574_OUT_ADDRESS, &Wire);
char daysOfTheWeek[7][4] = { "SUN", "MON", "TUE", "WED", "THU", "FRI", "SAT" };
char monthNames[12][4] = { "JAN", "FEB", "MAR", "APR", "MAY", "JUN", "JUL", "AUG", "SEP", "OCT", "NOV", "DEC" };

float temperature = 0, prev_temperature = 0;
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE, I2C_SCL, I2C_SDA);

uint8_t digitalInputs;
uint8_t digitalOutputs;

SemaphoreHandle_t i2c_Mutex = 0;

void dotCallback( void *parameter ) 
{
  while(1){
    Serial.print(".");
    prev_temperature = temperature;
    temperature += 0.01;
    vTaskDelay(2000);
  }
  vTaskDelete(NULL);
}


void setup( void ) 
{
  Serial.begin(115200);
  while (!Serial)
    delay(10);

  Serial.println(__FILE__ __DATE__);
  Serial.print(F("Starting I2C interface..."));
  if( Wire.begin(I2C_SDA, I2C_SCL) ){
    Serial.println(F("done."));
    i2c_Mutex = xSemaphoreCreateMutex();
  }
    else
        Serial.println(F("failed."));
  
  if( i2c_Mutex ){
        initModule( pcfIn.begin(), "Initialising inputs...", "done.", "Error initialising PCF8574 input!" );
        initModule( pcfOut.begin(), "Initialising outputs...", "done.", "Error initialising PCF8574 output!" );
        initModule( rtc.begin(), "Starting RTC...", "done.", "Couldn't find RTC" );
        initModule( HT.begin(), "Starting HT16K33...", "done.", "Couldn't find HT16K33" );

        if (!rtc.isrunning()) {
          Serial.println(F("RTC is NOT running, let's set the time!"));
          rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
          // rtc.adjust(DateTime(2026, 1, 31, 23, 59, 45));
        }

      // OLED display
      // Note that 7-bit I2C addresses (like 0x2F, 0x3C) need to be shifted left
      u8g2.setI2CAddress(0x3C << 1);
      u8g2.setBusClock(OLED_BUS_CLOCK);
      initModule( u8g2.begin(), "Starting OLED display...", "done.", "Error initialising OLED" );  
      u8g2.setFlipMode(true); // rotate 180 deg
  }

  digitalOutputs = 0;
  pinMode( BUTTON_PIN, INPUT_PULLUP );

  xTaskCreatePinnedToCore(timeCallback, "timeCallback", 4096, NULL, 5, NULL, 1);  
  xTaskCreatePinnedToCore(oledCallback, "oledCallback", 4096, NULL, 5, NULL, 1);
  // xTaskCreatePinnedToCore(pollingCallback, "pollingCallback", 4096, NULL, 5, NULL, 1);
  xTaskCreatePinnedToCore(dotCallback, "dotCallback", 1000, NULL, 5, NULL, 1);
}  // setup( void )




void loop(void) 
{
}  // void loop( void )

