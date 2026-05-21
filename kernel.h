#ifndef KERNEL_H
#define KERNEL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "queue.h"
#include "app.h"

#define NPROC 3 // Number of processess

typedef enum {
    READY,
    RUNNING,
    BLOCKED,
    FINISHED
} State;

typedef struct {

    pid_t pid;
    int pc;
    State state;
    char syscall; // 'D' para D1, 'R' para R, 'W' para W
        
} Processo;

extern Processo a[NPROC];
extern Queue wait_queue;
extern int current_process;
extern int pipe_syscall[2];
extern int pipe_pc[NPROC][2];

void init_kernel();
void schedule_next();
void print_state(void);

void IRQ0Handler(int signal); 
void IRQ1Handler(int signal);
void syscallHandler(int signal);
void sigchld_handler(int signum);

#endif 