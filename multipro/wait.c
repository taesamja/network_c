#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
  int number = 0;

  pid_t pid = fork();
  if(pid == -1) {
    printf("자식 프로세스 생성에 실패했습니다.\n");
  }
  printf("자식 프로세스 생성에 성공했습니다.\n");

  if(pid!=0) {
    number++;
    printf("부모 프로세스에서 number++ 값은 %d 입니다.\n", number);
    printf("자식 프로세스가 종료될 때까지 기다립니다.\n");

    int state;
    int child = wait(&state);
    printf("자식 프로세스가 종료했습니다.\n");
    printf("종료된 자식 프로세스의 아이디는 %d 입니다.\n", child);
    printf("자식 프로세스에서 부모 프로세스로 리턴한 값은 %d 입니다.\n", WEXITSTATUS(state));
    sleep(10);
  }
  else {
    number++;
    printf("자식 프로세스에서 number++ 값은 %d 입니다.\n", number);
  }

  return 0;
}
