#include "defines.h"

void vPCFTask(void * parameter ) 
{
  while(1)
  {
      if( ! digitalRead( BUTTON_PIN )){
            if( !getFlag( ALARM_FLAG ) ){
                  Serial.println();
                  Serial.println("Alarm!");
                  setFlag( ALARM_FLAG );              
                  setOutputs( OUT_5 );
            }// if( !getFlag( ALARM_FLAG ) ){
        }// if( ! digitalRead( BUTTON_PIN )){

    if( i2cMutex ){
      if( waitMutex( i2cMutex )){
        Wire.setClock(WIRE_BUS_CLOCK);

        updateInputs( pcfIn.read8() ^ 0xFF ); // Read and inverse inputs
        pcfOut.write8( ~ ( getInputsOutputsState() >> 8 ) ); // Inverse and send output flags to hardware outputs

        returnMutex( i2cMutex );
      }// if( waitMutex( i2cMutex ) ){

    }// if( i2cMutex ){
    vTaskDelay(20);
  }
  vTaskDelete(NULL);
}// void vPCFTask(void * parameter )