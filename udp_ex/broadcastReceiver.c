#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>

#define BUFFERSIZE 50
#define PORT 11111

int main() {
  int receiverSocket = socket(PF_INET, SOCK_DGRAM, 0);

  struct sockaddr_in receiverAddress;
  memset(&receiverAddress, 0, sizeof(receiverAddress));
  receiverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
  receiverAddress.sin_family = AF_INET;
  receiverAddress.sin_port = htons(PORT);

  bind(receiverSocket, (struct sockaddr *)&receiverAddress, sizeof(receiverAddress));

  char fromSender[BUFFERSIZE];
  while(1) {
    int strLen = recvfrom(receiverSocket, fromSender, BUFFERSIZE, 0, NULL, 0);
    if(strLen < 0) break;

    fromSender[strLen] = '\0';
    printf("%s\n", fromSender);
  }

  close(receiverSocket);
  return 0;
}
