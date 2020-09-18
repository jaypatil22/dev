#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>


int main() {

  int p;
  printf("welcome\n" );
  fork();
  printf("Hello\n" );
  printf("Bye\n" );
  if(p > 0) {
    printf("tata\n" );
  } else {
    printf("birla\n" );
  }

  return 0;
}
