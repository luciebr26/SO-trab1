#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>

typedef enum {
    READY,
    RUNNING,
    BLOCKED,
    FINISHED
} State;

typedef struct {
    pid_t pid;
    int pc;
    State State;
} PCB;

void contHandler(int signal);
void stopHandler(int signal);
void IRQ0Handler(int signal);
void IRQ1Handler(int signal);

void queue_ready();
void queue_blocked();