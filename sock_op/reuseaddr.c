//라즈베리파이에서는 동작하지 않음.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>

#define PORT 11111
#define BUFFERSIZE 500

int main() {
  int serverSocket = socket(PF_INET, SOCK_STREAM, 0);
  printf("서버 소켓을 생성했습니다.\n");

  /***reuseadd 옵션 설정 부분*********************************/
  int optval = 1;
  setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, (void *)&optval, sizeof(optval));
  /**********************************************************/

  struct sockaddr_in serverAddress;
  memset(&serverAddress, 0, sizeof(serverAddress));
  serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
  serverAddress.sin_family = AF_INET;
  serverAddress.sin_port = htons(PORT);

  int state = bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress));
  if(state == -1) {
    printf("서버 소켓에 아이피와 포트를 설정하는 bind()함수를 실행하지 못했습니다. 해당 IP와 포트는 다른 프로그램에서 사용 중입니다.\n");
    printf("서버 프로그램을 종료합니다.\n");
    return 0;
  }
  printf("서버 소켓에 bind()함수를 호출해서 IP와 포트를 설정했습니다.\n");

  listen(serverSocket, 5);
  printf("클라이언트가 접속하기를 기다리고 있습니다.\n");
  accept(serverSocket, NULL, NULL);
  printf("앗 클라이언트가 접속했습니다.\n");

  char toClient[BUFFERSIZE];
  sprintf(toClient, "클라이언트 방가워!!\n");
  write(serverSocket, toClient, BUFFERSIZE);
  printf("클라이언트로 전달한 메시지:%s\n", toClient);

  close(serverSocket);
  return 0;
}
