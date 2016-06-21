#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

void *go(void *arg) {
  int i;
  for(i=0;i<100;i++) {
    printf("i -->%d\n",i);
  }
}

void *come(void *arg) {
  int j;
  for(j=0;j<100;j++) {
    printf("j -->%d\n",j);
  }
}

int main() {
  pthread_t goThreadID;
  pthread_t comeThreadID;

  printf("스레드 생성 시작.....\n\n");

  int goThreadState = pthread_create(&goThreadID, NULL, go, NULL);
  if(goThreadState != 0) {
    printf("goThread 생성에러\n");
  }

  int comeThreadState = pthread_create(&comeThreadID, NULL, come, NULL);
  if(comeThreadState != 0) {
    printf("comeThread 생성에러\n");
  }

  printf("스레드 종료 .....\n\n");
  return 0;
}
