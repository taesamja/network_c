#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>

int main() {
  int tcpSocket = socket(PF_INET, SOCK_STREAM, 0);
  int udpSocket = socket(PF_INET, SOCK_DGRAM, 0);

  int socketType1 = -1;
  int typeLen1 = sizeof(socketType1);
  getsockopt(tcpSocket, SOL_SOCKET, SO_TYPE, &socketType1, &typeLen1);
  if(socketType1 == SOCK_STREAM) {
    printf("첫번째 소켓의 타입은 TCP 소켓입니다.\n");
  }
  else {
    printf("첫번째 소켓의 타입은 UDP 소켓입니다.\n");
  }

  int socketType2 = -1;
  int typeLen2 = sizeof(socketType2);
  getsockopt(udpSocket, SOL_SOCKET, SO_TYPE, &socketType2, &typeLen2);
  if(socketType2 == SOCK_STREAM) {
    printf("두번째 소켓의 타입은 TCP 소켓입니다.\n");
  }
  else {
    printf("두번째 소켓의 타입은 UDP 소켓입니다.\n");
  }

  return 0;  
}
