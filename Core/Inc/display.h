#ifndef __DISPLAY_H_
#define __DISPLAY_H_

#include "main.h"

void Display_DHT11_Value(void);

//void DisplaySMG_LED(void);

void DisplayTiming_KEY_Add_Subtract_Fun(void);


void Display_GMT(uint8_t hours,uint8_t minutes);
void Display_Colon_Blink_Function(uint8_t hours,uint8_t minutes,uint8_t sel);

void TimeColon_Smg_Blink_Fun(void);

#endif 
