#include "defines.h"

void setup( void ) 
{
  Serial.begin(115200);
  while (!Serial)
    delay(10);

  eventGroup = xEventGroupCreate();
  
  Serial.println(__FILE__ __DATE__);
  Serial.print(F("Starting I2C interface..."));
  if( Wire.begin(I2C_SDA, I2C_SCL) ){
    Serial.println(F("done."));
    i2cMutex = xSemaphoreCreateMutex();
  }
    else
        Serial.println(F("failed."));
  
  if( i2cMutex && xSemaphoreTake( i2cMutex, portMAX_DELAY ) == pdTRUE ){ // I2C available
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

      // tasks related to I2C
      xTaskCreate(vRTCTask,  "RTCTask",  4000, NULL, 5, NULL);      
      xTaskCreate(vOLEDTask, "OLEDTask", 4000, NULL, 5, NULL);
      xTaskCreate(vPCFTask,  "PCFTask",  4000, NULL, 20, NULL);
      xSemaphoreGive( i2cMutex );
  }

  digitalOutputs = 0;
  pinMode( BUTTON_PIN, INPUT_PULLUP );

  xTaskCreate(vDotTask, "dotTask", 1500, NULL, 5, NULL);
  xTaskCreate(vWateringTask, "WateringTask", 1500, NULL, 20, NULL);  
  xTaskCreate(vBarrelTask,  "BarrelTask",  1500, NULL, 20, NULL);

}  // setup( void )

