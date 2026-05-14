#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX 10000

void contHandler(int signal);
void stopHandler(int signal);
void IRQ0(int signal);
void IRQ1(int signal);

int main(){
    int PC, D1;
    int R = read();
    int W = write();

    for (int i=0; i<=6; i++){
        pid_t a[i];

        a[i] = fork();
        if (a[i] == 0){
            for (PC = 0; PC <= MAX; i++){
                sleep(1);
                syscall(D1, R);
                if(syscall(D1, W)){
                    signal(SIGSTOP, stopHandler);
                }
            }
        }
        
        signal(SIGCONT, contHandler);
    }

    return 0;
    
}

void stopHandler(int signal){

}

void contHandler(int signal){

}

void IRQ0(int signal){
    kill(a[i], SIGSTOP);
    kill(a[i+1], SIGCONT);
}

void IRQ1(int signal){

}