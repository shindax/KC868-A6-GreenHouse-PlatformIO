#include "defines.h"

void vPCFTask(void * parameter ) 
{
  while(1)
  {
      if( ! digitalRead( BUTTON_PIN )){
            if( !getFlag( ALARM_FLAG ) ){
                  Serial.println("Alarm!");
                  setFlag( ALARM_FLAG );              
                  setOutputs( OUT_5_FLAG );
            }// if( !getFlag( ALARM_FLAG ) ){
        }// if( ! digitalRead( BUTTON_PIN )){

    if( i2cMutex ){
      uint8_t temp;
      uint16_t state = getInputsOutputsState();
      if( xSemaphoreTake( i2cMutex, portMAX_DELAY ) == pdTRUE ){
        Wire.setClock(WIRE_BUS_CLOCK);
        pcfOut.write8( ~ ( state >> 8 ) ); // Sent output flags to hardware outputs
        uint8_t inputs = pcfIn.read8() ^ 0xFF;
        xSemaphoreGive( i2cMutex );
        clearInputs( ( state & 0x3F ) ^ inputs );
        setInputs( inputs );
      }
    }// if( i2cMutex ){
    vTaskDelay(20);
  }
  vTaskDelete(NULL);
}// void vPCFTask(void * parameter )