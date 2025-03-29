#include "bsp.h"


process_t g_pro;

void decode_process_handler(void)
{
  static uint8_t m,n;
  if(g_pro.wifi_set_timer_timing_flag ==1 &&  g_pro.power_on_flag ==  1) {
	  g_pro.wifi_set_timer_timing_flag++;

	  run_t.dispTime_minutes = 0;
             
            run_t.temp_set_timer_timing_flag= 1;
	   
			run_t.gTimer_key_timing=0;
		    
            
             m=(run_t.dispTime_hours ) /10;
	       

			 n= (run_t.dispTime_hours ) %10;
			
	       run_t.hours_two_bit = n;
				run_t.minutes_one_bit = 0;
			 
             TM1639_Write_4Bit_Time(m,run_t.hours_two_bit,run_t.minutes_one_bit,0,0) ; // timer   mode  "H0: xx"



  }  

}


void power_on_run_led_handler(void)
{
  
     Power_ON_Led();
	 SMG_POWER_ON(); //WT.EDIT 2023.03.02

}

