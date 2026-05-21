#include "kernel.h"
#include "intercontroller.h"
#include <string.h>
#include <sys/time.h>

Processo a[NPROC];
Queue wait_queue;
int current_process = 0; // Index of the currently running process
int pipe_syscall[2]; // Pipe for syscall communication between processes and kernel
int pipe_pc[NPROC][2]; // Pipes for PC communication between processes and kernel

static struct timeval start;

void print_state(void) {
    static int header_printed = 0;
    struct timeval now;

    // Get the time
    gettimeofday(&now, NULL);
    
    // Calculate the elapsed time in seconds since init_kernel
    int tempo = now.tv_sec - start.tv_sec;

    // Get the information of the current process
    char proc_name[10] = "-";
    int pc = 0;
    
    if (current_process != -1) {
        sprintf(proc_name, "A%d", current_process + 1);
        pc = a[current_process].pc;
    }

    // Build the string for the Ready Queue (File of ready processes)
    char fila_prontos[50] = "";
    int first = 1;
    
    for (int i = 0; i < NPROC; i++) {
        if (a[i].state == READY) {
            if (!first) {
                strcat(fila_prontos, ", ");
            }
            char temp[5];
            sprintf(temp, "A%d", i + 1);
            strcat(fila_prontos, temp);
            first = 0;
        }
    }
    
    if (strlen(fila_prontos) == 0) {
        strcpy(fila_prontos, "-");
    }

    // Display the formatted line
    printf("\n------------------------------------------------------------\n");
    printf("Tempo : %-7d | Processo : %-10s | PC : %-4d | Fila Prontos : %-15s\n", tempo, proc_name, pc, fila_prontos);
    
}

void init_kernel(void){
    initializeQueue(&wait_queue);
    current_process = 0;

    for (int i = 0; i < NPROC; i++) {
        a[i].pid = -1; 
        a[i].pc = 0;   
        a[i].state = READY; 
        a[i].syscall = '\0';
    }
    gettimeofday(&start, NULL);
    printf("Kernel initialized with %d processes.\n", NPROC);
}

void schedule_next()
{
    int next = (current_process + 1) % NPROC;
    int start = next;

    while(a[next].state != READY)
    {
        next = (next + 1) % NPROC;

        if(next == start)
        {
            current_process = -1;
            return;
        }
    }

    current_process = next;
    a[current_process].state = RUNNING;

    kill(a[current_process].pid, SIGCONT);
}

void IRQ0Handler(int signal){
    (void)signal;

    for (int i = 0; i < NPROC; i++) {
        int dernier_pc;

        while (read(pipe_pc[i][0], &dernier_pc, sizeof(int)) > 0) {
            a[i].pc = dernier_pc;
        }
    }

    print_state();

    if (a[current_process].state == RUNNING) {
        kill(a[current_process].pid, SIGSTOP);
        a[current_process].state = READY;
    }

    schedule_next();
}

void IRQ1Handler(int signal)
{
    (void)signal;

    int p = dequeue(&wait_queue);

    if(p != -1)
    {
        a[p].state = READY;
        printf("[Kernel] A%d READY after I/O\n", p+1);
    }

    if(current_process == -1)
        schedule_next();
}

void syscallHandler(int signal){
    (void)signal;

    int data[3];

    read(pipe_syscall[0], data, sizeof(data));

    pid_t pid = data[0];
    int pc = data[1];
    char syscall = data[2];

    int idx = -1;

    for(int i=0;i<NPROC;i++){

        if(a[i].pid == pid){

            idx = i;
            break;
        }
    }

    if(idx == -1)
        return;

    a[idx].pc = pc;
    a[idx].syscall = syscall;
    a[idx].state = BLOCKED;
    enqueue(&wait_queue, idx);

    io_timer(getpid());

    current_process = -1;

    schedule_next();
}

void sigchld_handler(int signum) {
    (void)signum;
    int status;
    pid_t pid;

    while ((pid = waitpid(-1, &status, WNOHANG)) > 0) {
        if (WIFEXITED(status) || WIFSIGNALED(status)) {
            for (int i = 0; i < NPROC; i++) {
                if (a[i].pid == pid) {
                    a[i].state = FINISHED; 

                    if (current_process == i) {
                        current_process = -1;
                        schedule_next();
                    }
                    break;
                }
            }
        }
    }
}
