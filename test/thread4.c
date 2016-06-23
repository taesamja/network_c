//gcc -D_RENTRANT thread4.c -o thread4 -lpthread
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

char stack[5];
int id=0;
char data;

pthread_mutex_t mutex;

void *pop(void *arg) {
  int i;
  for(i=0;i<5;i++) {
    pthread_mutex_lock(&mutex);
    id--;
    printf("pop-->stack[%d]=%c\n", id, stack[id]);
    pthread_mutex_unlock(&mutex);
  }
}

void *push(void *arg) {
  int i;
  for(i=0;i<5;i++) {
    pthread_mutex_lock(&mutex);
    data='A'+i;
    stack[id]=data;
    printf("push-->stack[%d]=%c\n", id, stack[id]);
    id++;
    pthread_mutex_unlock(&mutex);
  }
}

int main() {
  pthread_t popThreadID;
  pthread_t pushThreadID;
  pthread_mutex_init(&mutex,NULL);

  printf("\n\n*****멀티스레드 시작*****\n\n");
  int popThreadState = pthread_create(&popThreadID, NULL, pop, NULL);
  int pushThreadState = pthread_create(&pushThreadID, NULL, push, NULL);

  void *t_return;
  int state;
  state = pthread_join(popThreadID, &t_return);
  state = pthread_join(pushThreadID, &t_return);

  printf("스레드 종료..\n");
  pthread_mutex_destroy(&mutex);

  return 0;
}
