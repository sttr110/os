#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

struct sockaddr_in
{
  short int  sin_family ;
  int        sin_port; 
  int        sin_addr;
};

int main(void) {
  struct sockaddr_in server_address;
  int sockfd;
  int new_sockfd;
  int port;
  int addr_len;
  char hostname[100];
  struct hostent *myhost;
  
  
  //create socket
  if ((sockfd = socket(AF_INET, SOCK_STREAM,0)) < 0 ) {
    fprintf(stderr,"Socket for server failed.\n");
    return -1;
  }
  printf("%d\n", &sockfd);

  //ホスト名の取得
  gethostname(hostname,256);

  //ホスト名からIPアドレスへ変換
  //if((myhost = gethostbyname(hostname)) == NULL) {
  //  fprintf(stderr,"bad hostname!\n");
  //  return -1;
  //}
  //printf("%d\n", myhost);

  //ポート番号を入力
  scanf("%d", &port);

  //構造体に情報を代入
  server_address.sin_family = AF_INET;
  server_address.sin_port = port;
  server_address.sin_addr = inet_addr("192.168.33.10");
  addr_len = sizeof(server_address.sin_addr) ;

  //ソケットにIPアドレスとポート番号を設定
  bind(sockfd, (struct sockaddr *)&server_address, addr_len);

  //ネクト要求をいくつまで待つかを設定 
  //ソケット接続準備 
  if (listen(sockfd, 5) < 0) {
    perror("reader: listen");
    close(sockfd);
    exit(1);
  }


  //ソケット接続待機 違う予感
  if ((new_sockfd = accept(sockfd,(struct sockaddr *)&server_address, &addr_len)) < 0) {
    perror("reader: accept");
    exit(1);
  }
  return 0;
}
