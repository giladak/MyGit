/****************************************************************

	dev : Gilad Kahn
	rev: Idan Matalon
	status: approved
	date: 23.1.22
*********************************************************************/	


#include <stdio.h>  /*size_t, for, while*/
#include <stdlib.h> /*malloc, free*/
#include <assert.h> /*assert*/

#include "p_queue.h"
#include "sorted_list.h"
#include "task.h"
#include "scheduler.h"

#define RUN 0



#define EMPTY 0
#define STOP 1
#define ERROR 2

/* 
	flag can get:
0 - for run
1 - for stop
2 - clear while run, erase schedular -> task

*/

struct scheduler
{
	priority_queue_t *queue;
	task_t *task;
	int flag;  
};


static int RemoveCmp(const void *task, const void *param);



/************************create***********************/

scheduler_t *SchedulerCreate()
{
	scheduler_t *new_scheduler = (scheduler_t *)malloc(sizeof(scheduler_t));
	
	if (NULL == new_scheduler)
	{
		return (NULL);
	}
	
	new_scheduler -> queue = PriorityQueueCreate(TaskCmp);
	
	if( NULL == new_scheduler -> queue)
	{
		free (new_scheduler);
		return (NULL);
	}
	
	new_scheduler -> flag = RUN;
	new_scheduler -> task = NULL;
	
	return (new_scheduler);
}


/************************Destroy***********************/


void SchedulerDestroy(scheduler_t *scheduler)
{
	assert(scheduler);
	
	SchedulerClear(scheduler);
	
	
	if (NULL != scheduler -> task)
	{
		TaskDestroy (scheduler -> task);
		scheduler -> task = NULL;
	}
	
	PriorityQueueDestroy(scheduler -> queue);
	scheduler -> queue = NULL;
	
	free(scheduler);
}

/************************IsEmpty***********************/

int SchedulerIsEmpty(scheduler_t *scheduler)
{	
	assert (scheduler);

	return (PriorityQueueIsEmpty(scheduler -> queue));
}

/************************Add Task***********************/

ilrd_uid_t SchedulerAddTask(scheduler_t *scheduler, size_t time_interval, int(*task_func)(void *param), void *param)
{	
	task_t *new_task = NULL;
	int sucsess = 0;
	
	assert (scheduler);
	assert (task_func);
	
	if(0 == time_interval)
	{
		return (g_BadUid);
	}
	
	
	new_task = TaskCreate(time_interval, task_func, param);
	
	if(NULL == new_task)
	{
		return (g_BadUid);
	} 
	
	sucsess = PriorityQueueEnqueue(scheduler -> queue, new_task);
	
	if(1 == sucsess)
	{	
		free (new_task);
		
		new_task = NULL;
		
		return (g_BadUid);
	} 
	
	
	return (TaskGetUid(new_task));
}


/************************Remove***********************/

int SchedulerRemoveTask(scheduler_t *scheduler, ilrd_uid_t uid)
{
	task_t *task = NULL;
	
	assert (scheduler);

	task = (task_t*)PriorityQueueErase(scheduler -> queue, RemoveCmp, &uid);
	
	if(NULL == task)
	{
		return(1);
	}
	
	TaskDestroy(task);

	return (0);
}


/****************************************Size***************************************/

size_t SchedulerSize(scheduler_t *scheduler)
{	
	size_t size = 0;
	
	assert (scheduler);	

	size = PriorityQueueSize(scheduler -> queue);
	
	if (NULL != scheduler -> task)
	{
		++size;
	}

	return(size);
}


/**************************Clear**************************/

void SchedulerClear(scheduler_t *scheduler)
{	
	task_t *task = NULL;

	while (1 != SchedulerIsEmpty(scheduler))
	{
		task = (task_t*)PriorityQueueDequeue(scheduler -> queue);
		
		TaskDestroy(task);
	}

	
	if(NULL != scheduler -> task)
	{
		scheduler -> flag = 2;
	}
}


/**************************Stop**************************/


void SchedulerStop(scheduler_t *scheduler)
{	
	assert(scheduler);

	scheduler -> flag = STOP;
}


/**************************Run**************************/


int SchedulerRun(scheduler_t *scheduler)
{
	int sucssess = 0;
	int run_again = 0;
	int time_to_next = 0;
	scheduler -> flag = RUN;
	
	while (STOP != scheduler -> flag)
	{
			/***************check if empty and stop running*******/
			
		if (1 == SchedulerIsEmpty(scheduler))
		{
			return (EMPTY);
		}
		
			/***************take out the next task*******/
		
		scheduler -> task = (task_t *)PriorityQueueDequeue(scheduler -> queue);
		
				/*************sleep until the relevant time*******/
		
		time_to_next = (scheduler -> task -> time_exe) - time(NULL);

		sleep(time_to_next);
		
		
		/************run the task and return it back to the scheduler if relevant*******/
		
		run_again = TaskRun(scheduler -> task);
		
		
		
		if (0 != run_again || 2 == scheduler -> flag)
		{
			TaskDestroy(scheduler -> task);
			scheduler -> task = NULL;
		}
		
		else
		{
			TaskUpdateTimeToRun(scheduler -> task);
		
			sucssess = PriorityQueueEnqueue(scheduler -> queue, scheduler -> task);
			
		/**************check if there is a arrow in malloc in enqueue**********/
			
			if (1 == sucssess)
			{	
				TaskDestroy(scheduler -> task);
				scheduler -> task = NULL;
				
				return (ERROR);
			}
		}
		
	}

	return (STOP);
}


/************************************additional functions*********************************/

static int RemoveCmp(const void *task, const void *param)
{
	task_t *task_cast = (task_t *)task;
	
	ilrd_uid_t compare_uid = *(ilrd_uid_t *)param;
	
	if (1 == UIDIsSame(task_cast -> uid, compare_uid))
	{
		return (0);
	}
	
	return (1);
}











