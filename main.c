#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>
#include <fcntl.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "app.h"
#include "kernel.h"
#include "intercontroller.h"

extern int pipe_syscall[2];
extern int pipe_pc[NPROC][2];

int main(){
    printf("Inicializando o kernel\n");
    init_kernel();

    if(pipe(pipe_syscall) == -1){

        perror("pipe");

        exit(1);
    }

    //pipe para passar o pc do processo para o kernel
    for (int i = 0; i < NPROC; i++) {
        if (pipe(pipe_pc[i]) == -1) {
            perror("pipe_pc");
            exit(1);
        }
        // On rend le côté LECTURE [0] non-bloquant dès maintenant !
        int flags = fcntl(pipe_pc[i][0], F_GETFL, 0);
        fcntl(pipe_pc[i][0], F_SETFL, flags | O_NONBLOCK);
    }

    printf("Registrando handlers de IRQ\n");
    signal(SIGUSR1, syscallHandler);
    signal(SIGALRM, IRQ0Handler);
    signal(SIGUSR2, IRQ1Handler);
    signal(SIGCHLD, sigchld_handler);
    //start interrupt controller
    pid_t interrupt_pid = fork();

    if (interrupt_pid == 0) {

        intercontroller(getppid());
        exit(0);
    }

    printf("Criando processos de aplicação\n");
    processos();

    signal(SIGCHLD, sigchld_handler);

    printf("Start : A1, PID: %d\n", a[0].pid);
    a[0].state = RUNNING;
    kill(a[0].pid, SIGCONT);

    int all_finished = 0;

    while (!all_finished) {
        sleep(1);

        all_finished = 1;

        for (int i = 0; i < NPROC; i++) {
            if (a[i].state != FINISHED) {
                all_finished = 0;
                break;
            }
        }
    }

    kill(interrupt_pid, SIGKILL);
    printf("Todos os processos de aplicação terminaram.\n");


    return 0;
    
}

