#include "led.h"
#include "run.h"

void (*panel_led_fun)(void);

void AI_LED_OnOff(uint8_t sel);
void DRY_LED_OnOff(uint8_t sel);
void STER_LED_OnOff(uint8_t sel);
void TIME_LED_OnOff(uint8_t sel);

static void Power_BreathOnOff(uint8_t sel);



//void AI_LED_OnOff(uint8_t sel)
//{
//    if(sel==0){
//		LED_WIFI_ON();	

//	}
//	else
//		LED_WIFI_OFF();		
//}

//void DRY_LED_OnOff(uint8_t sel)
//{
//   if(sel==0){
//	 LED_DRY_ON();
//   }
//   else 
//   	LED_DRY_OFF();

//}
//void STER_LED_OnOff(uint8_t sel)
//{
//	if(sel==0){
//		LED_STER_ON();
//   }
//   else
//   	 LED_STER_OFF();

//}

//void TIME_LED_OnOff(uint8_t sel)
//{
//    if(sel==0)LED_TIME_ON();
//	else  LED_TIME_OFF();


//}


//void KeyLed_Power_On(void)
//{
//   LED_POWER_ON();
//   LED_TIME_ON();


//}


//void ALL_LED_Off(void)
//{
//   LED_STER_OFF();
//   LED_WIFI_OFF();
//  LED_DRY_OFF();
//  LED_WIFI_OFF();
//  LED_TIME_OFF();


//}

//void AI_Auto_Stop(void)
//{
//	LED_STER_OFF();
//	LED_WIFI_OFF();
//	LED_DRY_OFF();
//	
//}

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
	
//	 
//	  if(){
//		
//		  LED_AI_ON();
//		  run_t.gFan_off_flag=0;
//	  }
//	  else{
//	     LED_WIFI_OFF();
//
//	  }
	 
	  
//    if(run_t.gDry==0){
//		 run_t.gFan_off_flag=0;
//	     DRY_LED_OnOff(0);

//     }
//	 else{
//	    DRY_LED_OnOff(1);

//	 }

//	 if(run_t.gPlasma==0){
//	 	 run_t.gFan_off_flag=0;
//	     STER_LED_OnOff(0);

//     }
//	 else{
//	   STER_LED_OnOff(1);

//	 }

//	 if(run_t.gFan == 0 &&  run_t.gFan_off_flag ==0){
//         LED_FAN_ON();
//	 }
//	 else{
//         LED_FAN_OFF();
//	 }

//	

//	
// 
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
   // LED_POWER_OFF(); 

	 
}


void Panel_Led_OnOff_RunCmd(void (*panelledHandler)(void))
{

	 panel_led_fun= panelledHandler;
}
