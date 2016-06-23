//gcc -D_RENTRANT thread6.c -o thread6 -lpthread
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

char stack[5];
int id=0;

sem_t semaphore1;
sem_t semaphore2;

void *pop(void *arg) {
  int i;
  for(i=0;i<5;i++) {
    sem_wait(&semaphore1);
    id--;
    printf("pop-->stack[%d]=%c\n", id, stack[id]);
    sem_post(&semaphore2);
  }
}

void *push(void *arg) {
  int i;
  for(i=0;i<5;i++) {
    stack[id]='A'+i;
    printf("push-->stack[%d]=%c\n", id, stack[id]);
    id++;
    sem_post(&semaphore1);
    sem_wait(&semaphore2);
  }
}

int main() {
  pthread_t popThreadID;
  pthread_t pushThreadID;
  sem_init(&semaphore1,0,0);
  sem_init(&semaphore2,0,0);

  printf("\n\n*****멀티스레드 시작*****\n");
  int popThreadState = pthread_create(&popThreadID, NULL, pop, NULL);
  int pushThreadState = pthread_create(&pushThreadID, NULL, push, NULL);

  void *t_return;
  int state;
  state = pthread_join(popThreadID, &t_return);
  state = pthread_join(pushThreadID, &t_return);

  printf("스레드 종료\n");
  sem_destroy(&semaphore1);
  sem_destroy(&semaphore2);

  return 0;
}
