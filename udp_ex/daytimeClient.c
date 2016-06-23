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
  int clientSocket = socket(PF_INET, SOCK_DGRAM, 0);

  struct sockaddr_in serverAddress;
  memset(&serverAddress, 0, sizeof(serverAddress));
  serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1");
  serverAddress.sin_family = AF_INET;
  serverAddress.sin_port = htons(PORT);

  connect(clientSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress));

  char toServer[BUFFERSIZE];
  char fromServer[BUFFERSIZE];

  while(1) {
    sprintf(toServer, "지금 몇시예요?\n");
    write(clientSocket, toServer, BUFFERSIZE);

    read(clientSocket, fromServer, BUFFERSIZE);
    printf("%s\n", fromServer);
    sleep(1);
  }

  close(clientSocket);
  return 0;
}
