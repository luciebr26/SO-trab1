//This simulates hardware interrupts.
//Similar to an alarm clock, it's job is to wake up the kerenel

//generates the interrupts related to the clock and the completion of the i/o operation on device1
//IRQ0 (time slice) ad IRQ1 (device 1)
//infinite process that runs parrallel with kerenelsim

//hardware interrupt
//interrupt nesting - to manage multiple devices
//priortity scheme


//use signal() to generate an interrupt

//pre emptive scheduling

// To do this, implement the InterController Sim to generate:
// ∙ An IRQ0 every 1 second indicates the end of the process timeslice (use sleep() inside the loop body).
// ∙ An IRQ1 is triggered every 3 seconds after each process's I/O request, indicating the end of the I/O operation.

/*

 #include <signal.h>
 #include <stdio.h>
 #include <unistd.h>

 pid_t kernel_pid; 

 void interrupt_controller(){

    //irq0
    while(1){

        sleep(1);

        printf("[INTERRUPT] IRQ0 - timer interrupt\n");

        kill(kernel_pid, SIGALRM);
    }

    pid_t io_timer = fork();

    //irq1
    if(io_timer == 0){

        sleep(3);

        kill(kernel_pid, SIGUSR2);

        exit(0);
    }



 }



*/