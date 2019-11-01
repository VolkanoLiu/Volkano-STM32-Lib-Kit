#include "taskmanage.h"
#include "main.h"

/**
  * @brief 初始化一个任务队列
  * @param htim 定时器句柄
  * @param taskList 需要被初始化的队列
  * @param t 执行任务队列的函数指针
  */
void taskListInit(TIM_HandleTypeDef *htim, taskList_Typedef *taskList, void (*t)(void))
{
  taskList->_htim = htim;
  taskList->HEAD = NULL;
  taskList->TAIL = NULL;
  taskList->taskAmount = 0;
  taskList->taskManager = t;
}

/**
  * @brief 初始化一个前台任务
  * @param task 前台任务
  * @param taskList 任务队列
  * @param period 任务周期
  * @param callback 回调函数
  */
void foregroundTaskInit(taskElement_Typedef *task, taskList_Typedef *taskList, uint32_t period, void (*callback)(void))
{
  taskSetConfig(task, period, callback);
  addTask(task, taskList);
}

/**
  * @brief 初始化一个后台任务
  * @param task 后台任务
  * @param taskList 任务队列
  * @param period 任务周期
  * @param callback 回调函数
  */
void backgroundTaskInit(taskElement_Typedef *task, taskList_Typedef *taskList, uint32_t period, void (*callback)(void))
{
  taskSetConfig(task, period, callback);
  addTask(task, taskList);
}

void taskSetConfig(taskElement_Typedef *task, uint32_t period, void (*callback)(void))
{
  task->period = period;
  task->count = 0;
  task->callback = callback;
  task->next = NULL;
}

void addTask(taskElement_Typedef *task, taskList_Typedef *taskList)
{
  if (taskList->HEAD == NULL) {
    taskList->HEAD = task;
    taskList->TAIL = task;
  } else {
    taskList->TAIL->next = task;
    taskList->TAIL = task;
  }
  task->next = NULL;
  taskList->taskAmount++;
}

void foregroundTaskManager(taskList_Typedef *taskList)
{
  taskElement_Typedef *current_taskElement = taskList->HEAD;
  while (current_taskElement != NULL) {
    current_taskElement->count++;
    if (current_taskElement->count == current_taskElement->period) {
      if (current_taskElement->callback != NULL) {
        current_taskElement->callback();
      }
      current_taskElement->count = 0;
    }
    current_taskElement = current_taskElement->next;
  }
}

void backgroundTaskManager(taskList_Typedef *taskList)
{
  // todo
}

// 重写 HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
// 在其他文件中重写
/*
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  if(htim = SOME_TIMER)
  {

  }
}
*/
