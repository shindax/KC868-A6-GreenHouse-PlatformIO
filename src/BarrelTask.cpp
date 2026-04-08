#include "defines.h"

void vBarrelTask( void * parameter ) 
{
    int cnt = 0;
    while(1){
        waitFlag( MIDNIGHT_HAS_COME_FLAG );
        EventBits_t bits = xEventGroupGetBits( eventGroup );
        Serial.print("Barrel task pass: ");
        Serial.println(cnt);
        cnt ++;
        if( cnt == 3 ){
            cnt = 0;
            resetFlag( MIDNIGHT_HAS_COME_FLAG );
        }
        vTaskDelay(2000);
    }
  vTaskDelete(NULL);
}// void vBarreTask( void * parameter ) 