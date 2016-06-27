#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/tcp.h>
#include <netinet/ip.h>

int main() {
  int tcpSocket = socket(PF_INET, SOCK_STREAM, 0);

  int optval;
  int optvalLen = sizeof(optval);
  getsockopt(tcpSocket, IPPROTO_TCP, TCP_NODELAY, &optval, &optvalLen);
  if(optval == 0) {
    printf("nagle 알고리즘이 설정되었습니다.\n");
  }
  else {
    printf("nagle 알고리즘이 설정되지 않았습니다.\n");
  }

  optval = 1;
  setsockopt(tcpSocket, IPPROTO_TCP, TCP_NODELAY, &optval, optvalLen);
  getsockopt(tcpSocket, IPPROTO_TCP, TCP_NODELAY, &optval, &optvalLen);
  if(optval == 0) {
    printf("nagle 알고리즘이 설정되었습니다.\n");
  }
  else {
    printf("nagle 알고리즘이 설정되지 않았습니다.\n");
  }

  close(tcpSocket);
  return 0;
}
