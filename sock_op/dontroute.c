#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>

int main() {
  int tcpSocket = socket(PF_INET, SOCK_STREAM, 0);

  int optval;
  int optvalLen = sizeof(optval);

  getsockopt(tcpSocket, SOL_SOCKET, SO_DONTROUTE, &optval, &optvalLen);
  if(optval == 0) {
    printf("메시지를 전송할 때 라우팅 테이블을 참조합니다.\n");
  }
  else {
    printf("메시지를 전송할 때 라우팅 테이블을 참조하지 않습니다.\n");
  }

  optval = 1;
  setsockopt(tcpSocket, SOL_SOCKET, SO_DONTROUTE, &optval, optvalLen);
  getsockopt(tcpSocket, SOL_SOCKET, SO_DONTROUTE, &optval, &optvalLen);
  if(optval == 0) {
    printf("메시지를 전송할 때 라우팅 테이블을 참조합니다.\n");
  }
  else {
    printf("메시지를 전송할 때 라우팅 테이블을 참조하지 않습니다.\n");
  }

  return 0;
}
