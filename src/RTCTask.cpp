#include "defines.h"

void RTCTask( void *parameter ) 
{
  if( i2cMutex )
    while(1){
      if( xSemaphoreTake( i2cMutex, portMAX_DELAY ) == pdTRUE ){
        Wire.setClock(WIRE_BUS_CLOCK);
        now = rtc.now();
        xSemaphoreGive( i2cMutex );
        vTaskDelay(500);
      }
    }
  vTaskDelete(NULL);
}