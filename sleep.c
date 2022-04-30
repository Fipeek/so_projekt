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
    
    printf("\n Wybudzenie po otrzymaniu sygnalu.\n");
    
}

bool SleepMode(int sleepTime){

         struct sigaction sa = { 0 };
         sa.sa_handler = &handler_sigusr1;
         sigaction(SIGUSR1, &sa, NULL);
         
         return sleep(sleepTime);
}   
