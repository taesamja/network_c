//gcc -D_RENTRANT thread2.c -o thread2 -lpthread
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

int array[20];
int index=0;
int number=0;

void *insertNumber1(void *arg) {
  while(1) {
    array[index]=number;
    printf("insertNumber1--> array[%d] = %d\n", index, array[index]);
    sleep(2);
    index++;
    number++;

    if(index>20) break;
  }
}

void *insertNumber2(void *arg) {
  while(1) {
    array[index]=number;
    printf("insertNumber2--> array[%d] = %d\n", index, array[index]);
    index++;
    sleep(1);
    number++;

    if(index>20) break;
  }
}

int main() {
  pthread_t insertNumber1ThreadID;
  pthread_t insertNumber2ThreadID;

  printf("\n\n*****멀티스레드시작*****\n\n");
  int number1ThreadState = pthread_create(&insertNumber1ThreadID, NULL, insertNumber1, NULL);
  int number2ThreadState = pthread_create(&insertNumber2ThreadID, NULL, insertNumber2, NULL);

  void *t_return;
  int state;
  state = pthread_join(insertNumber1ThreadID, &t_return);
  state = pthread_join(insertNumber2ThreadID, &t_return);

  printf("\n\n*****멀티스레드 실행결과*****\n\n");
  int i;
  for(i=0;i<20;i++) {
    printf("array[%d]:%d\n", i, array[i]);
  }

  printf("스레드 종료..\n\n");
  return 0;
}
