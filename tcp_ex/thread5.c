//gcc -DENTRANT thread5.c -o thread5 -lpthread
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

char stack[5];
int id = 0;

sem_t semaphore;

void *pop(void *arg) {
  int i;
  for(i=0;i<5;i++) {
    sem_wait(&semaphore);
    id--;
    printf("pop-->stack[%d]=%c\n", id, stack[id]);
  }
}

void *push(void *arg) {
  int i;
  for(i=0;i<5;i++) {
    stack[id]='A'+i;
    printf("push-->stack[%d]=%c\n", id, stack[id]);
    id++;
    sem_post(&semaphore);
  }
}

int main() {
  pthread_t popThreadID;
  pthread_t pushThreadID;
  sem_init(&semaphore, 0, 0);

  printf("\n\n*****멀티스레드 시작*****\n");
  int popThreadState = pthread_create(&popThreadID, NULL, pop, NULL);
  int pushThreadState = pthread_create(&pushThreadID, NULL, push, NULL);

  void *t_return;
  int state;
  state = pthread_join(popThreadID, &t_return);
  state = pthread_join(pushThreadID, &t_return);

  printf("스레드 종료\n");
  sem_destroy(&semaphore);
  return 0;
}
