#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>

#define PORT 11111
#define BUFFERSIZE 100

int main() {
  int clientSocket = socket(PF_INET, SOCK_STREAM, 0);
  printf("클라이언트 소켓을 생성했습니다.\n");

  struct sockaddr_in serverAddress;
  memset(&serverAddress, 0, sizeof(serverAddress));
  serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1");
  serverAddress.sin_family = AF_INET;
  serverAddress.sin_port = htons(PORT);

  connect(clientSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress));

  pid_t pid = fork();
  if(pid == -1) {
    printf("자식 프로세스를 생성하지 못했습니다.\n");
    exit(0);
  }
  else {
    if(pid > 0) {
      while(1) {
        char fromServer[BUFFERSIZE];
        int strlen = read(clientSocket, fromServer, BUFFERSIZE);
        if(strlen == 0) {
          printf("서버와의 연결이 종료되었습니다.\n");
          exit(0);
        }
        printf("%s\n", fromServer);
      }
    }
    else {
      printf("전송할 메시지를 입력하세요. 종료시 'q'를 입력하세요.\n");

      char toServer[BUFFERSIZE];
      while(1) {
        fgets(toServer, BUFFERSIZE, stdin);
        toServer[strlen(toServer)]='\0';

        if(strcmp(toServer, "q\n")==0) {
          printf("서버와의 연결이 종료되었습니다.\n");
          shutdown(clientSocket, SHUT_WR);
          close(clientSocket);
          exit(0);
        }

        write(clientSocket, toServer, strlen(toServer)+1);
        printf("서버로 전송한 메시지 %s\n", toServer);
      }
    }
  }

  return 0;
}
