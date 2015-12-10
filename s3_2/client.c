#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

int main(void)
{
  int sockfd, len, port, result ;
  struct sockaddr_in address ;
  char *text = "Hello World";
  char ip_ad[124]; 
  
  printf("PORT: ");
  scanf("%d", &port);

  printf("IP: ");
  scanf("%s", ip_ad);

  sockfd = socket(AF_INET,SOCK_STREAM,0);

  address.sin_family = AF_INET ;
  address.sin_addr.s_addr = inet_addr(ip_ad);
  address.sin_port = htons(port) ;
  len = sizeof(address);
  result = connect(sockfd , (struct sockaddr *)&address , len);

  if ( result == -1 ) {
    perror("can not connect");
    exit(1);
  }

  write(sockfd, text,sizeof(text));
  read(sockfd, text,sizeof(text));

  printf("Receipt completion\n");
  close(sockfd);
  exit(0);
}

