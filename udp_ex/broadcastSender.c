#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <time.h>

#define PORT 11111
#define BUFFERSIZE 50

int main() {
  int senderSocket=socket(PF_INET, SOCK_DGRAM, 0);

  int soBroadcast = 1;
  setsockopt(senderSocket, SOL_SOCKET, SO_BROADCAST, (void *)&soBroadcast, sizeof(soBroadcast));

  struct sockaddr_in broadAddress;
  memset(&broadAddress, 0, sizeof(broadAddress));
  broadAddress.sin_addr.s_addr = htonl(INADDR_ANY);
  broadAddress.sin_family = AF_INET;
  broadAddress.sin_port = htons(PORT);

  printf("1초마다 현재 시간을 전체 수신자에게 보내고 있는 중입니다....\n");
  time_t t_clock;
  struct tm *newClock;

  char toReceiver[BUFFERSIZE];
  while(1) {
    time(&t_clock);
    newClock = localtime(&t_clock);
    sprintf(toReceiver, "현재 시간은 %d:%d:%d\n", newClock->tm_hour + 9, newClock->tm_min, newClock->tm_sec);
    sendto(senderSocket, toReceiver, strlen(toReceiver), 0, (struct sockaddr*)&broadAddress, sizeof(broadAddress));
    sleep(1);
  }

  close(senderSocket);
  return 0;
}
