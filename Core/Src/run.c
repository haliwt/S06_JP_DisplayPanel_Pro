#include "run.h"
#include "smg.h"
#include "gpio.h"
#include "cmd_link.h"
#include "led.h"
#include "display.h"

RUN_T run_t;

uint8_t power_on_off_flag;

void Power_Off(void);

static void Receive_Wifi_Cmd(uint8_t cmd);



/**********************************************************************************************************
**
*Function Name:static void notifyStatusToHost(uint8_t lightNum,uint8_t filterNum,uint8_t unionNum)
*Function : 
*Input Ref:lightNum--LED ,filterNum -filter number, unionNum - smart menu number
*Return Ref:NO
*
*********************************************************************************************************/
void Decode_Handler(void)
{
   
   Receive_MainBoard_Data_Handler(run_t.wifi_orderByMainboard_label);
  
}



/**********************************************************************
*
*Functin Name: void Display_DHT11_Value(void)
*Function : Timer of key be pressed handle
*Input Ref:  key of value
*Return Ref: NO
*
**********************************************************************/
void Power_Off(void)
{
    	 if(run_t.gPower_On ==0){

			run_t.gPower_On =0xff;
			Smg_AllOff();

			run_t.gPlasma=0;
			run_t.gDry=0;
			run_t.gUltrasonic =0;
			run_t.gTimer_Cmd=0; //timer of command "1"->timer is start
			//  run_t.dispTime_hours=0;
			//  run_t.dispTime_minutes=0;
			//  run_t.gTemperature_timer_flag=0;
			//run_t.dispTime_hours=12;

				
		}
		Breath_Led();
		SMG_POWER_OFF()	;
		
		
	      
}

void DisplayTimer_Timing(void)
{
      static uint8_t m,n,p,q;
      m = run_t.dispTime_hours /10 ;
	  n=  run_t.dispTime_hours %10; 
	  p = run_t.dispTime_minutes /10;
	  q=  run_t.dispTime_minutes %10;
	  TM1639_Write_4Bit_Time(m,n,p,q,0) ; //timer is default 12 hours "12:00"

  
}

