#include "defines.h"

float getTemperature( uint8_t addr )
{
  Wire.beginTransmission(addr);
  Wire.write(0x00); // Указатель на регистр температуры
  Wire.endTransmission();

  Wire.requestFrom( addr, (uint8_t) 2 );
  // if (Wire.available() == 2) {
    int8_t temp_high = Wire.read();
    uint8_t temp_low = Wire.read();
    int16_t rawTemp = ( ( temp_high << 8 ) | temp_low ) >> 4 ;
    temperature = (float)rawTemp * 0.0625; // 0.125 для 11-бит, или *0.5 для 9-бит
  // }
  return temperature;
}
