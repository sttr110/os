#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <sys/un.h>
#include <unistd.h>

int main(void)
{
  int server_sockfd , client_sockfd ;
  int server_len , client_len;
  struct sockaddr_un server_address ;
  struct sockaddr_un client_address ;

  unlink("server_socket");
  server_sockfd = socket(AF_UNIX,SOCK_STREAM,0);
  server_address.sun_family = AF_UNIX ;
  strcpy(server_address.sun_path , "server_socket");
  server_len = sizeof(server_address);
  bind(server_sockfd , (struct sockaddr *)&server_address , server_len);

  printf("starting...\n\n");

  listen(server_sockfd , 5);
  while(1) {
    char *buff;
    int rc;

    printf("server waiting\n");

    client_sockfd = accept(server_sockfd ,
        (struct sockaddr *)&client_address , &client_len);


    rc = read(client_sockfd,buff ,5);

    //buff[rc] = '\0';
    printf("%s\n", buff);

    write(client_sockfd,buff,1);
    close(client_sockfd);
  }
}
