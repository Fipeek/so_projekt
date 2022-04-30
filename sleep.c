#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <time.h>
#include <signal.h>
#include <stdbool.h>

void handler_sigusr1(int sig){
    time_t t;
    time(&t);
    printf("\n Wybudzenie o %s po otrzymaniu sygnalu.\n", ctime(&t));
}

bool SleepMode(int sleepTime){

    unsigned int ret;
    time_t t;
    time(&t);

    int pid = fork();
    if(pid == -1){
        return false;
    }

    if(pid != 0){
         printf("\nRozpoczynam sen o %s.\n", ctime(&t));
         struct sigaction sa = { 0 };
         sa.sa_handler = &handler_sigusr1;
         sigaction(SIGUSR1, &sa, NULL);
            
         ret = sleep(sleepTime);
         time(&t);
         printf("\nWybudzenie o %s.\n", ctime(&t));
    }
    
    return true;
}   
