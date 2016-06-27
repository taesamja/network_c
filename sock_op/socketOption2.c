//rpi 셋팅은 2의 배수이다. 예) 2*1 = 2배 / 2*2 = 4배
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>

int main() {
  int tcpSocket = socket(PF_INET, SOCK_STREAM, 0);

  socklen_t rcvBufferSize = 0;
  int rcvBufferSizeLen = sizeof(rcvBufferSize);
  getsockopt(tcpSocket, SOL_SOCKET, SO_RCVBUF, &rcvBufferSize, &rcvBufferSizeLen);
  printf("수신 버퍼의 사이즈는 %d 입니다.\n", rcvBufferSize);

  int sndBufferSize = 0;
  socklen_t sndBufferSizeLen = sizeof(sndBufferSize);
  getsockopt(tcpSocket, SOL_SOCKET, SO_SNDBUF, &sndBufferSize, &sndBufferSizeLen);
  printf("송신 버퍼의 사이즈는 %d 입니다.\n", sndBufferSize);

  rcvBufferSize *= 2; // 4배
  setsockopt(tcpSocket, SOL_SOCKET, SO_RCVBUF, &rcvBufferSize, rcvBufferSizeLen);

  sndBufferSize *= 2; // 4배
  setsockopt(tcpSocket, SOL_SOCKET, SO_SNDBUF, &sndBufferSize, sndBufferSizeLen);

  getsockopt(tcpSocket, SOL_SOCKET, SO_RCVBUF, &rcvBufferSize, &rcvBufferSizeLen);
  printf("변경된 수신 버퍼의 사이즈는 %d 입니다.\n", rcvBufferSize);

  getsockopt(tcpSocket, SOL_SOCKET, SO_SNDBUF, &sndBufferSize, &sndBufferSizeLen);
  printf("변경된 송신 버퍼의 사이즈는 %d 입니다.\n", sndBufferSize);

  return 0;
}
