#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <time.h>

#define PORT 11111
#define BUFFERSIZE 50

int main() {
  int serverSocket = socket(PF_INET, SOCK_DGRAM, 0);

  struct sockaddr_in serverAddress;
  memset(&serverAddress, 0, sizeof(serverAddress));
  serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
  serverAddress.sin_family = AF_INET;
  serverAddress.sin_port = htons(PORT);

  bind(serverSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress));
  printf("클라이언트에서 시간을 물어보기를 기다리고 있습니다. \n");

  char fromClient[BUFFERSIZE];
  char toClient[BUFFERSIZE];

  struct sockaddr_in clientAddress;
  int clientAddress_size;

  while(1) {
    clientAddress_size = sizeof(clientAddress);

    recvfrom(serverSocket, fromClient, BUFFERSIZE, 0,
            (struct sockaddr *)&clientAddress, &clientAddress_size);
    printf("앗!! 클라이언트가 시간을 물어봤습니다.\n");
    printf("클라이언트로 부터 전달된 메시지:%s\n", fromClient);

    time_t t_time;
    time(&t_time);
    struct tm *newTime = localtime(&t_time);
    sprintf(toClient, "현재시간: %d:%d:%d \n",newTime->tm_hour + 9, newTime->tm_min, newTime->tm_sec );
    sendto(serverSocket, toClient, BUFFERSIZE, 0,
          (struct sockaddr *)&clientAddress, sizeof(clientAddress));
    printf("클라이언트로 전달한 메시지:%s\n", toClient);
  }

  close(serverSocket);
  return 0;
}
