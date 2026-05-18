#include "app.h"

Processo a[N];

void processos(){

    for (int i=0; i<N; i++){
        pid_t pid = fork();

        //child
        if (pid==0){
            a[i].pid = getpid();

            for(a[i].pc = 0; a[i].pc<= MAX; a[i].pc++){
                sleep(1);
                printf("A%d, PID=%d, PC=%d\n", i + 1, getpid(), a[i].pc);

                //syscall('R') 
                //syscall('W') 
            }
            exit(0);
        }

        //parent
        else {
            // Parent
            a[i].pid = pid;
        }
    }
    
}