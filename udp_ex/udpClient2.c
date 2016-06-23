#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>

#define PORT 11111
#define BUFFERSIZE 30

int main() {
  int clientSocket = socket(PF_INET, SOCK_DGRAM, 0);

  struct sockaddr_in serverAddress;
  memset(&serverAddress, 0, sizeof(serverAddress));
  serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1");
  serverAddress.sin_family = AF_INET;
  serverAddress.sin_port = htons(PORT);

  connect(clientSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress));

  char toServer[BUFFERSIZE];
  char fromServer[BUFFERSIZE];

  sprintf(toServer, "UDP 서버 안녕!!!\n");
  write(clientSocket, toServer, BUFFERSIZE);
  printf("서버로 전달한 메시지:%s\n", toServer);

  read(clientSocket, fromServer, BUFFERSIZE);
  printf("서버로 부터 전송된 메시지: %s\n", fromServer);

  close(clientSocket);
  return 0;
}
