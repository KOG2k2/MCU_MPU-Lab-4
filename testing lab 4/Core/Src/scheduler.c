/*
 * scheduler.c
 *
 *  Created on: Nov 14, 2022
 *      Author: Admin
 */

#include "scheduler.h"

sTasks SCH_tasks_G[SCH_MAX_TASKS];
uint8_t current_index_task = 0;


uint8_t addpos = 0;

void SCH_shifting(int index){
	for(int i = current_index_task - 1; i > index; i--){
		SCH_tasks_G[i] = SCH_tasks_G[i - 1];
	}

	//Emptying Task
	SCH_tasks_G[index].pTask = 0x0000;
	SCH_tasks_G[index].Delay = 0;
	SCH_tasks_G[index].Period = 0;
	SCH_tasks_G[index].RunMe = 0;
	SCH_tasks_G[index].TaskID = 0;
}

void SCH_Add_Task(void (*pFunction)(), uint32_t DELAY, uint32_t PERIOD){
	sTasks taskTemp;
	taskTemp.pTask = pFunction;
	taskTemp.Delay = DELAY;
	taskTemp.Period =  PERIOD;
	taskTemp.RunMe = 0;
	taskTemp.TaskID = current_index_task;

	if(current_index_task < SCH_MAX_TASKS){
		if(current_index_task == 0){
			SCH_tasks_G[0] = taskTemp;
			current_index_task++;
			return;
		}
		for(; addpos < current_index_task; addpos++){
			if(taskTemp.Delay > SCH_tasks_G[addpos].Delay) taskTemp.Delay -= SCH_tasks_G[addpos].Delay;
		}

		current_index_task++;
		SCH_shifting(addpos);
		SCH_tasks_G[addpos] = taskTemp;
		SCH_tasks_G[addpos + 1].Delay -= SCH_tasks_G[addpos].Delay;
	}
}

void SCH_Dispatch_Tasks(void){
	while(SCH_tasks_G[0].pTask != 0x0000){
		if(SCH_tasks_G[0].RunMe > 0){
			SCH_tasks_G[0].RunMe--;
			(*SCH_tasks_G[0].pTask)();

			if(SCH_tasks_G[0].Period != 0) SCH_Add_Task(SCH_tasks_G[0].pTask, SCH_tasks_G[0].Period, SCH_tasks_G[0].Period);
			SCH_Delete_Tasks(0);
		}
	}
}

void SCH_Update(void){
	if(SCH_tasks_G[0].Delay > 0) SCH_tasks_G[0].Delay--;
	if(SCH_tasks_G[0].Delay == 0) SCH_tasks_G[0].RunMe++;
}

void SCH_Delete_Tasks(uint32_t taskIDX){
	if(taskIDX < current_index_task){
		for(int i = taskIDX; i < current_index_task - 1; i++){
			SCH_tasks_G[i] = SCH_tasks_G[i + 1];
		}

		SCH_tasks_G[current_index_task - 1].pTask = 0x0000;
		SCH_tasks_G[current_index_task - 1].Delay = 0;
		SCH_tasks_G[current_index_task - 1].Period = 0;
		SCH_tasks_G[current_index_task - 1].RunMe = 0;
		SCH_tasks_G[current_index_task - 1].TaskID = 0;

		current_index_task--;
	}
}

void REV_SCH_UP(){
	SCH_Add_Task(RED1_ON, 0, 50);
	SCH_Add_Task(RED2_ON, 50, 150);
	SCH_Add_Task(RED3_ON, 100, 100);
	SCH_Add_Task(RED4_ON, 150, 200);
	SCH_Add_Task(RED5_ON, 200, 250);
}
