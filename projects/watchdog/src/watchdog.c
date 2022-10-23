/*
	dev : Gilad Kahn
	rev : Idan Matalon
	status: approved
	date: 30.3.22
*/


#include <stdio.h>
#include <stdlib.h> /*atoi*/
#include <semaphore.h> /*sem_open*/
#include <assert.h> /*assert*/
#include <fcntl.h>  /*O_CREAT*/
#include <pthread.h> /*pthread_create*/
#include <signal.h> /*SIGUSR2*/
#include <stdatomic.h> /*atomic_size_t*/


#include "exe_watchdog.h"
#include "utilities.h"
#include "scheduler.h"



atomic_size_t grace_counter = 0;
atomic_int global_flag = OFF;

watch_dog_t watch_dog;




int main (int argc, char *argv[])
{
    pid_t user_process_pid = 0;
    pthread_t watchdog_process_thread;
    
    int grace = 0;

    UNUSED(argc);
    assert(argv);

    UnMask(SIGTERM);  /*********for case of SIGUSR 1 failure*******/


    #ifndef NDEBUG

    printf("watchdog.out called succsessfully, pid: %d\n", getpid());

    #endif

    user_process_pid = atoi(argv[PID_PLACE]);
    grace = atoi(argv[GRACE_PLACE]);

    WatchDogInit(&watch_dog, argv[EXE_PATH_PLACE], grace, TRUE, user_process_pid);

    watch_dog.sem = sem_open(argv[PID_PLACE],0);
    if (NULL == watch_dog.sem)
    {
        #ifndef NDEBUG

            printf("error in watchdog sem_open: \n");
            perror("sem_open");

        #endif

        pthread_exit(0);
    } 

    #ifndef NDEBUG

    printf("arriving at sem post \n");

    #endif

    if (0 != sem_post(watch_dog.sem))
    {
        #ifndef NDEBUG

            printf("error in watchdog sem_open: \n");
            perror("sem_post");

        #endif

        pthread_exit(0);
    }
    
    if (0 != pthread_create(&watchdog_process_thread, NULL, SchedulerThread, (void *)&watch_dog))
    {
        #ifndef NDEBUG

            printf("error in watchdog pthread_create: \n");
            perror("pthread_create");

        #endif

        pthread_exit(0);
    }

    if (0 != pthread_join(watchdog_process_thread, NULL))
    {
         #ifndef NDEBUG

            printf("error in watchdog pthread_join: \n");
            perror("pthread_join");

        #endif
    }

    pthread_exit(0);
}


