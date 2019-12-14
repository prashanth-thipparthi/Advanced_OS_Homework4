#define _GNU_SOURCE
#include <sys/wait.h>
#include <sys/utsname.h>
#include <sched.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define errExit(msg)    do { perror(msg); exit(EXIT_FAILURE); } while (0)

static int              /* Start function for cloned child */
childFunc(void *arg)
{
   char* arr[] = {"/bin/bash",NULL};

   if (chroot("/home/sai/Dropbox/Adv_os/home_work_4/os_hw_4/capsule") != 0) {
       perror("chroot /tmp");
       return 1;
   }

   execv("/bin/bash", arr);
   return 0;           /* Child terminates now */
}

#define STACK_SIZE (1024 * 1024)    /* Stack size for cloned child */

int main(int argc, char *argv[])
{
   char *stack;                    /* Start of stack buffer */
   char *stackTop;                 /* End of stack buffer */
   pid_t pid;
   struct utsname uts;
   long c_pid;
   char cmd_buf1[100];
   char cmd_buf2[100];
   char cmd_buf3[100];

   if (argc < 2) {
       fprintf(stderr, "Usage: %s <child-hostname>\n", argv[0]);
       exit(EXIT_SUCCESS);
   }

   /* Allocate stack for child */

   stack = malloc(STACK_SIZE);
   if (stack == NULL)
       errExit("malloc");
   stackTop = stack + STACK_SIZE;  /* Assume stack grows downward */

   /* Create child that has its own UTS namespace;
      child commences execution in childFunc() */

   pid = clone(childFunc, stackTop, CLONE_NEWPID | CLONE_NEWIPC | CLONE_NEWNET | CLONE_NEWNS | CLONE_NEWUTS | SIGCHLD, argv[1]);
   
   c_pid = (long) pid;

   snprintf(cmd_buf1, 100, "echo %ld > /sys/fs/cgroup/cpu/cpulimit/cgroup.procs", c_pid);
   system(cmd_buf1);

   snprintf(cmd_buf2, 100, "echo %ld > /sys/fs/cgroup/memory/memorylimit/cgroup.procs", c_pid);
   system(cmd_buf2);

   snprintf(cmd_buf3, 100, "echo %ld > /sys/fs/cgroup/blkio/iolimit/cgroup.procs", c_pid);
   system(cmd_buf3);

   if (pid == -1)
       errExit("clone");
   printf("clone() returned %ld\n", (long) pid);

   /* Parent falls through to here */

   sleep(1);           /* Give child time to change its hostname */

   if (waitpid(pid, NULL, 0) == -1)    /* Wait for child */
       errExit("waitpid");
   printf("child has terminated\n");

   exit(EXIT_SUCCESS);
}

