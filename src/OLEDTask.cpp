#include "defines.h"

void OLEDClearAndPrint( int x, int y, String oldValue, String newValue, const unsigned char * font )
{
  // Clear prevous data
  u8g2.setDrawColor(0);
  u8g2.setFontMode(1);
  u8g2.setFont(font);
  u8g2.setCursor(x, y);
  u8g2.print(oldValue.c_str());

  u8g2.setDrawColor(1);
  u8g2.setFontMode(0);
  u8g2.setCursor(x, y);
  u8g2.print(newValue.c_str());  
}// void OLEDClearAndPrint( int x, int y, String oldValue, String newValue, const unsigned char * font )

void vOLEDTask(void *parameter)
{
  if( i2cMutex )
    while(1){
      if( 
          xSemaphoreTake( i2cMutex, portMAX_DELAY ) == pdTRUE 
        ){
          u8g2.setBusClock(OLED_BUS_CLOCK);

          String monthName = monthNames[now.month() - 1];
          String dayOfWeek = daysOfTheWeek[now.dayOfTheWeek()];
          String oldValue = "", newValue = "";
          static String formattedTime = "";
          static String formattedDate = "";

          String dayStr = (now.day() < 10 ? "0" : "") + String(now.day(), DEC);
          String hourStr = (now.hour() < 10 ? "0" : "") + String(now.hour(), DEC);
          String minuteStr = (now.minute() < 10 ? "0" : "") + String(now.minute(), DEC);
          String secondStr = (now.second() < 10 ? "0" : "") + String(now.second(), DEC);

          oldValue = formattedDate;
          formattedDate = dayStr + " " + monthName + " " + dayOfWeek;
          newValue = formattedDate;  
          OLEDClearAndPrint( 20, 40, oldValue, newValue, u8g2_font_lubR10_tr );

          oldValue = formattedTime;
          formattedTime = hourStr + ":" + minuteStr + ":" + secondStr;
          newValue = formattedTime;  
          OLEDClearAndPrint( 30, 60, oldValue, newValue, u8g2_font_lubR12_tr );

          oldValue = String( prev_temperature ) + String("C");
          newValue = String( temperature ) + String("C");  
          // newValue = String( getTemperature( LM75_ADDR_ONE ) ) + String("C");
          OLEDClearAndPrint( 0, 20, oldValue, newValue, u8g2_font_lubR10_tr );

          u8g2.sendBuffer();
          xSemaphoreGive( i2cMutex );
          vTaskDelay(200);
      }
  }
  vTaskDelete(NULL);
}  // void vOLEDTask()

