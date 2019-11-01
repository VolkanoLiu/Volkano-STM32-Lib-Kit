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
} taskList_Typedef;

void taskListInit(TIM_HandleTypeDef *htim, taskList_Typedef *taskList, void (*t)(void));
void taskManagerForeground();
void taskManagerBackground();

#endif