//gcc -D_REENTRANT chatServer.c -o chatServer -lpthread
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <pthread.h>

#define PORT 11111
#define BUFFERSIZE 100
#define NAMESIZE 30

pthread_t thread;
pthread_mutex_t mutex;

int clientNumber = 0;
int allClientSocket[100];

void *broadcastAllClient(void *arg);

int main() {
  if(pthread_mutex_init(&mutex,NULL) != 0) {
    printf("뮤텍스 생성에 실패했습니다.\n");
    return 0;
  }

  int serverSocket = socket(PF_INET, SOCK_STREAM, 0);

  struct sockaddr_in serverAddress;
  memset(&serverAddress, 0, sizeof(serverAddress));
  serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
  serverAddress.sin_family = AF_INET;
  serverAddress.sin_port = htons(PORT);

  if(bind(serverSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) == -1) {
    printf("서버 소켓을 바인드 하는데 실패했습니다.\n");
    return 0;
  }

  if(listen(serverSocket, 5) == -1) {
    printf("서버 소켓을 listen 모드로 설정하는데 실패했습니다.\n");
    return 0;
  }

  printf("채팅 서버가 실행되었습니다.\n");
  printf("***** 전체 대화 내용 *****\n");

  while(1) {
    struct sockaddr_in clientAddress;
    int clientAddress_size = sizeof(clientAddress);

    int clientSocket = accept(serverSocket, (struct sockaddr *)&clientAddress, &clientAddress_size);

    pthread_mutex_lock(&mutex);
    clientNumber++;
    allClientSocket[clientNumber-1] = clientSocket;
    pthread_mutex_unlock(&mutex);

    char greeMessage[BUFFERSIZE];
    sprintf(greeMessage, "[서버]환영합니다. 대화명을 입력해 주세요.\n");
    write(clientSocket, greeMessage, sizeof(greeMessage));

    pthread_create(&thread, NULL, broadcastAllClient, (void *)clientSocket);
  }
  printf("채팅을 종료합니다.\n");

  return 0;
}

void *broadcastAllClient(void *arg) {
  char fromClient[NAMESIZE+BUFFERSIZE];

  int myClientSocket = (int)arg;

  int i = 0;
  while(1) {
    int readlen = read(myClientSocket, fromClient, sizeof(fromClient));
    if(readlen <= 0) {
      break;
    }
    printf("%s\n", fromClient);

    pthread_mutex_lock(&mutex);
    for(i=0;i<clientNumber;i++) {
      if(allClientSocket[i] != myClientSocket) {
        write(allClientSocket[i], fromClient, sizeof(fromClient));
      }
    }
    pthread_mutex_unlock(&mutex);
  }

  pthread_mutex_lock(&mutex);
  for(i=0;i<clientNumber;i++) {
    if(allClientSocket[i] == myClientSocket) {
      for(i;i<clientNumber-1;i++) {
        allClientSocket[i] = allClientSocket[i+1];
      }
      break;
    }
    clientNumber--;
    pthread_mutex_unlock(&mutex);
    close(myClientSocket);
  }
}
