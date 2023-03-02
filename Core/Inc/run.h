#ifndef __RUN_H_
#define __RUN_H_
#include "main.h"


typedef enum WIFI_STATE_T{
   
    WIFI_POWER_ON = 0x80,
    WIFI_POWER_OFF=0X81,
    WIFI_MODE_1=0X08,   //state ->normal works
    WIFI_MODE_2=0X18,   //state->sleeping works
    WIFI_KILL_ON=0x04,  //Anion(plasma)
    WIFI_KILL_OFF=0x14,
    WIFI_PTC_ON = 0x02, 
    WIFI_PTC_OFF = 0x12,
    WIFI_SONIC_ON = 0x01,       //ultrasonic
    WIFI_SONIC_OFF = 0x11,
    WIFI_WIND_SPEED_ITEM = 0x90,
    WIFI_TEMPERATURE = 0xA0


}wifi_state_t;

typedef enum TIMING_T{

   timing_not_definition,
   timing_success 
}timing_t;


typedef enum _Signal{
	POWER_ON=0x01,
	POWER_OFF,
	PANEL_DATA,
	WIFI_INFO,
	WIFI_TIME,
	WIFI_TEMP,
	WIFI_CMD,
	WIFI_WIND_SPEED,
	WIFI_BEIJING_TIME,
	WIFI_SET_TIMING
}signal_t;

typedef enum _WIFI_POWER_STATE_{
	WIFI_POWER_ON_ITEM = 0x01,
	WIFI_POWER_OFF_ITEM,
	WIFI_POWER_NULL

}wifi_power_state;



typedef struct __RUN{

   uint8_t keyValue;
   uint8_t power_key;
   uint8_t gTemperature_timer_flag;
   uint8_t gPower_On;
   uint8_t gRun_flag;
   uint8_t power_times;
   
   uint8_t keyAdd_continue;
   uint8_t keyDec_continue;
  

   uint8_t gDht11_flag;
   uint8_t gTemperature;
 
   uint8_t gTimer_Counter;
   
  
  
  uint8_t gTimer_setup_zero;

  uint8_t gFan_RunContinue;

  uint8_t temperature_flag;
  

   uint8_t decodeFlag;
   uint8_t time_led_flag;

   uint8_t dec_key_times;
   uint8_t add_key_times;
   
   uint8_t  gTimer_Cmd;
   uint8_t  gPlasma;
 
   uint8_t  gDry;
   uint8_t  gBug;
   uint8_t  gWifi;

   uint8_t  gFan;
   uint8_t  gModel;
   uint8_t  gMode_flag;
   
   uint8_t  gFan_off_flag ;
  
   uint8_t  dry_key;
   uint8_t  gTimer_fan_counter;
   uint8_t gTimes_minutes_temp;
   uint8_t set_up_temp_flag;
   uint8_t gSet_up_times;
  
   uint8_t dispTime_minute;

   uint8_t gTimer_display_dht11;
  
   uint8_t gTimer_led_500ms;

   uint8_t fan_off_60s;
   uint8_t gTimer_key_60s;

   uint8_t Timer_mode_flag;
   uint8_t temperature_set_flag;

   uint8_t gTimes_time_seconds;
  
	
   uint8_t gReal_humtemp[2];
   uint8_t gInputCmd[2];
   uint8_t wifisetTime[1];
   uint8_t wifiCmd[2];
 
   //WIFI 
   uint8_t wifi_send_buzzer_sound;
   uint8_t gTimer_minute_Counter;
   uint8_t wifi_led_fast_blink_flag;
   uint8_t timer_timing_define_flag;
   uint8_t disp_wind_speed_grade ;
   uint8_t wifi_orderByMainboard_label;
   uint8_t panel_key_setup_timer_flag;
   uint8_t wifi_set_temp_flag;
   uint8_t 	gTimer_numbers_one_two_blink;
   uint8_t gTimer_temp_delay;
   uint8_t wifi_set_temperature;
   uint8_t wifi_set_wind_speed;
   uint8_t wifi_connect_flag;
   uint8_t gTimer_wifi_connect_counter;
   uint8_t temp_set_timer_timing_flag;
   uint8_t gTimer_key_timing;

   //timer timing 
   uint8_t gTimer_set_temp_times;
   uint8_t gTimer_wifi_slowly;
   uint8_t gTimer_smg_timing;
   uint8_t gTimer_temperature;

   
   
 

	int8_t dispTime_hours;
	int8_t dispTime_minutes;
	int8_t dispTime_seconds;
   


   
 }RUN_T;

extern RUN_T run_t;



void SplitDispose_Key(uint8_t value);



void Decode_Handler(void);



void Power_Off_Fun(void);

//void Power_Off(void);
void DisplayTimer_Timing(void);

void Receive_MainBoard_Data_Handler(uint8_t cmd);
void Power_On_Fun(void);


#endif 



