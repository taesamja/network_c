#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/time.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <signal.h>

#define BUFFERSIZE 100
#define PORT 11111

void child_end(int signal);

int main() {
  int serverSocket = socket(PF_INET, SOCK_STREAM, 0);

  struct sockaddr_in serverAddress;
  memset(&serverAddress, 0, sizeof(serverAddress));
  serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
  serverAddress.sin_family = AF_INET;
  serverAddress.sin_port = htons(PORT);

  bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress));
  printf("서버 소켓에 bind()함수를 호출해서 IP와 PORT를 설정했습니다.\n\n");

  listen(serverSocket, 5);
  printf("클라이언트가 접속하기를 기다리고 있습니다.\n\n");

  struct sigaction signal;
  signal.sa_handler = child_end;
  sigemptyset(&signal.sa_mask);
  signal.sa_flags = 0;

  int state = sigaction(SIGCHLD, &signal, 0);
  if(state!=0) {
    printf("시그널 생성시 오류가 발생했습니다.\n");
  }

  while(1) {
    int clientSocket = accept(serverSocket, NULL, NULL);
    if(clientSocket == -1) {
      continue;
    }

    pid_t pid = fork();
    if(pid == -1) {
      close(clientSocket);
      continue;
    }
    else {
      if(pid > 0) {
        printf("\n클라이언트와 연결되어 자식 프로세스를 생성했습니다.\n");
        close(clientSocket);
        continue;
      }
      else {
        char fromClient[BUFFERSIZE];
        char toClient[BUFFERSIZE];
        close(serverSocket);

        while(1) {
          printf("\n클라이언트가 전송한 메시지를 읽어 들입니다.\n");
          int strlen = read(clientSocket, fromClient, BUFFERSIZE);
          if(strlen == 0) {
            printf("\n클라이언트와의 연결이 종료 되었습니다.\n");
            exit(0);
          }
          printf("\n클라이언트가 전달한 메시지:%s\n", fromClient);

          sprintf(toClient, "서버에서 전달한 메시지:%s\n", fromClient);
          printf("\n%s", toClient);
          write(clientSocket, toClient, BUFFERSIZE);
        }
      }
    }
  }

  return 0;
}

void child_end(int signal) {
  int state;
  int child = waitpid(-1, &state, WNOHANG);
  printf("자식 프로세스가 종료되었습니다.\n");
}
