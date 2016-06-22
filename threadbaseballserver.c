//gcc -D_RENTRANT threadbaseballserver.c -o threadbaseballserver -lpthread
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <pthread.h>

#define PORT 11111

void *playBaseballGame(void *arg);

int serverNumber[3];

pthread_t thread;

int main() {
  int serverSocket = socket(PF_INET, SOCK_STREAM,0);
  printf("서버 소켓을 생성했습니다.\n");

  struct sockaddr_in serverAddress;
  memset(&serverAddress, 0, sizeof(serverAddress));
  serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
  serverAddress.sin_family = AF_INET;
  serverAddress.sin_port = htons(PORT);

  bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress));

  listen(serverSocket, 5);
  printf("클라이언트의 접속을 기다립니다....\n");

  srand((unsigned)time(NULL));

  do {
    serverNumber[0] = rand() % 10;
    serverNumber[1] = rand() % 10;
    serverNumber[2] = rand() % 10;
  } while((serverNumber[0]==serverNumber[1]) | (serverNumber[1]==serverNumber[2]) | (serverNumber[2]==serverNumber[0]));
  printf("서버숫자--> %d %d %d\n", serverNumber[0], serverNumber[1], serverNumber[2]);

  while(1) {
    int clientSocket = accept(serverSocket, NULL, NULL);
    printf("클라이언트가 접속했습니다.\n");
    printf("야구게임시작...\n");
    pthread_create(&thread, NULL, playBaseballGame, (void*)clientSocket);
  }

  return 0;
}

void *playBaseballGame(void *arg) {
  int clientSocket = (int) arg;

  while(1) {
    int fromClientNumber[3];
    int toClientScore[2];
    read(clientSocket, (char*)fromClientNumber, sizeof(fromClientNumber));
    int id;
    for(id=0;id<3;id++) {
      fromClientNumber[id]=ntohl(fromClientNumber[id]);
    }
    printf("클라이언트가 입력한 수--> %d %d %d\n", fromClientNumber[0], fromClientNumber[1], fromClientNumber[2]);

    int strike = 0;
    int ball = 0;

    int i;
    for(i=0;i<3;i++) {
      int oneServerNumber = serverNumber[i];
      int j;
      for(j=0;j<3;j++) {
        int oneClientNumber = fromClientNumber[j];
        if(oneServerNumber == oneClientNumber) {
          if(i == j) {
            strike++;
          }
          else {
            ball++;
          }
        }
      }
    }

    printf("%d 스트라이크 %d 볼\n\n", strike, ball);

    toClientScore[0]=htonl(strike);
    toClientScore[1]=htonl(ball);

    write(clientSocket, (char*)toClientScore, sizeof(toClientScore));

    if(strike==3) {
      printf("3 스트라이크 현재 클라이언트와 접속을 종료 합니다.\n");
      break;
    }
  }
  close(clientSocket);
}
