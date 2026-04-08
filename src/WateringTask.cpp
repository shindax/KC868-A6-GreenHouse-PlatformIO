#include "defines.h"

void vWateringTask( void *parameter ) 
{
    while(1){
        if( waitSemaphore( minutesCheckSemaphore ) == pdPASS )
            Serial.print("Watering check completed");
        vTaskDelay(20);
    }
  vTaskDelete(NULL);
}// vRTCTask