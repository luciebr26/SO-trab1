#include "kernel.h"
#include "intercontroller.h"

Processo a[NPROC];
Queue wait_queue;
int current_process = 0; // Index of the currently running process

void init_kernel(void){
    initializeQueue(&wait_queue);
    current_process = 0;

    for (int i = 0; i < NPROC; i++) {
        a[i].pid = -1; 
        a[i].pc = 0;   
        a[i].state = READY; 
        a[i].syscall = '\0';
    }
    printf("Kernel initialized with %d processes.\n", NPROC);
}

void IRQ0Handler(int signal){

    printf("IRQ0 received\n");

    //Quando chega um IRQ0, o Kernel Sim, envia um SIGSTOP para o processo que estava executando 
    if (a[current_process].state == RUNNING) {
        kill(a[current_process].pid, SIGSTOP); // Block the currently running process
        a[current_process].state = READY;
    }

    //O Kernel escolhe outro processo de aplicação e o ativa usando o sinal SIGCONT, contanto que este processo não esteja esperando pelo término de um syscall para o dispositivo de I/O, D1.
    int next_process = (current_process + 1) % NPROC;
    int start_search = next_process;

    while(a[next_process].state != READY) {
        next_process = (next_process + 1) % NPROC;
        if (next_process == start_search) {
            // No ready process found
            return;
        }
    }

    current_process = next_process;
    a[current_process].state = RUNNING;
    kill(a[current_process].pid, SIGCONT); // Activate the next process
    printf("Process %d is now running\n", current_process +1);

}

void IRQ1Handler(int signal){

    printf("IRQ1 received\n");

    /*Se dois processos A1 e A2 tiverem executado uma syscall para I/O para o
    dispositivo, então o primeiro IRQ1 indicará o término do primeiro I/O (e irá desbloquear um dos
    processos Ai)*/
    if (!isEmpty(&wait_queue)) {
        int process_index = peek(&wait_queue);
        dequeue(&wait_queue);
        a[process_index].state = READY; // Unblock the process
        printf("Process %d unblocked and ready to run\n", process_index);
    }
    else{
        printf("Nao tem processos esperando para I/O.\n");
    }
}

void syscallHandler(int signal){
    printf("Syscall received from process %d\n", current_process);

    // Block the current process and add it to the wait queue
    a[current_process].state = BLOCKED;
    enqueue(&wait_queue, current_process);
    kill(a[current_process].pid, SIGSTOP); 

    //start device timer
    io_timer(getpid());

    IRQ0Handler(0);
}

