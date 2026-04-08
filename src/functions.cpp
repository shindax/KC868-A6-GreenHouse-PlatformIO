#include "defines.h"

BaseType_t getMutex( SemaphoreHandle_t  mutex )
{
    return xSemaphoreTake( mutex, portMAX_DELAY );
}

BaseType_t returnMutex( SemaphoreHandle_t  mutex )
{
    return xSemaphoreGive( mutex );
}

BaseType_t setSemaphore( SemaphoreHandle_t  semaphore )
{
    return xSemaphoreGive( semaphore );
}

BaseType_t waitSemaphore( SemaphoreHandle_t  semaphore )
{
    return xSemaphoreTake( semaphore, portMAX_DELAY );
}

EventBits_t waitFlag( EventBits_t flag )
{
    return xEventGroupWaitBits( eventGroup, flag, pdFALSE, pdTRUE, portMAX_DELAY );
}

EventBits_t setFlag( EventBits_t flag )
{
    return xEventGroupSetBits( eventGroup, flag ); 
}

EventBits_t resetFlag( EventBits_t flag )
{
    return xEventGroupClearBits( eventGroup, flag ); 
}