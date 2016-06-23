#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>

#define PORT 11111
#define BUFFERSIZE 50

int main() {
  int receiverSocket = socket(PF_INET, SOCK_DGRAM, 0);

  struct ip_mreq joinAddress;
  joinAddress.imr_multiaddr.s_addr = inet_addr("127.0.0.1"); //IP multicast address of group
  joinAddress.imr_interface.s_addr = htonl(INADDR_ANY);      //local IP address of interface
  setsockopt(receiverSocket, IPPROTO_IP, IP_ADD_MEMBERSHIP, (void *)&joinAddress, sizeof(joinAddress));

  struct sockaddr_in receiverAddress;
  memset(&receiverAddress, 0, sizeof(receiverAddress));
  receiverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
  receiverAddress.sin_family = AF_INET;
  receiverAddress.sin_port = htons(PORT);

  bind(receiverSocket, (struct sockaddr *)&receiverAddress, sizeof(receiverAddress));

  char fromSender[BUFFERSIZE];

  while(1) {
    int strLen = recvfrom(receiverSocket, fromSender, BUFFERSIZE-1, 0,
                         NULL, 0);
    if(strLen < 0) {
      break;
    }
    fromSender[strLen]=0;
    printf("%s\n", fromSender);
  }

  close(receiverSocket);
  return 0;
}
