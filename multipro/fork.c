#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
  int number = 0;

  pid_t pid = fork();

  if(pid == -1) {
    printf("자식프로세스 생성에 실패하였습니다.\n");
  }
  printf("자식프로세스 생성에 성공하였습니다. 자식 프로세스 id는 %d입니다.\n", pid);

  if(pid!=0) {
    number++;
    printf("부모프로세스에서 number++ 값은 %d입니다.\n", number);
  }
  else {
    number++;
    printf("자식프로세스에서 number++ 값은 %d입니다.\n", number);
  }

  return 0;
}
