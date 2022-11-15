/*
 * led_disp.c
 *
 *  Created on: Nov 14, 2022
 *      Author: Admin
 */

#include "led_disp.h"

void RED1_ON(){
	HAL_GPIO_TogglePin(RED1_GPIO_Port, RED1_Pin);
}
void RED2_ON(){
	HAL_GPIO_TogglePin(RED2_GPIO_Port, RED2_Pin);
}
void RED3_ON(){
	HAL_GPIO_TogglePin(RED3_GPIO_Port, RED3_Pin);
}
void RED4_ON(){
	HAL_GPIO_TogglePin(RED4_GPIO_Port, RED4_Pin);
}
void RED5_ON(){
	HAL_GPIO_TogglePin(RED5_GPIO_Port, RED5_Pin);
}
