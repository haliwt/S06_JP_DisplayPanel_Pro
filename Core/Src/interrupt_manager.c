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
  static uint8_t tm0;
    if(htim->Instance==TIM3){  
    tm0++;
	
    run_t.gTimer_smg_timing++;
	run_t.gTimer_set_temp_times++;
	run_t.gTimer_led_500ms++;
	run_t.gTimer_time_colon++ ;
	run_t.gTimer_smg_display++;

   
	
    if(tm0>99){ //100 *10ms = 1000ms = 1s
		tm0=0;
		
	     run_t.gTimer_colon++;
		
		run_t.dispTime_seconds++;
	    run_t.gTimer_display_dht11++;
		//--------------//
		run_t .gTimer_wifi_slowly++;
		run_t.gTimer_key_timing++;
		run_t.gTimer_temperature++;
		run_t.gTimer_key_temp_timing++ ;
		run_t.gTimer_wifi_couter++;
		run_t.gTimer_temp_delay++;
        //usart
        run_t.gTimer_check_iwdg_flag++;
	   run_t.gTimer_iwdg++;
	   run_t.gTimer_usart_error++;

		if(run_t.gPower_On==1){
		    run_t.gTimer_Counter ++;
		    run_t.gTimes_time_seconds ++;

		}
		
	}
    
    }
 }
	





