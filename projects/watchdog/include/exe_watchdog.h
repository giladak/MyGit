/**************************************************************************

	dev : Gilad Kahn
	rev: Idan Matalon
	status: approved
	date: 30.3.22
*******************************************************************/	

#ifndef EXE_WATCHDOG_H
#define EXE_WATCHDOG_H

/*
#ifndef _POSIX_C_SOURCE
#define _POSIX_C_SOURCE 200809L

#endif
*/
#include <stdio.h> /*size_t*/
#include <unistd.h> /*pid_t*/
#include <semaphore.h> /*sem_t*/
#include <signal.h> /*sigaction*/

#include <sys/types.h> /*pid_t*/

#include "scheduler.h" /*scheduler_t*/






#define PID_MAX_SIZE 8
#define PROCESS_PATH_SIZE 100
#define TIME_BETWEEN_SIGNALS 2
#define ARGS_NUM 5
#define MAX_ARGS_SIZE 50
#define REPLACE 1
#define NAME_MAX 251


#define MAX_LENTGH 100

#define EXE_PATH_PLACE 1
#define PID_PLACE 2
#define GRACE_PLACE 3
#define END_PLACE 4

#define MAX_PATH 150

#define CONVERT_INT_TO_STRING(string, int)  sprintf(string, "%d", int)


typedef struct watch_dog watch_dog_t;




struct watch_dog
{
    pid_t proccess_pid;
    char *process_path;
    size_t grace;
    scheduler_t *scheduler;
    int is_watch_dog;
    sem_t *sem;
};




/*************************************************************signal handlers********************************************88*/
int SetSignalHandlers();
void Sigusr1Handler(int signum);
void Sigusr2Handler(int signum);
void CleanUpRoutine(void *param);







/********************************************revive**************************************************/
int Revive (watch_dog_t *watch_dog);





/***************************************scheduler tasks*******************************************************/
int CheckStopFlag(void *param);
int CheckGlobalFlag(void *param);
int SendSignal (void *param);

#ifndef NDBUG

int TaskPrint(void *param);

#endif

/*******************************************************************watch_dog Init******************************************************/                                                               
watch_dog_t *WatchDogInit(watch_dog_t *watch_dog, char *path, size_t grace, int is_watch_dog , pid_t pid);
void MatchSchedulerToWatchDog(watch_dog_t *watch_dog, scheduler_t *scheduler);
scheduler_t *InitScheduler(watch_dog_t *watch_dog);


/******************************************Init masks and signals*******************************/
int SetMask(int signum);
int UnMask(int signum);
int SetSignalHandlers();




/******************************************SchedulerThread*******************************/
void *SchedulerThread (void *args);





/********************************Other Functions********************************************/

void WriteToLogFile(char *string);
sem_t *CreateNamedSemaphore(char *sem_name, int value);
void EndSchedulerProcess(pid_t pid);



#endif
