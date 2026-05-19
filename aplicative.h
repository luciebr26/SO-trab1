//Each application process Ax must contain a loop of up to MAX iterations 
//and have an iteration counter called PC.

//The loop body should contain a sleep(1) statement, and the time intervals 
//after the start of each syscall (D1, R, or W) should be defined.

#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

#define MAX_ITERATIONS 20

void application_process(int id) {

    int pc = 0;

    while (pc < MAX_ITERATIONS) {

        printf("A%d running | PC = %d\n", id, pc);

        sleep(1);

        if (pc == 4 || pc == 10 || pc == 15) {

            printf("A%d requesting I/O\n", id);

            // notify kernel
            kill(getppid(), SIGUSR1);

            // block process
            raise(SIGSTOP);
        }

        pc++;
    }

    printf("A%d finished\n", id);

    exit(0);
}


// if (pc == 4 || pc == 10)

// int io_points[] = {4, 10, 15};


// for (int i = 0; i < 3; i++) {

//     if (pc == io_points[i]) {

//         printf("A%d requesting I/O\n", id);

//         kill(getppid(), SIGUSR1);

//         raise(SIGSTOP);
//     }
// }