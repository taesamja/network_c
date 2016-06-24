#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>

#define PORT 11111

int main() {
  int clientSocket = socket(PF_INET, SOCK_STREAM, 0);
  printf("클라이언트 소켓을 생성했습니다.\n");

  struct sockaddr_in serverAddress;
  memset(&serverAddress, 0, sizeof(serverAddress));
  serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1");
  serverAddress.sin_family = AF_INET;
  serverAddress.sin_port = htons(PORT);

  connect(clientSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress));
  printf("서버에 접속했습니다.\n");

  char toServer[] = "서버 안녕";
  char fromServer[100];

  write(clientSocket, toServer, sizeof(toServer));
  printf("서버로 보낸 메시지: %s\n", toServer);

  read(clientSocket, fromServer, sizeof(fromServer));
  printf("서버에서 되돌아 온 메시지: %s\n", fromServer);

  close(clientSocket);
  return 0;
}
