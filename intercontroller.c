#include "intercontroller.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

pid_t kernel_pid; 

void intercontroller(pid_t kernel_pid){
    while(1){
        sleep(1);

        //IRQ 0
        printf("Interrupt Controller IRQ 0");

        kill(kernel_pid, SIGALRM);
    }
}

void io_timer(pid_t kernel_pid){

    pid_t pid = fork(); 

    if(pid < 0){
        //ERROR in creating child process 

        printf("Error in creating child process");

        //exit faliure
        exit(1);
    }

    //IRQ 1
    if(pid == 0){
        //inside the child process
        sleep(3);

        printf("Interrupt Controller IRQ1");

        kill(kernel_pid, SIGUSR2);

        //exit success
        exit(0);
    }

}