#ifndef __CMD_LINK_H_
#define __CMD_LINK_H_

#include "main.h"
#define  MAX_BUFFER_SIZE   8

extern uint8_t inputBuf[MAX_BUFFER_SIZE];
extern uint8_t outputBuf[8];

typedef enum DISPLAY_STATE_T{
   
   // WIFI_POWER_ON = 0x80,
    WIFI_POWER_OFF=0X81,
    WIFI_MODE_1=0X08,   //state ->normal works
    WIFI_MODE_2=0X18,   //state->sleeping works
    WIFI_KILL_ON=0x04,  //Anion(plasma)
    WIFI_KILL_OFF=0x14,
    WIFI_PTC_ON = 0x02, 
    WIFI_PTC_OFF = 0x12,
    WIFI_ULTRASONIC_ON = 0x01,       //ultrasonic
    WIFI_ULTRASONIC_OFF = 0x11,
    WIFI_WIND_SPEED= 0x90,
    WIFI_TEMPERATURE = 0xA0,
    WIFI_POWER_ON_NORMAL= 0xB0, //WT.EDIT 2025.03.31
    WIFI_POWER_ON_TIMER= 0xB1 //WT.EDIT 2025.03.31


}display_state_t;


typedef enum _copy_cmd{

     phone_power_off = 0xF0,
	 phone_power_on = 0xF1,
	 phone_power_timer_on = 0xFB

}compy_cmd_t;

typedef enum{

     WIFI_CLOUD_FAIL,
	 WIFI_CLOUD_SUCCESS

}wifi_cloud_state;


void SendData_PowerOnOff(uint8_t index);

void SendData_Set_Wifi(uint8_t hdata);
void SendData_Set_Command(uint8_t hdata);

void SendData_Temp_Data(uint8_t tdata);


void SendData_Time_Data(uint8_t tdata);

void SendData_Buzzer(void);

void SendData_Works_Time(uint8_t tdata,uint8_t tdata_2);

void SendData_Remaining_Time(uint8_t tdata,uint8_t tdata_2);
void USART1_Cmd_Error_Handler(void);

void SendData_Copy_Cmd(uint8_t tdata);



#endif 




