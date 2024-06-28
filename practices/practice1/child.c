#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char const *argv[]){
   
   printf("Main pid: %d, parend pid: %d\n", getpid(), getppid());

   pid_t child_pid = fork();

   if (child_pid == 0){
       printf("Child process pid(%d), ppid(%d)\n", getpid(), getppid());

       pid_t grandchild_pid = fork();

       if (grandchild_pid == 0){
           printf("Grandchild process pid(%d), ppid(%d)\n", getpid(), getppid());
           sleep(5);
           printf("Finish grandchild block.\n");
       }else{
           wait(NULL);
           printf("Finish child block.\n");
       }
   }else{
       // Parent process
       wait(NULL);
       printf("Finish parent block.\n");
   }
   
   printf("Finish main process pid(%d), ppid(%d).\n", getpid(), getppid());

   return 0;
}