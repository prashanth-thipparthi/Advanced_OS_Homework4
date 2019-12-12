#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <sched.h>
#include <sys/wait.h>
#include <errno.h>

#define STACKSIZE (1024*1024)
static char child_stack[STACKSIZE];

struct clone_args {
        char **argv;
};

static int child_fn()
{
    printf("PID: %ld\n", (long)getpid());
    printf("Parent PID: %ld\n", (long)getppid());
    return 0; 
}

int main(int argc, char **argv)
{
   pid_t child_pid = clone(child_fn, child_stack+1048576, CLONE_NEWPID | SIGCHLD, NULL);
   if(child_pid == -1) {
       printf("Error in creating clone");  
       exit(0); 
   }
   printf("clone() = %ld\n", (long)child_pid);
   waitpid(child_pid, NULL, 0);
   return 0; 
}
