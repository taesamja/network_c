#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>

#define BUFFERSIZE 50
#define PORT 11111

int main() {
  int serverSocket = socket(PF_INET, SOCK_DGRAM, 0);

  struct sockaddr_in serverAddress;
  memset(&serverAddress, 0, sizeof(serverAddress));
  serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
  serverAddress.sin_family = AF_INET;
  serverAddress.sin_port = htons(PORT);

  bind(serverSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress));
  printf("클라이언트에서 데이터를 보내 오기를 기다리고 있습니다.\n");

  char fromClient[BUFFERSIZE];
  char toClient[BUFFERSIZE];

  struct sockaddr_in clientAddress;
  int clientAddress_size;

  while(1) {
    clientAddress_size = sizeof(clientAddress);

    recvfrom(serverSocket, fromClient, BUFFERSIZE, 0,
             (struct sockaddr *)&clientAddress, &clientAddress_size);
    printf("앗!! 클라이언트가 메시지를 전송하였습니다.\n");
    printf("클라이언트로부터 전달된 메시지:%s\n", fromClient);

    sprintf(toClient, "UDP 클라이언트 반가워!!!\n");
    sendto(serverSocket, toClient, BUFFERSIZE, 0,
           (struct sockaddr *)&clientAddress, sizeof(clientAddress));
    printf("클라이언트로 전달한 메시지:%s\n", toClient);
  }

  close(serverSocket);

  return 0;
}
