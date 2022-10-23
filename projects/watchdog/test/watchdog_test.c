

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>



#include "utilities.h"
#include "watchdog.h"



int main(int argc, char *argv[])
{   
    size_t i = 0;
    watch_dog_answer_t *answer = NULL;

    UNUSED(argc);
    UNUSED(argv);

    printf("the user pid = %d \n", getpid());

    answer = WatchDogRun(argv[0], "/home/shikamaru/Desktop/git/gilad-kahn/projects/watchdog/src/watchdog.out", 3);     
  

    while(i < 20)
    {
        sleep(2);

        printf("current number = %ld \n", i++);

        /*
        if (0 == i % 4)
        {
            printf("sending sigterm -----------------------------------------------------------------------------------------------------------------------------------------\n");
        }
        */


    }
    



    WatchDogStop(answer);



    return(0);
}