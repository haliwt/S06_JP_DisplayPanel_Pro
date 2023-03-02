#include "interrupt_manager.h"
#include "run.h"


/*******************************************************************************
	*
	*Function Name:void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
	*Function : timing 10ms interrupt call back function 
	*
	*
*******************************************************************************/
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  static uint8_t tm0,tm1;
    if(htim->Instance==TIM3){  
    tm0++;
	tm1++;

    if(tm1 > 9){ //100ms 
		tm1=0;
	    run_t.gTimer_led_500ms++;

	}
	
    if(tm0>99){ //100 *10ms = 1000ms = 1s
		tm0=0;
		
		run_t.gTimer_set_temp_times ++;
		run_t.gTimer_key_4s ++;
		run_t.gTimer_key_60s++;
		run_t.fan_off_60s++;
		run_t.dispTime_seconds++;
	
	    run_t.gTimes_time_seconds ++;
		run_t.gTimer_Counter ++;
		run_t.gTimer_display_dht11++;
		 
		
	}
    
    }
 }
	





