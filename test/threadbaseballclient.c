#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>

#define PORT 11111

int main() {
  int clientSocket = socket(PF_INET, SOCK_STREAM, 0);
  if(clientSocket == -1) {
    printf("클라이언트 소켓을 생성하는데 실패했습니다.\n");
    return 0;
  }
  printf("클라이언트 소켓을 생성하는데 성공했습니다.\n");

  struct sockaddr_in serverAddress;
  memset(&serverAddress, 0, sizeof(serverAddress));
  serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1");
  serverAddress.sin_family = AF_INET;
  serverAddress.sin_port = htons(PORT);

  connect(clientSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress));
  printf("야구게임을 시작합니다.\n");

  while(1) {
    int clientNumber[3];
    printf("세 수를 입력해 주세요.(ex: 1 2 3)\n--> ");
    scanf("%d %d %d", &clientNumber[0], &clientNumber[1], &clientNumber[2]);

    int i;
    for(i=0;i<3;i++) {
      clientNumber[i]=htonl(clientNumber[i]);
    }
    send(clientSocket, (char *)clientNumber, sizeof(clientNumber), 0);

    int score[2];
    read(clientSocket, (char *)score, sizeof(score));

    int strike=ntohl(score[0]);
    int ball=ntohl(score[1]);
    printf(": %d 스트라이크 %d볼\n\n", strike, ball);

    if(strike == 3) {
      printf("3 스트라이크 프로그램을 종료합니다..\n\n");
      break;
    }
  }
  close(clientSocket);
}
