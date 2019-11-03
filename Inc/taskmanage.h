#ifndef __TASKMANAGE_H
#define __TASKMANAGE_H

#include "stm32f4xx_hal.h"

/*
 * 简易的任务管理库
 * 
 * 作者: Volkano Liu
 * 
 * TODO
 */

// 任务结构体
struct taskElement {
  uint32_t period;
  uint32_t count;
  void (*callback)(void);
  struct taskElement *next;
};

typedef struct taskElement taskElement_Typedef;

// 任务队列结构体
// todo: 加入销毁任务的机制
typedef struct {
  taskElement_Typedef* HEAD;
  taskElement_Typedef* TAIL;
  uint32_t taskAmount;
  void (*taskManager)(void);
  TIM_HandleTypeDef* _htim;
} taskList_Typedef;

// 初始化任务队列
void taskListInit(TIM_HandleTypeDef *htim, taskList_Typedef *taskList, void (*t)(void));

// 初始化前台与后台任务
void foregroundTaskInit(taskElement_Typedef *task, taskList_Typedef *taskList, uint32_t period, void (*callback)(void));
void backgroundTaskInit(taskElement_Typedef *task, taskList_Typedef *taskList, uint32_t period, void (*callback)(void));

// 配置任务的相关属性
void taskSetConfig(taskElement_Typedef *task, uint32_t period, void (*callback)(void));
void addTask(taskElement_Typedef *task, taskList_Typedef *taskList);

// 任务管理器
void foregroundTaskManager(taskList_Typedef *taskList);
void backgroundTaskManager(taskList_Typedef *taskList);

#endif