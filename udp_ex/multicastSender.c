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
#define TTL 64

int main() {
  int senderSocket = socket(PF_INET, SOCK_DGRAM, 0);

  struct sockaddr_in multiAddress;
  memset(&multiAddress, 0, sizeof(multiAddress));
  multiAddress.sin_addr.s_addr = inet_addr("127.0.0.1");
  multiAddress.sin_family = AF_INET;
  multiAddress.sin_port = htons(PORT);

  int multiTTL=TTL;
  setsockopt(senderSocket, IPPROTO_IP, IP_MULTICAST_TTL, (void *)&multiTTL, sizeof(multiTTL));

  time_t t_clock;
  struct tm *newClock;
  char toReceiver[BUFFERSIZE];

  while(1) {
    time(&t_clock);
    newClock = localtime(&t_clock);
    sprintf(toReceiver, "현재시각은 %d년 %d월 %d일 %d시%d분%d초\n\n", newClock->tm_year+1900, newClock->tm_mon+1, newClock->tm_mday, newClock->tm_hour + 9, newClock->tm_min, newClock->tm_sec);
    sendto(senderSocket, toReceiver, strlen(toReceiver), 0, (struct sockaddr*)&multiAddress, sizeof(multiAddress));
    sleep(1);
  }

  close(senderSocket);
  return 0;
}
