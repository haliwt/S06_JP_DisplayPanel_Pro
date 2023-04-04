#include "single_mode.h"
#include "run.h"
#include "smg.h"
#include "gpio.h"
#include "cmd_link.h"
#include "led.h"
#include "key.h"
#include "display.h"


uint8_t send_works_times_flag;

void (*single_ai_fun)(uint8_t cmd);
void (*single_add_fun)(void);
void (*single_buzzer_fun)(void);
void (*sendAi_usart_fun)(uint8_t senddat);
void (*dispose_key)(uint8_t dsdat);
static void Setup_Timer_Times(void);

static void Timing_Handler(void);
static void RunLocal_Smg_Process(void);

static void DisplayPanel_DHT11_Value(void);
static void SetTemperature_Function(void);



/******************************************************************************
*
*Function Name:static void Setup_Timer_Times(void)
*Funcion:display setup timer times  //__asm("NOP");//等待1个指令周期，系统主频24M
*Iinput Ref:NO
*Return Ref:NO
*
******************************************************************************/
static void Timing_Handler(void)
{

 
	switch(run_t.timer_timing_define_flag){

	case timing_success:
	   if(run_t.gTimer_Counter > 59){
	    run_t.gTimer_Counter =0;
		run_t.dispTime_minutes -- ;
		run_t.send_app_timer_total_minutes_data--;
	    if(run_t.dispTime_minutes < 0){
		     run_t.dispTime_hours -- ;
			 run_t.dispTime_minutes =59;

			if(run_t.dispTime_hours == 0 ){

	            run_t.dispTime_hours=0;
				
				run_t.dispTime_minutes=0;
				run_t.send_app_timer_total_minutes_data=0;
				run_t.gTimer_Cmd =0;	 //shut off timer of times

			    run_t.timer_timing_define_flag =  timing_fail;
				

			    
			    SendData_PowerOff(0);
				HAL_Delay(100);
				run_t.gTimer_set_temp_times=0; //conflict with send temperatur value 
				run_t.wifi_led_fast_blink_flag=0;
	
				run_t.gWifi =0;
				//run_t.temperature_set_flag =0;
		
				Power_Off_Fun();
				
				
		     }

	     }
		   

		 
            run_t.send_app_timer_minutes_one = run_t.send_app_timer_total_minutes_data >> 8;
		    run_t.send_app_timer_minutes_two = run_t.send_app_timer_total_minutes_data & 0x00ff;
            
		 	
		    SendData_Remaining_Time(run_t.send_app_timer_minutes_one, run_t.send_app_timer_minutes_two);
			
		    Display_GMT(run_t.dispTime_hours,run_t.dispTime_minutes);
            HAL_Delay(200);
		
		
	   }
        if(run_t.gTimer_colon < 51){
		   Display_Colon_Blink_Function(run_t.dispTime_hours,run_t.dispTime_minutes,0);
        }
		else if(run_t.gTimer_colon >  49  &&  run_t.gTimer_colon < 101){
		   
	       Display_Colon_Blink_Function(run_t.dispTime_hours,run_t.dispTime_minutes,1);

       }
	   else{
	      run_t.gTimer_colon =0;

	   }
      
       
	break;

	case  timing_fail:
		if(run_t.gTimes_time_seconds > 59){

			run_t.gTimes_time_seconds=0;
			run_t.works_dispTime_minutes++; //1 minute 
			run_t.send_app_wokes_total_minutes_data++;
			if(run_t.works_dispTime_minutes> 59){ //1 hour
			run_t.works_dispTime_minutes=0;
			run_t.works_dispTime_hours++;
			if(run_t.works_dispTime_hours > 24){
			run_t.works_dispTime_hours =0;
			}
		}
		
		run_t.send_app_wokes_minutes_one=run_t.send_app_wokes_total_minutes_data >> 8;
        run_t.send_app_wokes_minutes_two =run_t.send_app_wokes_total_minutes_data & 0x0ff;
		 SendData_Works_Time(run_t.send_app_wokes_minutes_one ,run_t.send_app_wokes_minutes_two);
		
		 Display_GMT(run_t.works_dispTime_hours,run_t.works_dispTime_minutes);
			
	   }

	   if(run_t.gTimer_colon < 51){
		   Display_Colon_Blink_Function(run_t.works_dispTime_hours,run_t.works_dispTime_minutes,0);
        }
		else if(run_t.gTimer_colon >  49  &&  run_t.gTimer_colon < 101){
		    Display_Colon_Blink_Function(run_t.works_dispTime_hours,run_t.works_dispTime_minutes,1);

       }
	   else{
	      run_t.gTimer_colon =0;

	   }
      
	
    break;

	}
    
    
    if(run_t.gTimes_time_seconds > 59 && run_t.timer_timing_define_flag ==timing_success ){
            run_t.gTimes_time_seconds=0;
            send_works_times_flag=1;
			run_t.works_dispTime_minutes++; //1 minute 
			run_t.send_app_wokes_total_minutes_data++;
            run_t.send_app_wokes_minutes_two++;
			if(run_t.works_dispTime_minutes> 59){ //1 hour
			run_t.works_dispTime_minutes=0;
			run_t.works_dispTime_hours++;
			if(run_t.works_dispTime_hours > 24){
			run_t.works_dispTime_hours =0;
			}
        
            if(run_t.works_dispTime_minutes >255){
               run_t.send_app_wokes_minutes_one++;
               run_t.send_app_wokes_minutes_two=0;
               run_t.send_app_wokes_total_minutes_data=0;
            }
		
    
          
            }
	  
        }
     while(send_works_times_flag==1){
            send_works_times_flag=0;
        SendData_Works_Time(run_t.send_app_wokes_minutes_one ,run_t.send_app_wokes_minutes_two);
        }


	
}
   
