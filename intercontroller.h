/*definition interruption
Para isso, implemente o InterConntoller Sim para gerar:
- Um IRQ0 a cada 1s indicando o fim do timeslice dos processos (use sleep() dentro do
corpo do loop)
- Um IRQ1 a cada 3s após o pedido de I/O de cada processo indicando o final da operação
de I/O
*/
//#include "kernel.h"
#include "app.h"
#include <sys/types.h>

#ifndef INTERRUPT_CONTROLLER_H
#define INTERRUPT_CONTROLLER_H

void intercontroller(pid_t kernel_pid);

void io_timer(pid_t kernel_pid);

#endif