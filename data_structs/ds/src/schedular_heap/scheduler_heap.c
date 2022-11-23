

#include <stdio.h>  /*size_t, for, while*/
#include <stdlib.h> /*malloc, free*/
#include <assert.h> /*assert*/

#include "pq_heap.h"
#include "heap.h"
#include "task.h"
#include "uid.h"
#include "scheduler_heap.h"

#define RUN 0



#define EMPTY 0
#define STOP 1
#define ERROR 2

/* 
	flag can get:
0 - for run
1 - for stop
2 - clear while run, erase scheduler_heap_t -> task

*/

struct scheduler_heap
{
	pq_heap_t *queue;
	task_t *task;
	int flag;  
};


static int RemoveCmp(const void *task, const void *param);
int TaskCmpHeap(const void *task1, const void *task2)
{
    return (TaskCmp(task1, task2));
}


/************************create***********************/

scheduler_heap_t *SchedulerHeapCreate()
{
	scheduler_heap_t *new_scheduler = (scheduler_heap_t *)malloc(sizeof(scheduler_heap_t));
	
	if (NULL == new_scheduler)
	{
		return (NULL);
	}
	
	new_scheduler -> queue = PriorityQueueHeapCreate(TaskCmpHeap);
	
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


void SchedulerHeapDestroy(scheduler_heap_t *scheduler)
{
	assert(scheduler);
	
	SchedulerHeapClear(scheduler);
	
	
	if (NULL != scheduler -> task)
	{
		TaskDestroy (scheduler -> task);
		scheduler -> task = NULL;
	}
	
	PriorityQueueHeapDestroy(scheduler -> queue);
	scheduler -> queue = NULL;
	
	free(scheduler);
}

/************************IsEmpty***********************/

int SchedulerHeapIsEmpty(scheduler_heap_t *scheduler)
{	
	assert (scheduler);

	return (PriorityQueueHeapIsEmpty(scheduler -> queue));
}

/************************Add Task***********************/

ilrd_uid_t SchedulerHeapAddTask(scheduler_heap_t *scheduler, size_t time_interval, int(*task_func)(void *param), void *param)
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
	
	sucsess = PriorityQueueHeapEnqueue(scheduler -> queue, new_task);
	
	if(1 == sucsess)
	{	
		free (new_task);
		
		new_task = NULL;
		
		return (g_BadUid);
	} 
	
	
	return (TaskGetUid(new_task));
}


/************************Remove***********************/

int SchedulerHeapRemoveTask(scheduler_heap_t *scheduler, ilrd_uid_t uid)
{
	task_t *task = NULL;
	
	assert (scheduler);

	task = (task_t*)PriorityQueueHeapErase(scheduler -> queue, RemoveCmp, &uid);
	
	if(NULL == task)
	{
		return(1);
	}
	
	TaskDestroy(task);

	return (0);
}


/****************************************Size***************************************/

size_t SchedulerHeapSize(scheduler_heap_t *scheduler)
{	
	size_t size = 0;
	
	assert (scheduler);	

	size = PriorityQueueHeapSize(scheduler -> queue);
	
	if (NULL != scheduler -> task)
	{
		++size;
	}

	return(size);
}


/**************************Clear**************************/

void SchedulerHeapClear(scheduler_heap_t *scheduler)
{	
	task_t *task = NULL;

	while (1 != SchedulerHeapIsEmpty(scheduler))
	{
		task = (task_t*)PriorityQueueHeapDequeue(scheduler -> queue);
		
		TaskDestroy(task);
	}

	
	if(NULL != scheduler -> task)
	{
		scheduler -> flag = 2;
	}
}


/**************************Stop**************************/


void SchedulerHeapStop(scheduler_heap_t *scheduler)
{	
	assert(scheduler);

	scheduler -> flag = STOP;
}


/**************************Run**************************/


int SchedulerHeapRun(scheduler_heap_t *scheduler)
{
	int sucssess = 0;
	int run_again = 0;
	int time_to_next = 0;
	scheduler -> flag = RUN;
	
	while (STOP != scheduler -> flag)
	{
		/***************check if empty and stop running*******/
			
		if (1 == SchedulerHeapIsEmpty(scheduler))
		{
			return (EMPTY);
		}
		
		/***************take out the next task*******/
		
		scheduler -> task = (task_t *)PriorityQueueHeapDequeue(scheduler -> queue);
		
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
		
			sucssess = PriorityQueueHeapEnqueue(scheduler -> queue, scheduler -> task);
			
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











