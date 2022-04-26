#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <time.h>
#include <signal.h>

void handler_sigusr1(int sig){
    time_t t;
    time(&t);
    printf("\n Wybudzenie o %s po otrzymaniu sygnalu.\n", ctime(&t));
    //sprawdz katalogi
}

int main(int amt, char *args[]){

    unsigned int ret;
    time_t t;
    time(&t);

    int pid = fork();
    if(pid == -1){
        return 1;
    }

    if(pid == 0){

    }else{

        while(1){

            printf("\nRozpoczynam sen o %s.\n", ctime(&t));

            struct sigaction sa = { 0 };
            sa.sa_handler = &handler_sigusr1;
            sigaction(SIGUSR1, &sa, NULL);
            
            if(amt == 2){
                ret = sleep(atoi(args[1]));
                time(&t);
                printf("\nWybudzenie o %s.\n", ctime(&t));
                //sprawdz katalogi
            }else{
                ret = sleep(300);
                time(&t);
                printf("\nWybudzenie o %s.\n", ctime(&t));
                //sprawdz katalogi
            }
        }
    }
    
    return 0;
}   