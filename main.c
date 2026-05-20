#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "app.h"
#include "kernel.h"
#include "intercontroller.h"

int main(){
    printf("Inicializando o kernel\n");
    init_kernel();

    //signal(SIGUSR1, syscallHandler);
    printf("Registrando handlers de IRQ\n");
    signal(SIGALRM, IRQ0Handler);
    signal(SIGUSR2, IRQ1Handler);

    printf("Criando processos de aplicação\n");
    processos();

    printf("Start : A1, PID: %d\n", a[0].pid);
    a[0].state = RUNNING;
    kill(a[0].pid, SIGCONT);

    printf("Kernel em loopo infinito, aguardando interrupções :\n");

    while (1) {
        sleep(1);
    }
    return 0;
    
}

