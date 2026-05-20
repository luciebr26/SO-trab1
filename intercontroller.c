#include "intercontroller.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void intercontroller(pid_t kernel_pid){
    while(1){
        sleep(1);

        //IRQ 0
        printf("[Interrupt Controller]-IRQ0\n");

        //error check for kill
        if(kill(kernel_pid, SIGALRM) == -1 ){
            perror("kill failed\n");
        }
    }
}

void io_timer(pid_t kernel_pid){

    pid_t pid = fork(); 

    if(pid < 0){
        //ERROR in creating child process 

        printf("Error in creating child process\n");

        //exit faliure
        exit(1);
    }

    //IRQ 1
    if(pid == 0){
        //inside the child process
        sleep(3);

        printf("[Interrupt Controller]-IRQ1\n");
        
        //error check 
        if(kill(kernel_pid, SIGUSR2) == -1){
            perror("Kill failed");
        }

        //exit success
        exit(0);
    }
}