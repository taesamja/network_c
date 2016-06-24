#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
  int number = 0;

  pid_t pid = fork();
  if(pid == -1) {
    printf("자식 프로세스 생성에 실패하였습니다.\n");
  }
  printf("자식 프로세스 생성에 성공하였습니다. 자식 프로세스 아이디는 %d 입니다.\n", pid);

  if(pid!=0) {
    number++;
    printf("부모 프로세스에서 number++ 값은 %d 입니다.\n", number);
    sleep(5);

    printf("종료된 자식 프로세스가 있는지 알아봅니다.\n");
    int state;
    int child = waitpid(-1, &state, WNOHANG);
    if(child!=0) {
      printf("종료된 자식 프로세스가 존재합니다.\n");
      printf("종료된 자식 프로세스의 아이디는 %d 입니다.\n", child);
      printf("자식 프로세스에서 부모 프로세스로 리턴한 값은 %d입니다.\n", WEXITSTATUS(state));
    }
    else {
      printf("종료된 자식 프로세스가 존재하지 않습니다.\n");
    }
  }
  else {
    number++;
    printf("자식 프로세스에서 number++ 값은 %d 입니다.\n", number);
  }

  return 0;
}
