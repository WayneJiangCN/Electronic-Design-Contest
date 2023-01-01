#ifndef __HW_key_H__
#define __HW_key_H__

#include "main.h"
//#include "stm32f1xx_hal.h"
#include <string.h>

char KEY_SCAN(void);
char KEY_ROW_SCAN(void);
void HW_KEY_FUNCTION(void);

#define KEY_CLO0_OUT_LOW  HAL_GPIO_WritePin(KEY_col0_GPIO_Port,KEY_col0_Pin,GPIO_PIN_RESET) 
#define KEY_CLO1_OUT_LOW  HAL_GPIO_WritePin(KEY_col1_GPIO_Port,KEY_col1_Pin,GPIO_PIN_RESET)
#define KEY_CLO2_OUT_LOW  HAL_GPIO_WritePin(KEY_col2_GPIO_Port,KEY_col2_Pin,GPIO_PIN_RESET)
#define KEY_CLO3_OUT_LOW  HAL_GPIO_WritePin(KEY_col3_GPIO_Port,KEY_col3_Pin,GPIO_PIN_RESET)

#define KEY_CLO0_OUT_HIGH  HAL_GPIO_WritePin(KEY_col0_GPIO_Port,KEY_col0_Pin,GPIO_PIN_SET) 
#define KEY_CLO1_OUT_HIGH  HAL_GPIO_WritePin(KEY_col1_GPIO_Port,KEY_col1_Pin,GPIO_PIN_SET)
#define KEY_CLO2_OUT_HIGH  HAL_GPIO_WritePin(KEY_col2_GPIO_Port,KEY_col2_Pin,GPIO_PIN_SET)
#define KEY_CLO3_OUT_HIGH  HAL_GPIO_WritePin(KEY_col3_GPIO_Port,KEY_col3_Pin,GPIO_PIN_SET)

#endif