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
  int clientSocket = socket(PF_INET, SOCK_STREAM, 0);
  printf("클라이언트 소켓 생성\n");

  struct sockaddr_in serverAddress;
  memset(&serverAddress, 0, sizeof(serverAddress));
  serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1");
  serverAddress.sin_family = AF_INET;
  serverAddress.sin_port = htons(PORT);

  connect(clientSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress));
  printf("서버에 접속했습니다.\n");

  char fromServer[BUFFERSIZE];
  read(clientSocket, fromServer, sizeof(fromServer));
  printf("서버로 부터 전달된 메시지: %s\n", fromServer);

  char toServer[BUFFERSIZE];
  sprintf(toServer, "서버 너두 방가워.!!!\n");
  write(clientSocket, toServer, sizeof(toServer));

  close(clientSocket);
  return 0;
}
