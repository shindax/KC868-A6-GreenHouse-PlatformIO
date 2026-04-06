#include "defines.h"

void vPCFTask(void * parameter ) 
{
  if( i2cMutex )
    while(1){
      uint8_t temp;
      if( xSemaphoreTake( i2cMutex, portMAX_DELAY ) == pdTRUE ){
        Wire.setClock(WIRE_BUS_CLOCK);
        temp = pcfIn.read8();
        if ( temp != digitalInputs) {
          digitalInputs = temp;
        }

        if( ! digitalRead( BUTTON_PIN ) )
          digitalOutputs |= 0x20;
            else
              digitalOutputs &= ~ 0x20;

        pcfOut.write8( ~ digitalOutputs );
        pcfOut.write8( 0xFF ^ ( int ) temperature );
        xSemaphoreGive( i2cMutex );
      }
      vTaskDelay(50);
    }// while(1){
  vTaskDelete(NULL);
}// void vPCFTask(void *parameter ) 