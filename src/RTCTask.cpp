#include "defines.h"

void vRTCTask( void * parameter ) 
{
  TickType_t xLastWakeTime = xTaskGetTickCount();

  if( i2cMutex )
    while(1){
      if( waitMutex( i2cMutex ) ){
        Wire.setClock(WIRE_BUS_CLOCK);
        now = rtc.now();
        returnMutex( i2cMutex );
      }// if( waitMutex( i2cMutex ) ){
      
      if( now.second() == 0 )// Check time every minute
          setFlag( MINUTE_PASSED_FLAG );

      if( now.second() == 5 || now.second() == 35 )
          setFlag( MIDNIGHT_HAS_COME_FLAG );

      if( now.hour() == 0 )// Night time
          setFlag( MIDNIGHT_HAS_COME_FLAG );

      vTaskDelayUntil( &xLastWakeTime, 1000 );
    }// while(1){
  vTaskDelete(NULL);
}// vRTCTask