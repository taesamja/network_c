#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>

#define PORT 11111
#define BUFFERSIZE 100

int main() {
  int serverSocket = socket(PF_INET, SOCK_STREAM, 0);

  int optval;
  int optvalLen = sizeof(optval);

  getsockopt(serverSocket, SOL_SOCKET, SO_KEEPALIVE, &optval, &optvalLen);
  if(optval == 0) {
    printf("서버 소켓에 2시간 마다 클라이언트들과 연결여부를 체크하는 \nSO_KEEPALIVE 옵션이 설정되지 않았습니다.\n");
  }
  else {
    printf("서버 소켓에 2시간 마다 클라이언트들과 연결여부를 체크하는 \nSO_KEEPALIVE 옵션이 설정되었습니다.\n");
  }

  optval = 1;
  setsockopt(serverSocket, SOL_SOCKET, SO_KEEPALIVE, &optval, optvalLen);
  getsockopt(serverSocket, SOL_SOCKET, SO_KEEPALIVE, &optval, &optvalLen);
  if(optval == 0) {
    printf("서버 소켓에 2시간 마다 클라이언트들과 연결여부를 체크하는 \nSO_KEEPALIVE 옵션이 설정되지 않았습니다.\n");
  }
  else {
    printf("서버 소켓에 2시간 마다 클라이언트들과 연결여부를 체크하는 \nSO_KEEPALIVE 옵션이 설정되었습니다.\n");
  }

  struct sockaddr_in serverAddress;
  memset(&serverAddress, 0, sizeof(serverAddress));
  serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
  serverAddress.sin_family = AF_INET;
  serverAddress.sin_port = htons(PORT);

  bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress));
  printf("서버소켓에 bind()함수를 호출해서 IP와 PORT를 설정했습니다.\n");

  listen(serverSocket, 5);
  printf("클라이언트가 접속하기를 기다리고 있습니다.\n");

  while(1) {
    int clientSocket = accept(serverSocket, NULL, NULL);
    printf("앗 클라이언트가 접속하였습니다.\n");

    getsockopt(clientSocket, SOL_SOCKET, SO_KEEPALIVE, &optval, &optvalLen);
    if(optval == 0) {
      printf("클라이언트 소켓에 2시간 마다 클라이언트들과 연결여부를 체크하는 \nSO_KEEPALIVE 옵션이 설정되지 않았습니다.\n");
    }
    else {
      printf("클라이언트 소켓에 2시간 마다 클라이언트들과 연결여부를 체크하는 \nSO_KEEPALIVE 옵션이 설정되었습니다.\n");
    }

    char toClient[BUFFERSIZE];
    sprintf(toClient, "클라이언트 방가워!!!\n");
    write(clientSocket, toClient, BUFFERSIZE);
    printf("클라이언트로 전달한 메시지:%s\n", toClient);
  }

  close(serverSocket);
  return 0;
}
