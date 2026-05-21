//Each application process Ax must contain a loop of up to MAX iterations 
//and have an iteration counter called PC.

//The loop body should contain a sleep(1) statement, and the time intervals 
//after the start of each syscall (D1, R, or W) should be defined.

#include "app.h"

extern int pipe_pc[NPROC][2];

void processos(){
    for (int i = 0; i < NPROC; i++) {

        pid_t pid = fork();

        /* CHILD */
        if (pid == 0) {

            int pc;

            raise(SIGSTOP); // wait scheduler

            for(pc = 0; pc <= MAX; pc++)
            {
                write(pipe_pc[i][1], &pc, sizeof(int));

                sleep(1); 

                if(pc == 2 || pc == 4 || pc == 6)
                {
                    char syscall_type;

                    if(pc == 2) syscall_type = 'D';
                    else if(pc == 4) syscall_type = 'R';
                    else syscall_type = 'W';

                    int data[3];

                    data[0] = getpid();
                    data[1] = pc;
                    data[2] = syscall_type;

                    write(pipe_syscall[1], data, sizeof(data));

                    printf("A%d requested syscall %c\n",
                        i + 1,
                        syscall_type);

                    kill(getppid(), SIGUSR1);

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
            a[i].syscall = '\0';
            int status;
            waitpid(pid, &status, WUNTRACED);
        }
        
        //Error
        else {
            printf("Error in creating child process");
            exit(1);
        }
    }
    
}