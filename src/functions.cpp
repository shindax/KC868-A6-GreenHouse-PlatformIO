#include "defines.h"

BaseType_t getMutex( SemaphoreHandle_t  mutex )
{
    return xSemaphoreTake( mutex, portMAX_DELAY );
}

BaseType_t returnMutex( SemaphoreHandle_t  mutex )
{
    return xSemaphoreGive( mutex );
}

EventBits_t waitFlag( EventBits_t flag )
{
    return xEventGroupWaitBits( eventGroup, flag, pdFALSE, pdTRUE, portMAX_DELAY );
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

EventBits_t setInputs( EventBits_t flag )
{
    return xEventGroupSetBits( inputsOutputs, flag ); 
}

EventBits_t clearInputs( EventBits_t flag )
{
    return xEventGroupClearBits( inputsOutputs, flag );
}

EventBits_t setOutputs( EventBits_t flag )
{
    return xEventGroupSetBits( inputsOutputs, flag << 8 ); 
}

EventBits_t clearOutputs( EventBits_t flag )
{
    return xEventGroupClearBits( inputsOutputs, flag << 8 ); 
}

EventBits_t updateOutputs( EventBits_t flag )
{
    clearOutputs();
    return xEventGroupSetBits( inputsOutputs, flag << 8 ); 
}

EventBits_t getInputsOutputsState( void )
{
    return xEventGroupGetBits( inputsOutputs );
}


