#include "defines.h"

void timeCallback( void *parameter ) 
{
  if( i2c_Mutex )
    while(1){
      if( xSemaphoreTake( i2c_Mutex, portMAX_DELAY ) == pdTRUE ){
        Wire.setClock(WIRE_BUS_CLOCK);
        now = rtc.now();
        xSemaphoreGive( i2c_Mutex );
        vTaskDelay(500);
      }
    }
  vTaskDelete(NULL);
}