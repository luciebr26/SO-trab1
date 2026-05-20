//Each application process Ax must contain a loop of up to MAX iterations 
//and have an iteration counter called PC.

//The loop body should contain a sleep(1) statement, and the time intervals 
//after the start of each syscall (D1, R, or W) should be defined.

#include "app.h"

void processos(){

    for (int i=0; i<NPROC; i++){
        pid_t pid = fork();

        //Child
        if (pid==0){
            int pc = 0;
            
            a[i].pid = getpid();
            raise(SIGSTOP); //block the process until the kernel schedules it

            for(pc = 0; pc<= MAX; pc++){
                sleep(1);
                printf("A%d, PID=%d, PC=%d\n", i + 1, getpid(), pc);

                if (pc == 4 ) {
                    a[i].syscall = 'D'; // D1 syscall

                    // notify kernel
                    kill(getppid(), SIGUSR1);

                    // block process
                    raise(SIGSTOP); 
                }

                if (pc == 10) {
                    a[i].syscall = 'R'; // Read syscall
                    // notify kernel
                    kill(getppid(), SIGUSR1);

                    // block process
                    raise(SIGSTOP); 
                }

                if (pc == 15) {
                    a[i].syscall = 'W'; // Write syscall
                    // notify kernel
                    kill(getppid(), SIGUSR1);

                    // block process
                    raise(SIGSTOP); 

                }

            }

            printf("A%d finished\n", i + 1);
            exit(0);
        }

        //parent
        else if (pid > 0){
            // Parent
            a[i].pid = pid;
            a[i].pc = 0;
            a[i].state = READY;
        }

        //Error
        else {
            printf("Error in creating child process");
            exit(1);
        }
    }
}