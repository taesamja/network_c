#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void *go(void *arg) {
  int i;
  for(i=0;i<10;i++) {
    printf("i -->%d\n", i);
  }
}

void *come(void *arg) {
  int j;
  for(j=0;j<10;j++) {
    printf("j -->%d\n", j);
  }
}

int main() {
  pthread_t goThreadID;
  pthread_t comeThreadID;

  printf("스레드 생성 시작...\n\n");

  int goThreadState = pthread_create(&goThreadID, NULL, go, NULL);
  if(goThreadState!=0) {
    printf("goThread 생성 에러\n");
  }

  int comeThreadState = pthread_create(&comeThreadID, NULL, come, NULL);
  if(comeThreadState!=0) {
    printf("comeThread 생성 에러\n");
  }

  void *t_return;
  int state=pthread_join(goThreadID, &t_return);
  state=pthread_join(comeThreadID, &t_return);

  printf("스레드 생성 종료...\n\n");
  return 0;
}
