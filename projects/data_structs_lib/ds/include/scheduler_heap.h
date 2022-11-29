#ifndef SCHEDULER_HEAP_H
#define SCHEDULER_HEAP_H

#include <stddef.h> /*size_t*/

#include "task.h"
#include "pq_heap.h"
#include "heap.h"
#include "uid.h"


typedef struct scheduler_heap scheduler_heap_t;




/****************************************************************************
                                        				create
***************************************************************************
DESCRIPTION: creates a new scheduler_heap
	
ARGUMENTS: non
	
RETURN VALUE: a pointer to the new scheduler_heap
	
complexity: O(1) 
*****************************************************************************************************************************************/
scheduler_heap_t *SchedulerHeapCreate();





/*************************************************************************************************
                                        				Destroy
**************************************************************************************************
DESCRIPTION: destroys a scheduler a frees its memory
	
ARGUMENTS: 
	scheduler_heap - the adress of the relevant scheduler_heap
	
RETURN VALUE:
	non
	
complexity: O(n) 
****************************************************************************************************************************************/
void SchedulerHeapDestroy(scheduler_heap_t *scheduler_heap);






/*****************************************************************************************************************************************
                                        				AddTask
******************************************************************************************************************************************
DESCRIPTION: adds a task to the scheduler_heap
	
ARGUMENTS: 
	scheduler_heap - a pointer to the new scheduler_heap
	time_interval - the frequency the task will repet itself in seconds
	task_func - the task func
	param - the parameters for the task func
	
RETURN VALUE:
	a new uid the describes the new task
	
complexity O(n)
****************************************************************************************************************************************/
ilrd_uid_t SchedulerHeapAddTask(scheduler_heap_t *scheduler_heap, size_t time_interval, int(*task_func)(void *param), void *param);





/*****************************************************************************************************************************************
                                        				RemoveTask
******************************************************************************************************************************************
DESCRIPTION: removes a task from the list
	
ARGUMENTS: 
	uid - the tasks uid
	scheduler_heap - a pointer to the relavent scheduler_heap
	
	
RETURN VALUE: 1 in failure and 0 in sucsses
	
complexity: O(n)
****************************************************************************************************************************************/
int SchedulerHeapRemoveTask(scheduler_heap_t *scheduler_heap, ilrd_uid_t uid);




/***********************************************************************************************
                                       Run
***********************************************************************************************
DESCRIPTION:
	a function that runs the scheduler_heap
	
ARGUMENTS:
		scheduler_heap - a pointer to the relavent scheduler_heap
	
RETURN VALUE
	0 - succsess
	1 - tasks completed
	2 - error 
	
complexity O(n)
****************************************************************************************************************************************/
int SchedulerHeapRun(scheduler_heap_t *scheduler_heap);




/****************************************************************************************************************************************
                                        				Stop
*****************************************************************************************************************************************
DESCRIPTION:
	a function that stops the scheduler_heap
	
ARGUMENTS:
		scheduler_heap - a pointer to the relavent scheduler_heap
	
RETURN VALUE
	non
	
	
complexity: O(1) 
****************************************************************************************************************************************/
void SchedulerHeapStop(scheduler_heap_t *scheduler_heap);





/****************************************************************************************************************************************
                                        				Size
*****************************************************************************************************************************************
DESCRIPTION: checks the size of the schdular
	
ARGUMENTS:
		scheduler_heap - a pointer to the relavent scheduler_heap	
	
RETURN VALUE: the size of the schdular
	
complexity 
****************************************************************************************************************************************/
size_t SchedulerHeapSize(scheduler_heap_t *scheduler_heap);






/****************************************************************************************************************************************
                                        				IsEmpty
*****************************************************************************************************************************************
DESCRIPTION
	
ARGUMENTS
	
RETURN VALUE
	
complexity 
****************************************************************************************************************************************/
int SchedulerHeapIsEmpty(scheduler_heap_t *scheduler_heap);






/****************************************************************************************************************************************
                                        				Clear
*****************************************************************************************************************************************
DESCRIPTION
	
ARGUMENTS
	
RETURN VALUE
	
complexity 
****************************************************************************************************************************************/
void SchedulerHeapClear(scheduler_heap_t *scheduler_heap);









#endif /*SCHEDULER_H*/


