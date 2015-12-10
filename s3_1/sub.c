#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main()
{
  int pid;
  int status;
  char program[100];
  scanf("%s", program);


  if ((pid = fork()) == 0) {
    execvp(program, NULL);
  }

  waitpid(pid, &status, 0);
  if(WIFEXITED(status)) {
  }

  return 0;
}
