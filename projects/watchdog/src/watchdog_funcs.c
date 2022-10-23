/**************************************************************************

	dev : Gilad Kahn
	rev: Idan Matalon
	status: approved
	date: 30.3.22
*******************************************************************/	

#define _DEFAULT_SOURCE

#include <stdio.h>  /*for*/
#include <stdlib.h> /*malloc*/
#include <assert.h> /*assert*/
#include <signal.h> /*sigemptyset 200809L*/
#include <time.h>   /*time*/
#include <string.h> /*strcpy*/
#include <fcntl.h>  /*O_CREAT*/
#include <unistd.h> /*usleep*/

#include <pthread.h>    /*pthread_create*/
#include <semaphore.h>  /*semaphore*/
#include <stdatomic.h>  /*atomic_size_t*/


#include "utilities.h" 
#include "scheduler.h"
#include "task.h"
#include "watchdog.h"
#include "exe_watchdog.h"




/***************************global variables*************************************/

char value = ON; 
char enviroment_flag[PID_MAX_SIZE]       = {0};
char process_pid_as_string[PID_MAX_SIZE] = {0};
char grace_as_string[PID_MAX_SIZE]       = {0};


atomic_size_t grace_counter = 0;
atomic_int run              = 0;
atomic_int global_flag      = OFF;

watch_dog_t watch_dog               = {0};
watch_dog_answer_t watch_dog_answer = {0};

char *user_process_argv[ARGS_NUM]   = {0};
char *watchdog_argv[ARGS_NUM]       = {0};

struct sigaction sa;
struct sigaction sb;

pthread_t user_process_thread;
pthread_mutex_t log_mutex;



/******************************************API functions**********************************************/


watch_dog_answer_t *WatchDogRun(char *process_exe_path, char *watchdog_exe_path, size_t grace)
{
    pid_t watchdog_pid = 0;
    watch_dog_t *user_watchdog_struct = NULL;
    sem_t *wait_for_watchdog          = NULL;

    assert(process_exe_path);
    assert(watchdog_exe_path);

    SetMask(SIGUSR1);
    SetMask(SIGUSR2);
    SetMask(SIGTERM);



    /*initilizing relevant data*/

    CONVERT_INT_TO_STRING(grace_as_string, (int)grace);
    CONVERT_INT_TO_STRING(process_pid_as_string, getpid());

    user_watchdog_struct = &watch_dog;

    if (0 != sem_unlink(process_pid_as_string))
    {
        #ifndef NDEBUG

        printf ("execution failed at unlink: \n");
        perror("execvp");

        #endif /*NDEBUG*/

    }

    wait_for_watchdog = CreateNamedSemaphore(process_pid_as_string, 0);

    watchdog_argv[0] = watchdog_exe_path;
    watchdog_argv[EXE_PATH_PLACE] = process_exe_path;
    watchdog_argv[GRACE_PLACE] = grace_as_string;
    watchdog_argv[PID_PLACE] = process_pid_as_string;
    watchdog_argv[END_PLACE] = NULL;
    

    /*create enviroment variable flag and write to log file*/



    WriteToLogFile("start running watch dog");


    /*create watchdog process*/

    watchdog_pid = fork();                                                  

    if (-1 == watchdog_pid)
    {
        return(NULL);
    }

        

    else if (0 == watchdog_pid) /*watch dog process*/
    {

        if (-1 == execvp(watchdog_exe_path, watchdog_argv))
        {
            #ifndef NDEBUG

            printf ("execution failed at creating watchdog process: \n");
            perror("execvp");

            #endif /*NDEBUG*/

            return(NULL);
        }
        else
        {   
            WriteToLogFile("execution failed at creating watchdog process");
        }
    }



    /*create user thread*/
    else
    {   
        user_watchdog_struct = WatchDogInit(&watch_dog, watchdog_exe_path, grace, FALSE, watchdog_pid);
        user_watchdog_struct->sem = wait_for_watchdog;

        sem_wait(wait_for_watchdog);
        pthread_create(&user_process_thread, NULL, SchedulerThread, (void*)user_watchdog_struct);
    }


    CONVERT_INT_TO_STRING(enviroment_flag, watchdog_pid);
    strcat(enviroment_flag, " RUNNING");
 
    if (0 != setenv("WD_PID", enviroment_flag, 0))
    {

        #ifndef NDEBUG
            
        printf ("failure at creating enivroment flag \n");
        perror("setenv");
            
        #endif /*NDEBUG*/

        return(NULL);
    }

    watch_dog_answer.pid = watchdog_pid;
    watch_dog_answer.pthread = &user_process_thread;

    return(&watch_dog_answer);
}



void WatchDogStop (watch_dog_answer_t *watch_dog_return)
{
    EndSchedulerProcess(watch_dog_return->pid);
    EndSchedulerProcess(0);

    if (0 != pthread_join(*(pthread_t*)(watch_dog_return->pthread), NULL))
    {
        #ifndef NDEBUG

            printf("error in stop pthread_join: \n");
            perror("pthread_join");

        #endif
    }

    if (0 != setenv("WD_PID", "OFF", REPLACE))
    {

        #ifndef NDEBUG
        
            
            printf ("failure at creating enivroment flag \n");
            perror("setenv");

           
        #endif /*NDEBUG*/

        return;
    }

    WriteToLogFile("stopped running watch dog");
}






