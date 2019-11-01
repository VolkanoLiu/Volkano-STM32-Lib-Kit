#ifndef __TASKMANAGE_H
#define __TASKMANAGE_H

#include "stm32f4xx_hal.h"

struct taskElement {
  uint32_t period;
  uint32_t count;
  void (*callback)(void);
  struct taskElement *next;
};

typedef struct taskElement taskElement_Typedef;

typedef struct {
  taskElement_Typedef* HEAD;
  taskElement_Typedef* TAIL;
  uint32_t taskAmount;
  void (*taskManager)(void);
  TIM_HandleTypeDef* _htim;
} taskList_Typedef;

void taskListInit(TIM_HandleTypeDef *htim, taskList_Typedef *taskList, void (*t)(void));

void foregroundTaskInit(taskElement_Typedef *task, taskList_Typedef *taskList, uint32_t period, void (*callback)(void));
void backgroundTaskInit(taskElement_Typedef *task, taskList_Typedef *taskList, uint32_t period, void (*callback)(void));

void taskSetConfig(taskElement_Typedef *task, uint32_t period, void (*callback)(void));
void addTask(taskElement_Typedef *task, taskList_Typedef *taskList);

void foregroundTaskManager(taskList_Typedef *taskList);
void backgroundTaskManager(taskList_Typedef *taskList);

#endif