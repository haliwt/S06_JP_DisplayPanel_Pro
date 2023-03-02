#include "single_mode.h"
#include "run.h"
#include "smg.h"
#include "gpio.h"
#include "cmd_link.h"
#include "led.h"
#include "key.h"
#include "display.h"




void (*single_ai_fun)(uint8_t cmd);
void (*single_add_fun)(void);
void (*single_buzzer_fun)(void);
void (*sendAi_usart_fun)(uint8_t senddat);
void (*dispose_key)(uint8_t dsdat);
static void Setup_Timer_Times(void);

static void Timing_Handler(void);
static void RunLocal_Smg_Process(void);

static void DisplayPanel_DHT11_Value(void);




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
    
	
	if( run_t.timer_timing_define_flag == timing_success){
		
        
       if(run_t.gTimer_Counter > 59){

	    run_t.gTimer_Counter =0;
		run_t.dispTime_minutes -- ;
	    if(run_t.dispTime_minutes < 0){
		     run_t.dispTime_hours -- ;
			 run_t.dispTime_minutes =59;

			if(run_t.dispTime_hours < 0 ){

	            run_t.dispTime_hours=0;
			
				run_t.dispTime_minutes=0;
				run_t.gTimer_Cmd =0;	 //shut off timer of times

			
				run_t.gPower_On =0 ;
			    run_t.gFan_RunContinue=1;
				run_t.fan_off_60s = 0;
				SendData_PowerOff(0);//shut down 
				
		     }

	     }
		
		Display_GMT();
	  
	  
	   }
	}
    else{
		      if(run_t.gTimes_time_seconds > 59){
			  	
				run_t.gTimes_time_seconds=0;
				run_t.dispTime_minutes++; //1 minute 
                if(run_t.dispTime_minutes> 59){ //1 hour
                   run_t.dispTime_minutes=0;
 					run_t.dispTime_hours++;
                   if(run_t.dispTime_hours > 24){
				    run_t.dispTime_hours =0;
				    }
			   }
               Display_GMT();
		      }
  }

}
   


/******************************************************************************
*
*Function Name:static void Setup_Timer_Times(void)
*Funcion:display setup timer times  //__asm("NOP");//等待1个指令周期，系统主频24M
*Iinput Ref:NO
*Return Ref:NO
*
******************************************************************************/
static void Setup_Timer_Times(void)
{
    
	
	if(run_t.gTimer_Cmd==1){
		
        
       if(run_t.gTimer_Counter > 59){

	    run_t.gTimer_Counter =0;
		run_t.dispTime_minutes -- ;
	    if(run_t.dispTime_minutes < 0){
		     run_t.dispTime_hours -- ;
			 run_t.dispTime_minutes =59;

			if(run_t.dispTime_hours < 0 ){

	            run_t.dispTime_hours=0;
			
				run_t.dispTime_minutes=0;
				run_t.gTimer_Cmd =0;	 //shut off timer of times

			
				run_t.gPower_On =0 ;
			    run_t.gFan_RunContinue=1;
				run_t.fan_off_60s = 0;
				SendData_PowerOff(0);//shut down 
				
		     }

	     }
		
			Display_GMT();
	  
	  
	   }
	}
    else{
		      if(run_t.gTimes_time_seconds > 59){
			  	
				run_t.gTimes_time_seconds=0;
				run_t.dispTime_minutes++; //1 minute 
                if(run_t.dispTime_minutes> 59){ //1 hour
                   run_t.dispTime_minutes=0;
 					run_t.dispTime_hours++;
                   if(run_t.dispTime_hours > 24){
				    run_t.dispTime_hours =0;
				    }
			   }
               Display_GMT();
		      }
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
   	
       RunLocal_Smg_Process();//RunKeyOrder_Handler();
       
	
	   if(run_t.temperature_set_flag ==1 && run_t.gTimer_temp_delay >59){
               run_t.gTimer_temp_delay =0;
		 
		  
		  if(run_t.wifi_set_temperature <= run_t.gReal_humtemp[1] || run_t.gReal_humtemp[1] >39){//envirment temperature
	  
				run_t.gDry = 0;

		        SendData_Set_Command(DRY_OFF);//PTC turn off
			    
			    
                
		  }
		  else if((run_t.wifi_set_temperature -3) > run_t.gReal_humtemp[1] ||  run_t.gReal_humtemp[1] < 37){
	  
		     run_t.gDry = 1;
	         SendData_Set_Command(DRY_ON); //PTC turn On
				 
		  }
	  
	    
	  }
	   
   }

   //set up timrer timing how many, temperature ? 
   Set_Timer_Temperature_Fun();




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
    if(run_t.gPower_On ==1){
		

	 Panel_Led_OnOff_Function() ;//Lcd_PowerOn_Fun();
	 Timing_Handler();
	 DisplayPanel_DHT11_Value();


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


