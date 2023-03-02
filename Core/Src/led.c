#include "led.h"
#include "run.h"

void (*panel_led_fun)(void);


static void DRY_LED_OnOff(uint8_t sel);
static void PLASMA_LED_OnOff(uint8_t sel);

static void TIME_LED_OnOff(uint8_t sel);

static void Power_BreathOnOff(uint8_t sel);



//void AI_LED_OnOff(uint8_t sel)
//{
//    if(sel==0){
//		LED_WIFI_ON();	
//
//	}
//	else
//		LED_WIFI_OFF();		
//}

static void DRY_LED_OnOff(uint8_t sel)
{
   if(sel==0){
	 LED_DRY_ON();
   }
   else 
   	LED_DRY_OFF();

}
static void PLASMA_LED_OnOff(uint8_t sel)
{
	if(sel==0){
		LED_PLASMA_ON();
   }
   else
   	 LED_PLASMA_OFF();

}

static void TIME_LED_OnOff(uint8_t sel)
{
    if(sel==0)LED_TIME_ON();
	else  LED_TIME_OFF();


}

void KeyLed_Power_On(void)
{
   LED_POWER_ON();
   LED_TIME_ON();


}


void ALL_LED_Off(void)
{
   LED_PLASMA_OFF();
   LED_WIFI_OFF();
  LED_DRY_OFF();
  LED_WIFI_OFF();
  LED_TIME_OFF();


}



/*******************************************************************************************
 	*
 	* Function Name:void Panel_Led_OnOff_Function(void)
 	* Function :panel of led turn on or off which key function 
 	* Input Ref:NO
 	* Return Ref:NO
 	* 
*******************************************************************************************/  
void Panel_Led_OnOff_Function(void)
{
	
	 
	 if(run_t.gWifi == 1){
		
		  LED_WIFI_ON();
		  
	  }
	  else{
	  	
	    
		 if(run_t.gTimer_led_500ms > 0 && 	run_t.gTimer_led_500ms< 6){
		     LED_WIFI_OFF();

		 }
		 else if(run_t.gTimer_led_500ms>5 && run_t.gTimer_led_500ms< 11){
		 	 LED_WIFI_ON();
		     

        }
		else{
		  	run_t.gTimer_led_500ms=0;
		     LED_WIFI_OFF();

		}

	  }
	 
	  
    if(run_t.gDry==0){
		 run_t.gFan_off_flag=0;
	     DRY_LED_OnOff(0);

     }
	 else{
	    DRY_LED_OnOff(1);

	 }

	 if(run_t.gPlasma==0){
	 	 run_t.gFan_off_flag=0;
	     PLASMA_LED_OnOff(0);

     }
	 else{
	   PLASMA_LED_OnOff(1);

	 }

	 if(run_t.gFan == 0 &&  run_t.gFan_off_flag ==0){
         LED_FAN_ON();
	 }
	 else{
         LED_FAN_OFF();
	 }

	

	
 
}
/***************************************************************
*
*Function Name: void LED_TempHum(void)
*Function : display temperature and humidity and times led 
*
*
*
**************************************************************/
static void Power_BreathOnOff(uint8_t sel)
{
    
     static uint32_t k;
   
    k++;

	if(k<40000){

	LED_POWER_ON();



	}
          

	if(k>40000 && k <80000){

	    LED_POWER_OFF();

	}
	if(k>80000 && k< 120000){

	  LED_POWER_TOGGLE();


	}

	if(k>120000){

        k=0;
	}

}




void Breath_Led(void)
{
    
   
     Power_BreathOnOff(0);
   
}


void Panel_Led_OnOff_RunCmd(void (*panelledHandler)(void))
{

	 panel_led_fun= panelledHandler;
}
