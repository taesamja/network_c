#include <stdio.h>
#include <stdlib.h>

void go() {
  int i;
  printf("***** go start *****\n");
  for(i=0; i<10; i++)
  {
    printf("i-->%d\n", i);
  }
  printf("***** go end *****\n");
}

void come() {
  int i;
  printf("***** come start *****\n");
  for(i=0; i<10; i++)
  {
    printf("i-->%d\n", i);
  }
  printf("***** come end *****\n");
}

int main() {
  go();
  come();
  return 0;
}
