#include "defines.h"

BaseType_t waitMutex( SemaphoreHandle_t  mutex )
{
    return xSemaphoreTake( mutex, portMAX_DELAY ) == pdTRUE;
}

BaseType_t returnMutex( SemaphoreHandle_t  mutex )
{
    return xSemaphoreGive( mutex );
}

EventBits_t waitFlag( EventBits_t flag, BaseType_t clear ) // default clear = pdFALSE
{
    return xEventGroupWaitBits( eventGroup, flag, clear, pdTRUE, portMAX_DELAY );
}

EventBits_t getFlag( EventBits_t flag )
{
    return xEventGroupGetBits( eventGroup ) & flag;
}

EventBits_t setFlag( EventBits_t flag )
{
    return xEventGroupSetBits( eventGroup, flag ); 
}

EventBits_t resetFlag( EventBits_t flag )
{
    return xEventGroupClearBits( eventGroup, flag ); 
}

EventBits_t updateInputs( EventBits_t flag )
{
    EventBits_t bits = 0;
    if( waitMutex( inputOutputMutex ) ){
        xEventGroupClearBits( inputsOutputs, 0x3F );
        bits = xEventGroupSetBits( inputsOutputs, flag & 0x3F ); 
        returnMutex( inputOutputMutex );
    }
    return bits;
}

EventBits_t setOutputs( EventBits_t flag )
{
    return xEventGroupSetBits( inputsOutputs,  ( flag & PORT_MASK ) << 8 ); 
}

EventBits_t clearOutputs( EventBits_t flag )
{
    return xEventGroupClearBits( inputsOutputs, ( flag & PORT_MASK ) << 8 ); 
}

EventBits_t updateOutputs( EventBits_t flag )
{
    EventBits_t bits = 0;
    if( waitMutex( inputOutputMutex ) ){
        xEventGroupClearBits( inputsOutputs, PORT_MASK << 8 ); 
        bits =  xEventGroupSetBits( inputsOutputs, ( flag & PORT_MASK ) << 8 ); 
        returnMutex( inputOutputMutex );
    }
    return bits;
}

EventBits_t getInputsOutputsState( void )
{
    EventBits_t bits = 0;
    if( waitMutex( inputOutputMutex ) ){
            bits = xEventGroupGetBits( inputsOutputs );
            returnMutex( inputOutputMutex );
        } // if( waitMutex( inputOutputMutex ) ){
    return bits;
}


