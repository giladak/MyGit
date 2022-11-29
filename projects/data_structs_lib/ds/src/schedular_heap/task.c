

#include <stdio.h>  /*size_t, for, while*/
#include <stdlib.h> /*malloc, free*/
#include <assert.h> /*assert*/

#include "task.h" 


task_t *TaskCreate(size_t time_interval, int(*task_func)(void *param), void *param)
{
	task_t *new_task = (task_t *)malloc(sizeof(task_t));
	
	if (NULL == new_task)
	{
		return (NULL);
	} 
	
	assert(task_func);
	
	new_task -> uid = UIDCreate();
	
	if (UIDIsSame(new_task -> uid, g_BadUid))
	{
		free (new_task);	
		return (NULL);
	}
	
	
	new_task -> task_func = task_func;
	new_task -> param = param;
	
	new_task -> time_interval = time_interval;
	new_task -> time_exe = time(NULL) + time_interval;
	
	return (new_task);
}



void TaskDestroy(task_t *task)
{
	assert(task);
	
	free(task);
	
	task = NULL;
}





int TaskRun(task_t *task)
{
	int sucsses = 0;
	
	assert(task);	
		
	sucsses = (*task -> task_func)(task -> param);	
	
	return (sucsses);	
}





time_t TaskGetExeTime(const task_t *task)
{
	assert(task);

	return (task -> time_exe);
}


void TaskUpdateTimeToRun(task_t *task)
{
	assert(task);
	
	task -> time_exe += task -> time_interval;
}



ilrd_uid_t TaskGetUid(const task_t *task)
{
	assert(task);
	
	return(task -> uid);
}


int TaskCmp(const void *enterence_task1, const void *task2_in_schedular)
{
	task_t *task1_cast = (task_t*)enterence_task1;
	task_t *task2_cast = (task_t*)task2_in_schedular;
	
	
	assert (task1_cast);
	assert (task2_cast);	
	
	
	return (task2_cast -> time_exe - task1_cast -> time_exe);
}
						
					
				

						
					
					




