#include "defines.h"

void pollingCallback(void * parameter ) 
{
  uint8_t temp;

  if( i2c_Mutex )
    while(1){
      if( xSemaphoreTake( i2c_Mutex, portMAX_DELAY ) == pdTRUE ){
        temp = pcfIn.read8();
        if ( temp != digitalInputs) {
          digitalInputs = temp;
        }

        if( ! digitalRead( BUTTON_PIN ) )
          digitalOutputs |= 0x20;
            else
              digitalOutputs &= ~ 0x20;

        pcfOut.write8( ~ digitalOutputs );
        xSemaphoreGive( i2c_Mutex );
        vTaskDelay(pdMS_TO_TICKS(50));
      }
    }
  vTaskDelete(NULL);
}// void pollingCallback(void *parameter ) 