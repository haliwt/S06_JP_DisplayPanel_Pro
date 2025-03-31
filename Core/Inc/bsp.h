#ifndef __BSP_H_
#define __BSP_H_
#include "main.h"



#include "main.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "smg.h"
#include "cmd_link.h"
#include "run.h"
#include "key.h"
#include "led.h"
#include "single_mode.h"
#include "display.h"
#include "interrupt_manager.h"






typedef struct __PROCESS_T{

  uint8_t power_on_flag ;
  uint8_t key_power_off_sound_flag;
  uint8_t wifi_set_timer_timing_flag;
  uint8_t copy_cmd_flag;
  uint8_t manual_shutoff_ptc_flag ;

  uint8_t gTimer_turn_on_led;
  uint8_t gTimer_copy_cmd_couter;


}process_t;



extern process_t g_pro;


void decode_process_handler(void);

void power_on_run_led_handler(void);


void answer_cmd_form_mainboard(void);


#endif 

