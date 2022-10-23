/****************************************************************

	dev : Gilad Kahn
	rev: Idan Matalon
	status: approved
	date: 23.1.22
*********************************************************************/	


#include <stdio.h>  /*size_t, for, while*/
#include <stdlib.h> /*malloc, free*/
#include <assert.h> /*assert*/

#include "heap.h"
#include "pq_heap.h"
#include "task.h"
#include "scheduler_heap.h"
#include "uid.h"



/*
	if (  != )
	{
		printf ("error in test 1 \n");
	}
	
	if (  != )
	{
		printf ("error in test 2 \n");
	}
	
	if (  != )
	{
		printf ("error in test 3 \n");
	}   
*/

/***task functions ******/


int AddTask1(void* scheduler);
int RemoveTask2(void* scheduler);
int StopTask(void* scheduler);
int ManagmentTask(void* scheduler);
int MinusOne(void* num);
int TimesTwo(void* num);
int AddOne(void* num);
void TaskTests (void);
void schedulerTests (void);



typedef struct remove_struct
{
	scheduler_heap_t *scheduler;
	ilrd_uid_t uid;

}remove_t;



ilrd_uid_t task1;
ilrd_uid_t task2;
ilrd_uid_t task3;


int a = 5;
int b = 10;
int c = 10;

void schedulerheapTests (void)
{
	remove_t for_remove;
	
	scheduler_heap_t *test = NULL;

	printf("scheduler Heap Tests: \n");
	
/*****************check if create works***********/

	test = SchedulerHeapCreate();
	
	if (0 != SchedulerHeapSize(test))
	{
		printf ("error in Create test 1 \n");
	}	

	if (1  != SchedulerHeapIsEmpty(test))
	{
		printf ("error in Create test 2 \n");
	}
	
/*****************check if add works **************/

	task1 = SchedulerHeapAddTask(test, 10, AddOne, &a);
	task2 = SchedulerHeapAddTask(test, 20, MinusOne, &a);
	task3 = SchedulerHeapAddTask(test, 20, TimesTwo, &b);

	if (3 != SchedulerHeapSize(test))
	{
		printf ("error in Add test 1 \n");
	}
	
/*****************check if Remove works **************/
	
	
	SchedulerHeapRemoveTask(test, task1);
	SchedulerHeapRemoveTask(test, task2);

	if (1 != SchedulerHeapSize(test))
	{
		printf ("error in Remove test 1 \n");
	}

/*****************check if clear works *****************/

	SchedulerHeapClear(test);

	if (1  != SchedulerHeapIsEmpty(test))
	{
		printf ("error in Clear test 1 \n");
	}
	

/*****************check if stop works*****************/
	
	printf ("check if stop works: \n");	
	
	SchedulerHeapAddTask(test, 1, TimesTwo, &b);
	SchedulerHeapAddTask(test, 3, StopTask, test);


	SchedulerHeapRun(test);
	
	if (b != 40)
	{
		printf ("error in run test 1 b = %d \n", b);
	}
	
	SchedulerHeapClear(test);
		
		
/*****************check if empty stop works*****************/
	
	
	printf ("check if empty stop works: \n");	
	
	SchedulerHeapAddTask(test, 1, TimesTwo, &b);
	task1 = SchedulerHeapAddTask(test, 2, AddOne, &a);
	task2 = SchedulerHeapAddTask(test, 3, MinusOne, &c);	

	
	SchedulerHeapRun(test);
	
	if (b < 200)
	{
		printf ("error in run test 2 b = %d \n", b);
	}
	
	if (a != 10)
	{
		printf ("error in run test 3 a = %d \n", a);
	}
	
	if (c != 5)
	{
		printf ("error in run test 4 c = %d \n", c);
	}
	
	
	SchedulerHeapClear(test);
	
	

/*****************check if add and remove while works*****************/
	a = 5;
	b = 10;
	c = 10;
	
	printf ("check if add and remove while works: \n");	
	
	SchedulerHeapAddTask(test, 1, TimesTwo, &b);
	task2 = SchedulerHeapAddTask(test, 1, MinusOne, &c);
	SchedulerHeapAddTask(test, 3, AddTask1, test);

	for_remove.scheduler = test;
	for_remove.uid = task2; 
	
	SchedulerHeapAddTask(test, 2, RemoveTask2, &for_remove);		

	SchedulerHeapRun(test);


	if (b < 200)
	{
		printf ("error in run test 5 \n");
	}

	if (a  != 10)
	{
		printf ("error in run test 6 \n");
	}
	
	if (c  == 5)
	{
		printf ("error in run test 7 \n");
	}   



/************check if scheduler was deleted propely (vlg)************/
	
	SchedulerHeapDestroy(test);
}




int main()
{
	schedulerheapTests();
	TaskTests();


	return(0);
}







int TimesTwo(void* num)
{
	*(int*)num *= 2;
	
/*	printf ("b = %d \n",*(int*)num);*/
	
	if (200 < *(int*)num)
	{
		return(1);
	}
	
	return(0);
}





int AddOne(void* num)
{

	*(int*)num += 1;
	
	/*printf ("a = %d \n",*(int*)num);*/

	
	if (10 == *(int*)num)
	{
		return(1);
	}
	
	
	return(0);
}

int MinusOne(void* num)
{
	*(int*)num -= 1;
	/*printf ("c = %d \n",*(int*)num);*/
	
	if (5 == *(int*)num)
	{
		return(1);
	}
	
	
	return(0);
}

int ManagmentTask(void* scheduler)
{	
	scheduler_heap_t *casted_scheduler = (scheduler_heap_t *)scheduler;
	
	assert (scheduler);
	
	SchedulerHeapAddTask(casted_scheduler, 2, AddOne, scheduler);
	SchedulerHeapRemoveTask(casted_scheduler, task2);

	
	return(1);
}


int StopTask(void* scheduler)
{	
	scheduler_heap_t *casted_scheduler = (scheduler_heap_t *)scheduler;
	
	assert (scheduler);
	
	SchedulerHeapStop(casted_scheduler);
	
	return(0);
}



int AddTask1(void* scheduler)
{	
	scheduler_heap_t *casted_scheduler = (scheduler_heap_t *)scheduler;
	
	assert (casted_scheduler);
	
	SchedulerHeapAddTask(casted_scheduler, 1, AddOne, &a);
	
	return(1);

}


int RemoveTask2(void* for_remove)
{	
	remove_t *casted_remove = (remove_t *)for_remove;
	
	assert (for_remove);
	
	SchedulerHeapRemoveTask(casted_remove -> scheduler, casted_remove -> uid);
	
	return(1);
}





void TaskTests (void)
{
	task_t *test = NULL;
	task_t *test2 = NULL;
	int a = 2;
	int b = 10;
	
	printf ("Task Tests: \n");
	test = TaskCreate (200, TimesTwo, &b);
	test2 = TaskCreate (200, AddOne, &a);

	TaskRun (test);
	TaskRun (test2);
	
	TaskDestroy(test);
	TaskDestroy(test2);	
}





	/*
	printf("uid test = %lu \n", TaskGetUid(test));
	printf("uid test2 = %lu \n", TaskGetUid(test2));
	*/
