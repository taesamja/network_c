#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>

#define BUFFERSIZE 30
#define PORT 11111

int main() {
  int clientSocket = socket(PF_INET, SOCK_DGRAM, 0);

  struct sockaddr_in serverAddress;
  memset(&serverAddress, 0, sizeof(serverAddress));
  serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1");
  serverAddress.sin_family = AF_INET;
  serverAddress.sin_port = htons(PORT);

  char toServer[BUFFERSIZE];
  char fromServer[BUFFERSIZE];

  sprintf(toServer, "UDP 서버 안녕!!!\n");
  sendto(clientSocket, toServer, BUFFERSIZE, 0,
         (struct sockaddr*)&serverAddress, sizeof(serverAddress));
  printf("서버로 전달한 메시지:%s\n", toServer);

  recvfrom(clientSocket, fromServer, BUFFERSIZE, 0,
           NULL, NULL);
  printf("서버로 부터 전달된 메시지:%s\n", fromServer);

  close(clientSocket);
  return 0;
}
