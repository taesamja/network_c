#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void child_end(int signal);

int main() {
  struct sigaction signal;
  signal.sa_handler = child_end;
  signal.sa_flags = 0;
  sigemptyset(&signal.sa_mask);

  int state = sigaction(SIGCHLD, &signal,0);
  if(state!=0) {
    printf("\n시그널 생성 시 오류가 발생하였습니다.\n");
    return -1;
  }

  int number = 0;
  pid_t pid = fork();
  if(pid == -1) {
    printf("\n자식 프로세스 생성에 실패했습니다.\n");
  }
  printf("\n자식 프로세스 생성에 성공했습니다. \n자식 프로세스 아이디는 %d 입니다.\n", pid);

  if(pid!=0) {
    number++;
    printf("\n부모 프로세스에서 number++ 값은 %d 입니다.\n", number);
    sleep(10);
  }
  else {
    number++;
    sleep(5);
    printf("\n자식 프로세스에서 number++ 값은 %d 입니다.\n", number);
  }

  return 0;
}

void child_end(int signal) {
  int state;
  int child = waitpid(-1, &state, WNOHANG);
  printf("\n종료된 자식 프로세스가 존재합니다. \n");
  printf("\n종료된 자식 프로세스의 아이디는 %d 입니다. \n", child);
  printf("\n자식 프로세스에서 부모 프로세스로 리턴한 값은 %d 입니다.\n", WEXITSTATUS(state));
}
