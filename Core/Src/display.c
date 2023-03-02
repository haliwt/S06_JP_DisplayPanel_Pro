#include "display.h"
#include "smg.h"
#include "cmd_link.h"
#include "run.h"
#include "key.h"
#include "led.h"
//#include "single_mode.h"


/*************************************************************
 * 
 * Function Name:void DisplaySMG_LED(void)
 * Function :
 * 
*************************************************************/
void DisplaySMG_LED(void)
{
   static uint8_t m,n,p,q;
    if(run_t.gPower_On==1){

		SMG_POWER_ON()	;


		m = (run_t.dispTime_hours /10) ;
		n=	(run_t.dispTime_hours%10); 
		p = (run_t.dispTime_minutes/10);
		q=  (run_t.dispTime_minutes%10);



		TM1639_Write_4Bit_Time(m,n,p,q,0) ; //timer is default 12 hours "12:00"
		panel_led_fun();//Display_Function_OnOff();
		//KeyLed_Power_On();

   }

		   
}


/**********************************************************************
*
*Functin Name: void Display_DHT11_Value(void)
*Function : Timer of key be pressed handle
*Input Ref:  key of value
*Return Ref: NO
*
**********************************************************************/
void Display_DHT11_Value(void)
{
    
  static uint8_t hum1,hum2; 
  static uint8_t temp1,temp2;

	hum1 =  run_t.gReal_humtemp[0]/10 %10;  //Humidity 
	hum2 =  run_t.gReal_humtemp[0]%10;

	temp1 = run_t.gReal_humtemp[1]/10 %10;  // temperature
	temp2 = run_t.gReal_humtemp[1]%10;

	TM1639_Write_2bit_TempData(temp1,temp2);
	TM1639_Write_2bit_HumData(hum1,hum2);


}  


/**********************************************************************
*
*Functin Name: void DisplayTiming_KEY_Add_Subtract_Fun(void)
*Function : Timer of key be pressed handle
*Input Ref:  key of value
*Return Ref: NO
*
**********************************************************************/
void DisplayTiming_KEY_Add_Subtract_Fun(void)
{
      
	  static uint8_t m,n,p,q;

	if(run_t.gPower_On==1){
    
    if(run_t.gMode_flag==1){ // set up timer of  timimg value
		
           
			p=run_t.dispTime_hours  /10%10;
		    q=run_t.dispTime_hours  %10;
			m = run_t.dispTime_minutes  /10%10;
			n=	run_t.dispTime_minutes %10;
	
			TM1639_Write_4Bit_Time(p,q,m,n,0) ; // timer   mode  "H0: xx"
			
			
            run_t.add_key_times =0;
			run_t.dec_key_times =0;
		
		
	 }
	 else{

        run_t.gMode_flag=0;
		m= (run_t.gTemperature /10) %10;
        n =  run_t.gTemperature %10;
	    TM1639_Write_2bit_TempData(m,n);

	 }
	 
	
	

    }
 }
void Display_GMT(void)
{ 
    static uint8_t m,n,p,q;
	m = run_t.dispTime_hours /10 %10;
	n=	run_t.dispTime_hours%10; 
	p = run_t.dispTime_minutes/10 %10;
	q=  run_t.dispTime_minutes%10;
	TM1639_Write_4Bit_Time(m,n,p,q,0) ; //timer is default 12 hours "12:00"


}

void SetUp_Temperature_Value(void)
{
    static uint8_t m,n;
		m= (run_t.gTemperature /10) %10;
        n =  run_t.gTemperature %10;
	 if(run_t.gTimer_led_500ms < 41)
          TM1639_Write_2bit_SetUp_TempData(m,n,0);
     else if(run_t.gTimer_led_500ms > 39 && run_t.gTimer_led_500ms < 81)
	 	   TM1639_Write_2bit_SetUp_TempData(m,n,1);
	 else{
	 	run_t.gTimer_led_500ms=0;
		run_t.gSet_up_times ++ ;
	 }
}


