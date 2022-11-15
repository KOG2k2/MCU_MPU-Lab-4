/*
 * scheduler.h
 *
 *  Created on: Nov 14, 2022
 *      Author: Admin
 */

#ifndef INC_SCHEDULER_H_
#define INC_SCHEDULER_H_

#include "main.h"
#include "led_disp.h"
#include <stdint.h>

typedef struct{
	void (*pTask)(void);
	uint32_t 	Delay;
	uint32_t 	Period;
	uint8_t 	RunMe;

	uint32_t 	TaskID;
}sTasks;

#define SCH_MAX_TASKS	40

void SCH_Init();

void swap(sTasks* item1, sTasks* item2);
void bubbleSort();
void assignTaskID();

void SCH_Add_Task(void (*pFunction)(), uint32_t DELAY, uint32_t PERIOD);

void SCH_Update(void);
void SCH_Dispatch_Tasks(void);
void SCH_Delete_Tasks(uint32_t taskID);
void REV_SCH_UP();

#endif /* INC_SCHEDULER_H_ */
