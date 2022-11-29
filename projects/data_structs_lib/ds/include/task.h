#ifndef TASK_H
#define TASK_H

#include <time.h>
#include <stddef.h>

#include "uid.h"

struct task
{
	ilrd_uid_t uid;
	time_t time_exe;
	size_t time_interval;
	int(*task_func)(void *param);
	void *param;
};



typedef struct task task_t;



/***************************************************************************************
                                        				create
****************************************************************************
DESCRIPTION: a function that creates a new task for the schedular
	
ARGUMENTS: 
	time interval - how often would i want the task to run
	task_func - what the tasks needs to acmplish
	param - the parameters of the task
	
RETURN VALUE
 the function returns a pointer to the new task
	
complexity: O(1) 
**************************************************************************************/
task_t *TaskCreate(size_t time_interval, int(*task_func)(void *param), void *param);




/*****************************************************************************************************************************************
                                        				Destroy
******************************************************************************************************************************************
DESCRIPTION: destroys a task
	
ARGUMENTS: a pointer to the task
	
RETURN VALUE: non
	
complexity: O(1)
****************************************************************************************************************************************/
void TaskDestroy(task_t *task);






/****************************************************************************************************************************************
                                        				Run
*****************************************************************************************************************************************
DESCRIPTION: executes the task func of a task
	
ARGUMENTS: the task
	
RETURN VALUE: 0 if sucsseds, 1 for stopping the task from running again
	
complexity O(1)
****************************************************************************************************************************************/
int TaskRun(task_t *task);






/**********************************************************************
                                        				GetExeTime
**************************************************************************
DESCRIPTION:
	
ARGUMENTS:
	
RETURN VALUE:
	
complexity:
****************************************************************************************************************************************/
time_t TaskGetExeTime(const task_t *task);






/****************************************************************************************************************************************
                                        				UpdateTimeToRun
*****************************************************************************************************************************************
DESCRIPTION
	
ARGUMENTS
	
RETURN VALUE
	
complexity 
****************************************************************************************************************************************/
void TaskUpdateTimeToRun(task_t *task);





/*********************************************************************
                                        				GetUid
***********************************************************************
DESCRIPTION
	
ARGUMENTS
	
RETURN VALUE
	
complexity 
****************************************************************************************************************************************/
ilrd_uid_t TaskGetUid(const task_t *task);





/****************************************************************************************************
                                        				Cmp
*****************************************************************************************************************************************
DESCRIPTION
	
ARGUMENTS
	
RETURN VALUE
	
complexity 
****************************************************************************************************************************************/
int TaskCmp(const void *enterence_task1, const void *task2_in_schedular);

int TaskCmpHeap(const void *task1, const void *task2);






#endif /*TASK_H*/









