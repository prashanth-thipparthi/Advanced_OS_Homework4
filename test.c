#define _GNU_SOURCE
#include <sys/wait.h>
#include <sys/utsname.h>
#include <sched.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define errExit(msg)    do { perror(msg); exit(EXIT_FAILURE); } while (0)


int main(int argc, char *argv[]) {
   chdir("/home/sai/Dropbox/Adv_os/home_work_4/os_hw_4");
   if (chroot("/home/sai/Dropbox/Adv_os/home_work_4/os_hw_4/capsule") != 0) {
     perror("chroot /tmp");
   return 1;
   }
   return 0;
}
