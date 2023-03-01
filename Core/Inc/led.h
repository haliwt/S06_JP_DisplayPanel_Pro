#ifndef __LED_H_
#define __LED_H_
#include "main.h"

#define LED_POWER_PIN     	GPIO_PIN_12
#define LED_POWER_PORT      GPIOB

#define LED_STER_PIN        GPIO_PIN_8
#define LED_DRY_PIN       	GPIO_PIN_9  
#define LED_GPIOA     	 	GPIOA


#define LED_WIFI_Pin                     GPIO_PIN_6
#define LED_WIFI_GPIO_Port               GPIOC


#define  SMG_POWER_PIN			         GPIO_PIN_1
#define  SMG_POWER_PORT       		     GPIOA





#define LED_POWER_ON()				HAL_GPIO_WritePin(LED_POWER_PORT, LED_POWER_PIN,GPIO_PIN_SET)
#define LED_POWER_OFF()             HAL_GPIO_WritePin(LED_POWER_PORT, LED_POWER_PIN,GPIO_PIN_RESET)

#define LED_WIFI_ON()			  HAL_GPIO_WritePin(LED_AI_GPIO_Port, LED_AI_Pin,GPIO_PIN_SET)
#define LED_WIFI_OFF()    	      HAL_GPIO_WritePin(LED_AI_GPIO_Port, LED_AI_Pin,GPIO_PIN_RESET)

#define LED_DRY_ON()			  HAL_GPIO_WritePin(LED_GPIOA, LED_DRY_PIN,GPIO_PIN_SET)
#define LED_DRY_OFF()             HAL_GPIO_WritePin(LED_GPIOA, LED_DRY_PIN,GPIO_PIN_RESET)

#define LED_TIME_ON()			   HAL_GPIO_WritePin(LED_TIME_GPIO_Port, LED_TIME_Pin,GPIO_PIN_SET)
#define LED_TIME_OFF()             HAL_GPIO_WritePin(LED_TIME_GPIO_Port, LED_TIME_Pin,GPIO_PIN_RESET)

#define LED_STER_ON()				HAL_GPIO_WritePin(LED_GPIOA, LED_STER_PIN,GPIO_PIN_SET)
#define LED_STER_OFF()             HAL_GPIO_WritePin(LED_GPIOA, LED_STER_PIN,GPIO_PIN_RESET)

#define LED_FAN_ON()  				HAL_GPIO_WritePin(LED_FAN_GPIO_Port, LED_FAN_Pin,GPIO_PIN_SET)
#define LED_FAN_OFF()				HAL_GPIO_WritePin(LED_FAN_GPIO_Port, LED_FAN_Pin,GPIO_PIN_RESET)


//control SMG supply power 
#define SMG_POWER_ON()				HAL_GPIO_WritePin(SMG_POWER_PORT , SMG_POWER_PIN,GPIO_PIN_SET)
#define SMG_POWER_OFF()             HAL_GPIO_WritePin(SMG_POWER_PORT , SMG_POWER_PIN,GPIO_PIN_RESET)

#define LED_POWER_TOGGLE()            HAL_GPIO_TogglePin(LED_POWER_PORT, LED_POWER_PIN)





extern void (*panel_led_fun)(void);

void Panel_Led_OnOff_RunCmd(void (*panelledHandler)(void));

//void KeyLed_Power_On(void);


//void ALL_LED_Off(void);

void Panel_Led_OnOff_Function(void);

void AI_Auto_Stop(void);
void Breath_Led(void);









#endif 
