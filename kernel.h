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

#define NPROC 6 // Number of processess

typedef enum {
    READY,
    RUNNING,
    BLOCKED,
} State;

typedef struct {

    pid_t pid;
    int pc;
    State state;
    char syscall; // 'D' para D1, 'R' para R, 'W' para W
        
} Processo;

extern Processo a[NPROC];

void init_kernel();

//void syscallHandler(int signal); 
void IRQ0Handler(int signal); 
void IRQ1Handler(int signal);

#endif 