/******************************************************************************
*
*Function Name:void Single_RunCmd(void)
*Funcion: handle of receive by usart data
*
*
******************************************************************************/
static void DisplayPanel_DHT11_Value(void)
{

  if(run_t.gTimer_display_dht11 > 10 && run_t.set_temperature_flag==0){
	    run_t.gTimer_display_dht11=0;
       	Display_DHT11_Value();
     
	}
}

/******************************************************************************
	*
	*Function Name:void RunPocess_Command_Handler(void)
	*Funcion: display pannel run of process 
	*Input Ref: NO
	*Return Ref:NO
	*
******************************************************************************/
void RunPocess_Command_Handler(void)
{
	//key input run function
   static uint8_t key_set_temp_flag,m,n;
   if(run_t.gPower_On ==1 && run_t.decodeFlag ==0){
   	
       RunLocal_Smg_Process();
	   Timing_Handler();
       SetTemperature_Function();  
   	   SetTimer_Temperature_Number_Blink();
  }
   
  //POWER OFF 
  if(run_t.gPower_On ==0 || run_t.gPower_On == 0xff){
	 	run_t.gPower_On =0xff;
	      Breath_Led();
		  Power_Off();
		 
     }
 

 }
/*******************************************************
	*
	*Function Name: static void RunLocal_Smg_Process(void)
	*Function : display pannel display conetent
	*
	*
	*
*******************************************************/
static void RunLocal_Smg_Process(void)
{

	Panel_Led_OnOff_Function() ;//Lcd_PowerOn_Fun();
	
	 DisplayPanel_DHT11_Value();


}

static void SetTemperature_Function(void)
{
	 if(run_t.temperature_set_flag ==1 && run_t.gTimer_temp_delay >59){
               run_t.gTimer_temp_delay =0;
		 
		  
		  if(run_t.wifi_set_temperature <= run_t.gReal_humtemp[1] || run_t.gReal_humtemp[1] >39){//envirment temperature
	  
				run_t.gDry = 0;

		        SendData_Set_Command(DRY_OFF_NO_BUZZER);//PTC turn off
			    
			    
                
		  }
		  else if((run_t.wifi_set_temperature -3) > run_t.gReal_humtemp[1] ||  run_t.gReal_humtemp[1] < 37){
	  
		     run_t.gDry = 1;
	         SendData_Set_Command(DRY_ON_NO_BUZZER); //PTC turn On
				 
		  }
	  
	    
	  }
      else{ //no define set up temperature value 
          if(run_t.gReal_humtemp[1] >39 && run_t.gTimer_temp_delay >119){//envirment temperature
	            run_t.gTimer_temp_delay =0;
				run_t.gDry = 0;
                run_t.auto_model_shut_off_ptc_flag =1;
			    SendData_Set_Command(DRY_OFF_NO_BUZZER);

             }
             
             if(run_t.gReal_humtemp[1] < 36 && run_t.auto_model_shut_off_ptc_flag ==1 &&  run_t.gTimer_temp_delay >119){
                  run_t.gTimer_temp_delay =0;
                  run_t.gDry = 1;
	              SendData_Set_Command(DRY_ON_NO_BUZZER); //PTC turn On
             
             
             }
			    
                
		  }



}

/****************************************************************
 * 
 * Function Name:
 * Function :function of pointer 
 * 
 * 
****************************************************************/
void Single_Add_RunCmd(void(*addHandler)(void))
{
    single_add_fun = addHandler;   

}

void Single_SendBuzzer_RunCmd(void(*buzzerHandler)(void))
{
	single_buzzer_fun = buzzerHandler;

}
void Single_SendAi_Usart_RunCmd(void(*sendaiHandler)(uint8_t seddat))
{
    sendAi_usart_fun = sendaiHandler;

}

void SplitDispose_Key_RunCmd(void(*keyHandler)(uint8_t dat))
{

  dispose_key = keyHandler;

}


