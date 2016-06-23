#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>

#define PORT 11111

int main(int argc, char **argv) {
  int clientSocket = socket(PF_INET, SOCK_STREAM, 0);

  struct sockaddr_in serverAddress;
  memset(&serverAddress, 0, sizeof(serverAddress));
  serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1");
  serverAddress.sin_family = AF_INET;
  serverAddress.sin_port = htons(PORT);

  connect(clientSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress));

  char myName[100];
  strcpy(myName, argv[1]);
  write(clientSocket, myName, sizeof(myName));
  printf("서버로 보낸 클라이언트의 이름-->%s\n\n", myName);

  char fromServer[100];
  read(clientSocket, fromServer, sizeof(fromServer));
  printf("서버로 부터 온 메시지-->%s\n\n", fromServer);

  close(clientSocket);
  return 0;
}
