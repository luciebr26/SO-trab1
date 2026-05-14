#include "kernel.h"

void stopHandler(int signal){

}

void contHandler(int signal){

}

void IRQ0Handler(int signal){
    kill(a[i], SIGSTOP);
    kill(a[i+1], SIGCONT);
}

void IRQ1Handler(int signal){

}