/******************************************************WatchDog Init Funcs******************************************************************/


watch_dog_t *WatchDogInit(watch_dog_t *watch_dog, char *path, size_t grace, int is_watch_dog, pid_t pid)
{
    assert(path);

    watch_dog->grace = grace;
    watch_dog->process_path = path;
    watch_dog->is_watch_dog = is_watch_dog;
    watch_dog ->proccess_pid = pid;

    return(watch_dog);
}


scheduler_t *InitScheduler(watch_dog_t *watch_dog)
{
    scheduler_t *new_scheduler = NULL;

    assert(watch_dog);

    new_scheduler = SchedulerCreate(TaskCmp);

    if (NULL == new_scheduler)
    {
        return(NULL);
    }

    #ifndef NDEBUG

    SchedulerAddTask(new_scheduler, 2, TaskPrint, watch_dog);

    #endif

    SchedulerAddTask(new_scheduler, TIME_BETWEEN_SIGNALS, SendSignal, watch_dog);

    SchedulerAddTask(new_scheduler, 1, CheckStopFlag, watch_dog);

    SchedulerAddTask(new_scheduler, TIME_BETWEEN_SIGNALS, CheckGlobalFlag, watch_dog);

    return (new_scheduler);
}


void MatchSchedulerToWatchDog(watch_dog_t *watch_dog, scheduler_t *scheduler)
{
    assert(watch_dog);
    assert(scheduler);

    watch_dog->scheduler = scheduler;
}



/******************************************************WatchDog Thread Run And Revive******************************************************************/

void *SchedulerThread (void *args)
{   
    watch_dog_t *watch_dog = (watch_dog_t *)args;

    pthread_cleanup_push(CleanUpRoutine, args);

    SetSignalHandlers();

    UnMask(SIGUSR1);
    UnMask(SIGUSR2);    
    UnMask(SIGTERM);


 
    watch_dog->scheduler = InitScheduler(watch_dog);


    if (NULL ==  watch_dog->scheduler)
    {
        #ifndef NDEBUG

        printf("problem in sched init aginst %s \n", watch_dog->process_path);

        #endif

        EndSchedulerProcess(0);
    }

    else
    {   
        #ifndef NDEBUG

        printf("succsess in sched init aginst %s \n", watch_dog->process_path);

        #endif
    }

    

    run = TRUE;

    
    if (0 != SchedulerRun(watch_dog->scheduler))
    {
        #ifndef NDEBUG

        printf("problem in sched run aginst %s \n", watch_dog->process_path);

        #endif
    }   

    else
    {
        #ifndef NDEBUG

        printf("succsess in sched run aginst %s \n", watch_dog->process_path);

        #endif
    }

    pthread_cleanup_pop(1);
    pthread_exit(0);
}


int Revive(watch_dog_t *watch_dog)
{   
    pid_t old_pid = 0;
    pid_t new_pid = 0;

    #ifndef NDEBUG

    int svalue = 0;

    #endif

    assert(watch_dog);

    old_pid = watch_dog->proccess_pid;

    /*first we kill gently the old process*/

    EndSchedulerProcess (old_pid);

    /* test if i can kill with send signal*/

    new_pid = fork();

    if (-1 == new_pid)
    {
        return(0);
    }

    else if (0 == new_pid) /*at child*/
    {
        /* now i revive the process and kill the running one if nedded*/
        

        if (TRUE != watch_dog->is_watch_dog)
        {   
            WriteToLogFile("starting to revive watch-dog");

            #ifndef NDEBUG

            printf("starting to revive watch-dog \n");

            #endif


            if (-1 == execvp(watch_dog->process_path, watchdog_argv))
            {
                #ifndef NDEBUG

                printf ("execution failed at recreating watchdog process: \n");
                perror("execvp");

                #endif /*NDEBUG*/

                return(1);
            }
        }

        else        /*at watchdog process*/
        {   
            WriteToLogFile("starting to revive user process:");

           #ifndef NDEBUG

            printf("starting to revive user process \n");

            #endif

            user_process_argv[0] = watch_dog->process_path;
            user_process_argv[1] = NULL;

            if (-1 == execvp(watch_dog->process_path, user_process_argv))
            {
                #ifndef NDEBUG

                printf ("execution failed at recreating user process: \n");
                perror("execvp");

                #endif /*NDEBUG*/

                return(1);
            }
        }
    }

    else /*parent process*/
    {
        if (TRUE == watch_dog->is_watch_dog)
        {
            pthread_exit(0);
        }

        else
        {
            watch_dog->proccess_pid = new_pid;


            #ifndef NDEBUG

            printf("at wait \n");
            sem_getvalue(watch_dog->sem, &svalue);
            printf("watchdog sem value = %d \n", svalue);

            #endif
            


            sem_wait(watch_dog->sem);

            #ifndef NDEBUG
            
            printf("passed wait \n");

            #endif
        }
    }

    return(0);

    /*we kill brutely the old process, need to save old pid?*/ /*neccery?*/
}



