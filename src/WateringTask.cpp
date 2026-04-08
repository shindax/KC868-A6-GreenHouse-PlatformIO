#include "defines.h"

void vWateringTask( void * parameter ) 
{
    while(1){
        waitFlag( MINUTE_PASSED_FLAG );
        Serial.println("Watering check completed");
        resetFlag( MINUTE_PASSED_FLAG );
        vTaskDelay(20);
    }
  vTaskDelete(NULL);
}// vRTCTask