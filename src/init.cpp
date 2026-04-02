#include "defines.h"

void initModule( bool status, String startMsg, String okMsg, String faultMsg )
{
  Serial.print(startMsg);
  if (status)
    Serial.println( okMsg );
      else
        Serial.println( faultMsg );
}

