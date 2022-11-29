#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <stddef.h> /*size_t*/

#include "task.h"
#include "p_queue.h"
#include "uid.h"


typedef struct scheduler scheduler_t;




/****************************************************************************
                                        				create
***************************************************************************
DESCRIPTION: creates a new scheduler
	
ARGUMENTS: non
	
RETURN VALUE: a pointer to the new scheduler
	
complexity: O(1) 
*****************************************************************************************************************************************/
scheduler_t *SchedulerCreate();





/*************************************************************************************************
                                        				Destroy
**************************************************************************************************
DESCRIPTION: destroys a schedular a frees its memory
	
ARGUMENTS: 
	scheduler - the adress of the relevant scheduler
	
RETURN VALUE:
	non
	
complexity: O(n) 
****************************************************************************************************************************************/
void SchedulerDestroy(scheduler_t *scheduler);






/*****************************************************************************************************************************************
                                        				AddTask
******************************************************************************************************************************************
DESCRIPTION: adds a task to the scheduler
	
ARGUMENTS: 
	scheduler - a pointer to the new scheduler
	time_interval - the frequency the task will repet itself in seconds
	task_func - the task func
	param - the parameters for the task func
	
RETURN VALUE:
	a new uid the describes the new task
	
complexity O(n)
****************************************************************************************************************************************/
ilrd_uid_t SchedulerAddTask(scheduler_t *scheduler, size_t time_interval, int(*task_func)(void *param), void *param);





/*****************************************************************************************************************************************
                                        				RemoveTask
******************************************************************************************************************************************
DESCRIPTION: removes a task from the list
	
ARGUMENTS: 
	uid - the tasks uid
	scheduler - a pointer to the relavent scheduler
	
	
RETURN VALUE: 1 in failure and 0 in sucsses
	
complexity: O(n)
****************************************************************************************************************************************/
int SchedulerRemoveTask(scheduler_t *scheduler, ilrd_uid_t uid);




/***********************************************************************************************
                                       Run
***********************************************************************************************
DESCRIPTION:
	a function that runs the scheduler
	
ARGUMENTS:
		scheduler - a pointer to the relavent scheduler
	
RETURN VALUE
	0 - succsess
	1 - tasks completed
	2 - error 
	
complexity O(n)
****************************************************************************************************************************************/
int SchedulerRun(scheduler_t *scheduler);




/****************************************************************************************************************************************
                                        				Stop
*****************************************************************************************************************************************
DESCRIPTION:
	a function that stops the scheduler
	
ARGUMENTS:
		scheduler - a pointer to the relavent scheduler
	
RETURN VALUE
	non
	
	
complexity: O(1) 
****************************************************************************************************************************************/
void SchedulerStop(scheduler_t *scheduler);





/****************************************************************************************************************************************
                                        				Size
*****************************************************************************************************************************************
DESCRIPTION: checks the size of the schdular
	
ARGUMENTS:
		scheduler - a pointer to the relavent scheduler	
	
RETURN VALUE: the size of the schdular
	
complexity 
****************************************************************************************************************************************/
size_t SchedulerSize(scheduler_t *scheduler);






/****************************************************************************************************************************************
                                        				IsEmpty
*****************************************************************************************************************************************
DESCRIPTION
	
ARGUMENTS
	
RETURN VALUE
	
complexity 
****************************************************************************************************************************************/
int SchedulerIsEmpty(scheduler_t *scheduler);






/****************************************************************************************************************************************
                                        				Clear
*****************************************************************************************************************************************
DESCRIPTION
	
ARGUMENTS
	
RETURN VALUE
	
complexity 
****************************************************************************************************************************************/
void SchedulerClear(scheduler_t *scheduler);









#endif /*SCHEDULER_H*/


