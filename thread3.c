//gcc -D_RENTRANT thread3.c -o thread3 -lpthread
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

int array[20];
int id = 0;
int number = 0;

pthread_mutex_t mutex;

void *insertNumber1(void *arg) {
  while(1) {
    if(id>=20) {
      break;
    }

    pthread_mutex_lock(&mutex);

    array[id]=number;
    printf("insertNumber1-->array[%d]=%d\n", id, array[id]);
    sleep(1);
    id++;
    number++;

    pthread_mutex_unlock(&mutex);
  }
}

void *insertNumber2(void *arg) {
  while(1) {
    if(id>=20) {
      break;
    }

    pthread_mutex_lock(&mutex);

    array[id]=number;
    printf("insertNumber2-->array[%d]=%d\n", id, array[id]);
    sleep(1);
    id++;
    number++;

    pthread_mutex_unlock(&mutex);
  }
}

int main() {
  pthread_t insertNumber1ThreadID;
  pthread_t insertNumber2ThreadID;
  pthread_mutex_init(&mutex, NULL);

  printf("\n\n*****멀티스레드 시작.*****\n\n");
  int number1ThreadState = pthread_create(&insertNumber1ThreadID, NULL, insertNumber1, NULL);
  int number2ThreadState = pthread_create(&insertNumber2ThreadID, NULL, insertNumber2, NULL);

  void *t_return;
  int state;
  state = pthread_join(insertNumber1ThreadID, &t_return);
  state = pthread_join(insertNumber2ThreadID, &t_return);

  printf("\n\n*****멀티스레드 실행 결과.*****\n\n");
  int i;
  for(i=0;i<20;i++) {
    printf("array[%d]:%d\n", i, array[i]);
  }

  printf("스레드 종료\n");
  pthread_mutex_destroy(&mutex);

  return 0;
}
