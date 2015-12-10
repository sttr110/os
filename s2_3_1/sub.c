#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int num = 0;

int main()
{
  int pid;
  int status;

  if ((pid = fork()) == 0) {
    //child process
    num = num + 10; 
  } 

  waitpid(pid, &status, 0);
  if(WIFEXITED(status)) {
    printf("%d\n", num);
  }

  return 0;
}
