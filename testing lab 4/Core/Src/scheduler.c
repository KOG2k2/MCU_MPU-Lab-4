/*
 * scheduler.c
 *
 *  Created on: Nov 14, 2022
 *      Author: Admin
 */

#include "scheduler.h"

sTasks SCH_tasks_G[SCH_MAX_TASKS];
uint8_t current_index_task = 0;

uint32_t DelaySaved;
sTasks temp;

void swap(sTasks* item1, sTasks* item2){
	temp = *item1;
	*item1 = *item2;
	*item2 = temp;
}

void bubbleSort(){
    for(int i = 0; i < current_index_task; i++){
    	for(int j = i + 1; j < current_index_task; j++){
    		if(SCH_tasks_G[i].Delay > SCH_tasks_G[j].Delay){
    			swap(&SCH_tasks_G[i], &SCH_tasks_G[j]);
    		}
    	}
    }
}

void assignTaskID(){
	for(int index = 0; index < current_index_task; index++){
		SCH_tasks_G[index].TaskID = index;
	}
}

void SCH_Add_Task(void (*pFunction)(), uint32_t DELAY, uint32_t PERIOD){
	if(current_index_task < SCH_MAX_TASKS){
		SCH_tasks_G[current_index_task].pTask = pFunction;
		SCH_tasks_G[current_index_task].Delay = DELAY;
		SCH_tasks_G[current_index_task].Period =  PERIOD;
		SCH_tasks_G[current_index_task].RunMe = 0;

		bubbleSort();
		//selectionSort();
		assignTaskID();

		current_index_task++;
	}
}

void SCH_Dispatch_Tasks(void){
	while(SCH_tasks_G[0].pTask != 0x0000){
		if(SCH_tasks_G[0].RunMe > 0){
			SCH_tasks_G[0].RunMe--;
			(*SCH_tasks_G[0].pTask)();

			for(int i = 1; i < current_index_task; i++){
				SCH_tasks_G[i].Delay -= DelaySaved;
			}

			if(SCH_tasks_G[1].Delay == 0){
				SCH_tasks_G[1].RunMe++;
			}
			if(SCH_tasks_G[0].Period > 0) SCH_Add_Task(SCH_tasks_G[0].pTask, SCH_tasks_G[0].Period, SCH_tasks_G[0].Period);
			SCH_Delete_Tasks(0);
			DelaySaved = SCH_tasks_G[0].Delay;
		}
	}
}

void SCH_Update(void){
	if(SCH_tasks_G[0].Delay > 0) SCH_tasks_G[0].Delay--;
	if(SCH_tasks_G[0].Delay == 0) SCH_tasks_G[0].RunMe++;
}

void SCH_Delete_Tasks(uint32_t taskID){
	for(int i = taskID; i < current_index_task - 1; i++){
		SCH_tasks_G[i] = SCH_tasks_G[i + 1];
	}

	SCH_tasks_G[current_index_task - 1].pTask = 0x0000;
	SCH_tasks_G[current_index_task - 1].Delay = 0;
	SCH_tasks_G[current_index_task - 1].Period = 0;
	SCH_tasks_G[current_index_task - 1].RunMe = 0;

	current_index_task--;
}

void REV_SCH_UP(){
	SCH_Add_Task(RED1_ON, 0, 100);
	SCH_Add_Task(RED3_ON, 100, 100);
	SCH_Add_Task(RED2_ON, 50, 100);
	SCH_Add_Task(RED4_ON, 150, 100);
	SCH_Add_Task(RED5_ON, 200, 100);
	DelaySaved = SCH_tasks_G[0].Delay;
}
