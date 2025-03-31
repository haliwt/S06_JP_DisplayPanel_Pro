#include "bsp.h"


process_t g_pro;

void decode_process_handler(void)
{
  static uint8_t m,n;
  if(g_pro.wifi_set_timer_timing_flag ==1 &&  g_pro.power_on_flag ==  1) {
	  g_pro.wifi_set_timer_timing_flag++;

	  run_t.dispTime_minutes = 0;
      g_pro.gTimer_wifi_set_timing =0;//run_t.gTimer_time_colon=0;
	  run_t.gTimer_Counter =0;
             
         run_t.temp_set_timer_timing_flag= 1;
	   
			//run_t.gTimer_key_timing=0;
		    
            
             m=(run_t.dispTime_hours ) /10;
	       

			 n= (run_t.dispTime_hours ) %10;
			
	       run_t.hours_two_bit = n;
				run_t.minutes_one_bit = 0;
			 
             TM1639_Write_4Bit_Time(m,run_t.hours_two_bit,run_t.minutes_one_bit,0,0) ; // timer   mode  "H0: xx"
          run_t.gTimer_time_colon=0;


  }  
  else if(g_pro.wifi_set_timer_timing_flag == 2 && g_pro.gTimer_wifi_set_timing < 1){
	
		  TimeColon_Smg_Blink_Fun();
		  run_t.temp_set_timer_timing_flag =1;
        
		
		
	
   }
   else if(g_pro.wifi_set_timer_timing_flag ==2 && g_pro.gTimer_wifi_set_timing >0){
	
		  g_pro.wifi_set_timer_timing_flag++;
		  run_t.temp_set_timer_timing_flag =1;
          run_t.gTimer_Counter =0;
         
	
	
	 }

}


void power_on_run_led_handler(void)
{
  
     Power_ON_Led();
	 SMG_POWER_ON(); //WT.EDIT 2023.03.02

}

void answer_cmd_form_mainboard(void)
{

    if(g_pro.copy_cmd_flag !=0 && g_pro.gTimer_copy_cmd_couter > 1){

       g_pro.gTimer_copy_cmd_couter=0;

	   switch(g_pro.copy_cmd_flag){

         case KEY_POWER_ON:
		 	SendData_PowerOnOff(1);

	     break;

		 case KEY_POWER_OFF:
		    SendData_PowerOnOff(0);


		 break;

		 case RUN_WIFI_TIMER_POWER_ON:
		 	
		  SendData_Copy_Cmd(0xFB);


		 break;




	   }


	}


}

void panel_process_led_on(void)
{
if(g_pro.gTimer_turn_on_led > 1 && g_pro.power_on_flag == 1){

		g_pro.gTimer_turn_on_led=0;
	  //  power_on_run_led_handler();
	   
		Panel_Led_OnOff_Function();


	 }

}

