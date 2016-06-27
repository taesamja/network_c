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

  linger optval;
  int optvalLen = sizeof(optvalLen);
  getsockopt(serverSocket, SOL_SOCKET, SO_LINGER, &optval, &optvalLen);
  printf("*************************************************\n");
  if(optval.l_onoff == 0) {
    printf("close() 함수 호출 시 서버 소켓은 바로 종료됩니다.\n");
  }
  else {
    printf("close() 함수 호출 시 서버 소켓은 바로 종료되지 않고, 전송하지 못한 메시지를 전송하고 종료됩니다.\n");
  }
  printf("close() 함수 호출 시 전송하지 못한 메시지가 있다면 서버 소켓은 %d 초 후에 종료됩니다.\n", optval.l_linger);
  printf("*************************************************\n");

  optval.l_onoff = 1;
  optval.l_linger = 10;
  setsockopt(serverSocket, SOL_SOCKET, SO_LINGER, &optval, optvalLen);
  getsockopt(serverSocket, SOL_SOCKET, SO_LINGER, &optval, &optvalLen);
  printf("*************************************************\n");
  if(optval.l_onoff == 0) {
    printf("close() 함수 호출 시 서버 소켓은 바로 종료됩니다.\n");
  }
  else {
    printf("close() 함수 호출 시 서버 소켓은 바로 종료되지 않고, 전송하지 못한 메시지를 전송하고 종료됩니다.\n");
  }
  printf("close() 함수 호출 시 전송하지 못한 메시지가 있다면 서버 소켓은 %d 초 후에 종료됩니다.\n", optval.l_linger);
  printf("*************************************************\n");

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
    printf("앗 클라이언트가 접속했습니다.\n");
    getsockopt(clientSocket, SOL_SOCKET, SO_LINGER, &optval, &optvalLen);
    printf("*************************************************\n");
    if(optval.l_onoff == 0) {
      printf("close() 함수 호출 시 클라이언트 소켓은 바로 종료됩니다.\n");
    }
    else {
      printf("close() 함수 호출 시 클라이언트 소켓은 바로 종료되지 않고, 전송하지 못한 메시지를 전송하고 종료됩니다.\n");
    }
    printf("close() 함수 호출 시 전송하지 못한 메시지가 있다면 클라이언트 소켓은 %d 초 후에 종료됩니다.\n", optval.l_linger);

    printf("*************************************************\n");
    char toClient[BUFFERSIZE];
    sprintf(toClient, "클라이언트 방가워!!!\n");
    write(clientSocket, toClient, BUFFERSIZE);
    printf("클라이언트로 전달한 메시지:%s\n", toClient);

    char fromClient[BUFFERSIZE];
    int strlen = read(clientSocket, fromClient, BUFFERSIZE);
    if(strlen >= 0) {
      printf("클라이언트로부터 전달된 메시지: %s\n", fromClient);
    }
    printf("*************************************************\n");
  }

  close(serverSocket);
  return 0;
}
