#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main()
{
  int pid;
  int status;
  int pp[2]; 
  char *text = "hello";

  printf("parent process ID : %d\n", getpid());

  //create pipe
  pipe(pp);
  write(pp[1], text, strlen(text));

  if ((pid = fork()) == 0) {
    //start child
    printf("child process ID : %d\n", getpid());

    char buf[128];
    read(pp[0], buf, sizeof buf);

    printf("%s\n", buf);
    //end child
  } else {
    if (pid != -1) {
      wait(&status);
      //end parent 
    } else {
      perror("parent : ");
    }
  }

  return 0;
}
