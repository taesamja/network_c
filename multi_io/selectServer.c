#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>

#define BUFFERSIZE 50
#define PORT 11111

int main() {
  int serverSocket = socket(PF_INET, SOCK_STREAM, 0);

  struct sockaddr_in serverAddress;
  memset(&serverAddress, 0, sizeof(serverAddress));
  serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
  serverAddress.sin_family = AF_INET;
  serverAddress.sin_port = htons(PORT);

  bind(serverSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress));
  printf("서버 소켓에 bind()함수를 호출해서 IP와 PORT를 설정했습니다.\n\n");

  listen(serverSocket, 5);
  printf("클라이언트가 접속하기를 기다리고 있습니다.\n\n");

  fd_set readSet;
  fd_set tempSet;

  FD_ZERO(&tempSet);
  FD_ZERO(&readSet);

  FD_SET(serverSocket, &tempSet);

  int fdmax;
  fdmax = serverSocket;

  while(1) {
    readSet = tempSet;
    printf("읽기 셋에 변화가 생길때까지 대기합니다.\n\n");

    if(select(fdmax+1, &readSet, NULL, NULL, NULL) == -1) {
      printf("select() 함수 실행 중에 에러가 발생 했습니다.\n\n");
      return 0;
    }
    printf("소켓에 변화가 발생해서 select 함수의 대기 상태가 해제 되었습니다.\n");

    int fd;
    for(fd = 0; fd<fdmax+1;fd++) {
      if(FD_ISSET(fd, &readSet) != 0) {
        if(fd == serverSocket) {
          int clientSocket = accept(serverSocket, NULL, NULL);
          printf("클라이언트가 접속했습니다.^^\n\n");
          FD_SET(clientSocket, &tempSet);
          printf("클라이언트 소켓을 tempSet에 삽입했습니다.\n\n");
          fdmax = clientSocket;
        }
        else {
          char fromClient[BUFFERSIZE];
          int strlen = read(fd, fromClient, BUFFERSIZE);
          if(strlen == 0) {
            FD_CLR(fd, &tempSet);
            close(fd);
            printf("클라이언트 하나가 종료 되었습니다.\n");
          }
          else {
            write(fd, fromClient, strlen);
          }
        }
      }
    }
  }

  return 0;
}
