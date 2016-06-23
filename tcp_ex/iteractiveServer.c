#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>

#define PORT 11111

int main() {
  int serverSocket = socket(PF_INET, SOCK_STREAM, 0);

  struct sockaddr_in serverAddress;
  memset(&serverAddress, 0, sizeof(serverAddress));
  serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
  serverAddress.sin_family = AF_INET;
  serverAddress.sin_port = htons(PORT);

  bind(serverSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress));

  listen(serverSocket,5);
  printf("클라이언트의 접속을 기다립니다.....\n\n");

  int clientSocket;
  while(1) {
    clientSocket = accept(serverSocket, NULL, NULL);

    char clientName[100];
    read(clientSocket, clientName, sizeof(clientName));
    printf("%s님이 접속했습니다.\n\n", clientName);

    char toClient[100];
    sprintf(toClient, "%s님 안녕 *^^*\n", clientName);
    write(clientSocket, toClient, sizeof(toClient));
    printf("클라이언트로 전송한 메시지-->%s\n", toClient);

    close(clientSocket);
  }

  close(serverSocket);
  return 0;
}
