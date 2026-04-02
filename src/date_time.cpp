#include "defines.h"

String formattedString;

const char* getDateString( void ) 
{
  DateTime now = rtc.now();
  String yearStr = String(now.year(), DEC);
  String monthStr = (now.month() < 10 ? "0" : "") + String(now.month(), DEC);
  String dayStr = (now.day() < 10 ? "0" : "") + String(now.day(), DEC);
  String dayOfWeek = daysOfTheWeek[now.dayOfTheWeek()];

  formattedString = dayOfWeek + " " + dayStr + "." + monthStr + "." + yearStr;
  
  return formattedString.c_str();
}  // const char * getDateString( void )

const char * getTimeString(void) 
{
  DateTime now = rtc.now();
  String hourStr = (now.hour() < 10 ? "0" : "") + String(now.hour(), DEC);
  String minuteStr = (now.minute() < 10 ? "0" : "") + String(now.minute(), DEC);
  String secondStr = (now.second() < 10 ? "0" : "") + String(now.second(), DEC);

  formattedString = hourStr + ":" + minuteStr + ":" + secondStr;
  return formattedString.c_str();
}  // const char * getTimeString( void )