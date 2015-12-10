#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <sys/ioctl.h>
#include <net/if.h>

int getIpAddr(void) {
  int fd, addr;
  struct ifreq ifr;

  fd = socket(AF_INET, SOCK_DGRAM, 0);
  ifr.ifr_addr.sa_family = AF_INET;
  strncpy(ifr.ifr_name, "lo", IFNAMSIZ-1);
  ioctl(fd, SIOCGIFADDR, &ifr);
  close(fd);
  addr = inet_addr(inet_ntoa(((struct sockaddr_in *)&ifr.ifr_addr)->sin_addr));

  return addr;
}

int main(void)
{
  int port, server_sockfd, client_sockfd, server_len, client_len;
  struct sockaddr_in server_address;
  struct sockaddr_in client_address;

  printf("PORT: ");
  scanf("%d", &port);

  server_sockfd = socket(AF_INET,SOCK_STREAM,0);
  server_address.sin_family = AF_INET;
  server_address.sin_addr.s_addr = getIpAddr(); 
  server_address.sin_port = htons(port);

  server_len = sizeof(server_address);
  bind(server_sockfd , (struct sockaddr *)&server_address , server_len);

  listen(server_sockfd , 5);

  while(1) {
    char *buff;

    printf("server waiting\n");

    client_sockfd = accept(server_sockfd,
        (struct sockaddr *)&client_address, &client_len);

    read(client_sockfd, &buff, sizeof(buff));

    printf("%s\n", &buff);

    write(client_sockfd, buff, sizeof(buff));
    close(client_sockfd);
  }
}
