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
    processos();
    while (1) {
        sleep(1);
    }
    return 0;
    
}