/******************************************************Initilize Masks and Signal handlers******************************************************************/


int SetSignalHandlers()
{   
    sa.sa_handler = &Sigusr1Handler;
    sb.sa_handler = &Sigusr2Handler;

   /*not working - check
    sa->sa_flags = SA_RESTART;
    sa.sa_flags =  SA_NODEFER | SA_SIGINFO;*/

    sigaction(SIGUSR1, &sa, NULL);
    sigaction(SIGUSR2, &sb, NULL);

    return(0);
}

int SetMask(int signum)
{
    sigset_t sigmask;
    
    sigemptyset(&sigmask);
    sigaddset(&sigmask, signum);


	if (0 != sigprocmask(SIG_BLOCK, &sigmask, NULL))
	{
		return(1);
	}

    return (0);
}

int UnMask(int signum)
{
    sigset_t sigmask;
    
    sigemptyset(&sigmask);
    sigaddset(&sigmask, signum);


	if (0 != pthread_sigmask(SIG_UNBLOCK, &sigmask, NULL))
	{
		return(1);
	}

    return (0);
}


/******************************************************Signal handlers and Clean up routine******************************************************************/



void Sigusr1Handler(int signum)
{   
    UNUSED(signum);

    global_flag = ON;
}

void Sigusr2Handler(int signum)
{   
    UNUSED(signum);
    run = OFF;
}

void CleanUpRoutine(void *param)
{
    watch_dog_t *watch_dog = (watch_dog_t *)param;

    sem_close(watch_dog ->sem);

    #ifndef NDBUG

    printf("clean up apllied at is_watchdog = %d\n", watch_dog->is_watch_dog);

    #endif

    SchedulerDestroy(watch_dog->scheduler);
}


/******************************************************Tasks******************************************************************/



int SendSignal (void *param)
{
    watch_dog_t *watch_dog = (watch_dog_t *)param;

    #ifndef NDEBUG

    printf("sending signal to %s: \n", watch_dog->process_path); /*erase*/

    #endif

   kill(watch_dog->proccess_pid, SIGUSR1);

   return(0);
}

int CheckGlobalFlag(void *param)
{   
    watch_dog_t *watch_dog = (watch_dog_t *)param; 

    if (ON == global_flag)
    {
        grace_counter = 0;
        global_flag = OFF;

        #ifndef NDEBUG

        printf("succsess in accepting signal from %s \n",  watch_dog->process_path); /*erase*/

        #endif
    }

    else if (OFF == global_flag) /*take of*/
    {
        ++grace_counter;

        if (watch_dog->grace == grace_counter)
        {
            #ifndef NDEBUG

            printf("didnt accept signal, should start reviving %s : \n", watch_dog->process_path);

            #endif

            Revive(watch_dog);

            return(0);
        }

        else
        {   
            #ifndef NDEBUG

            printf("didnt accept signal, but shouldn`t start to revive %s: \n", watch_dog->process_path);

            #endif

            return(0);
        }

    }

    return(0);
}

int CheckStopFlag(void *param)
{
    watch_dog_t *watch_dog = (watch_dog_t *)param;

    assert(param);

    if (TRUE != run)
    {   
        if (TRUE == watch_dog->is_watch_dog)
        {
            EndSchedulerProcess(watch_dog->proccess_pid);
        }

        #ifndef NDBUG

        printf("stop running\n");

        #endif

        pthread_exit(0);
    }

    return(0);
}


#ifndef NDBUG


int TaskPrint(void *param)
{   
    watch_dog_t *watch_dog = (watch_dog_t *)param;

    printf("scheduler aginst %s running \n", watch_dog ->process_path);

    return(0);
}

#endif


/******************************************************Other Functions******************************************************************/


void WriteToLogFile(char *string)
{   
    FILE *file_ptr = NULL;
    time_t t;

    assert(string);

    time(&t);

    pthread_mutex_lock(&log_mutex);

    file_ptr = fopen("log.txt", "a");

    fprintf(file_ptr, "%s \t %s \n", ctime(&t), string);

    fclose(file_ptr);

    pthread_mutex_unlock(&log_mutex);
}


sem_t *CreateNamedSemaphore(char *sem_name, int value)
{
    sem_t *new_sem = NULL;

    new_sem = sem_open(sem_name, O_CREAT, 0644, value);

    if (NULL == new_sem)
    {
        return(NULL);
    }

    return(new_sem);
}

void EndSchedulerProcess(pid_t pid)
{   
    size_t i = 0;

    for (i = 0; i < 10; ++i)
    {
        usleep(1000000);
        if (0 != kill(pid, SIGUSR2))
        {
            break;
            i = 0;
        }
    }



    if (0 != i)
    {
        while(0 == kill(pid, SIGTERM) && i < 20)
        {
            usleep(1000);
            ++i;
        }
    }

}