/**********************************************************************
*
*Functin Name: void Receive_MainBoard_Data_Handler(run_t.single_data)
*Function : run order from main command 
*Input Ref:  run_t.single_dat is command 
*Return Ref: NO
*
**********************************************************************/
void Receive_MainBoard_Data_Handler(uint8_t cmd)
{
	static uint8_t m,n,p,q;
	static uint8_t hum1,hum2,temp1,temp2; 
	
    switch(cmd){


	 case WIFI_CMD:
	 	 
	 	 Receive_Wifi_Cmd(run_t.wifiCmd[0]);
	 break;

	 case WIFI_TEMP: //set temperature value
	       if(run_t.gPower_On ==1){
		   	   run_t.set_temperature_flag=1;
           run_t.gTimer_key_temp_timing=0;
        		m= run_t.wifi_set_temperature /10 ;
			  		n= run_t.wifi_set_temperature %10;
		   
	        TM1639_Write_2bit_SetUp_TempData(m,n,0);
			}

	 break;

	 case PANEL_DATA:
	   
        if(run_t.gPower_On ==1){
        hum1 =  run_t.gReal_humtemp[0]/10 %10;  //Humidity 
        hum2 =  run_t.gReal_humtemp[0]%10;
        
        temp1 = run_t.gReal_humtemp[1]/10 %10;  // temperature
        temp2 = run_t.gReal_humtemp[1]%10;

         //temperature 
          TM1639_Write_2bit_TempData(temp1,temp2);
	      TM1639_Write_2bit_HumData(hum1,hum2);
	
        }

      break;

       case WIFI_BEIJING_TIME: 
         if(run_t.wifi_connect_flag ==1 && run_t.gPower_On==1){
           if(run_t.timer_timing_define_flag==timing_not_definition && run_t.temp_set_timer_timing_flag==0){
               
			 m=(run_t.dispTime_hours ) /10;
	        n = (run_t.dispTime_hours ) %10;;
			
            p= (run_t.dispTime_minutes )/10;
            q = (run_t.dispTime_minutes )%10;
			

	       TM1639_Write_4Bit_Time(m,n,p,q,0) ; // timer   mode  "H0: xx"
	      }
         }
		    
        
 
      break;

      case WIFI_SET_TIMING:
        
       
            if(run_t.dispTime_hours !=0){
            run_t.timer_timing_define_flag = timing_success ;
            run_t.Timer_model_flag = 1;
            run_t.dispTime_minutes = 0;
            
             m=(run_t.dispTime_hours ) /10;
	       

			 n= (run_t.dispTime_hours ) %10;;
			
	   
              TM1639_Write_4Bit_Time(m,n,p,q,0) ; // timer   mode  "H0: xx"
        }

      break;

	}


}
/**********************************************************************
*
*Functin Name: void Receive_ManiBoard_Cmd(uint8_t cmd)
*Function :  wifi recieve data
*Input Ref:  receive wifi send order
*Return Ref: NO
*
**********************************************************************/
static void Receive_Wifi_Cmd(uint8_t cmd)
{
	switch(cmd){


		   case WIFI_POWER_ON: //turn on 
		 	
            //  single_buzzer_fun();
              run_t.wifi_send_buzzer_sound = WIFI_POWER_ON_ITEM;
              Power_On_Fun();
			  cmd=0xff;

	         break;

			 case WIFI_POWER_OFF: //turn off 
                
			    //single_buzzer_fun();
			   run_t.wifi_send_buzzer_sound = WIFI_POWER_OFF_ITEM;
				
			    Power_Off_Fun();
				
              cmd=0xff;

			 break;

			 case WIFI_KILL_ON: //kill turn on plasma
			  if(run_t.gPower_On==1){
               run_t.gPlasma = 1;
			        
             } 
			 break;

			 case WIFI_KILL_OFF: //kill turn off
                if(run_t.gPower_On==1){
			 	  run_t.gPlasma =0;
				  
		          
                }
			 break;

			 case WIFI_PTC_ON://dry turn on
                if(run_t.gPower_On==1){
			        run_t.gDry =1;
                    
                 
                }
			 break;

			 case WIFI_PTC_OFF: //dry turn off
               
			 	if(run_t.gPower_On==1){
					run_t.gDry=0;
                 
		           
			 	}

			 break;

			 case WIFI_SONIC_ON:  //drive bug
		
				 if(run_t.gPower_On==1){		   
				  run_t.gUltrasonic =1; //turn on 
			
				 
			    }

			 break;

			 case WIFI_SONIC_OFF: //drive bug turn off
			 	if(run_t.gPower_On==1){
				    run_t.gUltrasonic=0;
					
			   }
			 break;


	         default :
                  cmd =0;
			 break;

			 
        }
   
}

void Power_On_Fun(void)
{
                
   static uint8_t hour_decade,hour_unit;

	run_t.gPower_On=1;

	run_t.power_key =1;
	


	run_t.gPlasma=1;
	run_t.gDry =1;
	run_t.gBug =1;
	run_t.time_led_flag=1;
	run_t.gUltrasonic =1;
	
	run_t.temperature_set_flag = 0; //WT.EDIT 2023.01.31
    run_t.wifi_set_temp_flag=0; // //WT.EDIT 2023.01.31
    run_t.disp_wind_speed_grade =3;
	        
	run_t.gTimer_minute_Counter =0;
	run_t.wifi_send_buzzer_sound=0xff;
     Power_ON_Led();
	if(power_on_off_flag==0){
	     run_t.dispTime_hours=12;
		 
	}

	 hour_decade=(run_t.dispTime_hours ) /10;
     hour_unit=(run_t.dispTime_hours ) %10;
	 SMG_POWER_ON(); //WT.EDIT 2023.03.02
     
	 TM1639_Write_4Bit_Time(hour_decade,hour_unit,0x0,0x0,0);


}

/************************************************************************
	*
	*Function Name: static void Power_Off_Fun(void)
	*
	*
	*
	*
************************************************************************/
void Power_Off_Fun(void)
{
	
 
		run_t.gPlasma=0;
		run_t.gDry =0;
		run_t.gBug =0;
		
		run_t.wifi_led_fast_blink_flag=0;
      
		run_t.timer_timing_define_flag = timing_not_definition;

		
	
		run_t.power_key =2;
	
		run_t.disp_wind_speed_grade =1;	
		run_t.gPower_On=0;
		run_t.fan_off_60s =0;
		power_on_off_flag=1;

   
		
           

       
		Power_Off_Led_Off();

  
} 

