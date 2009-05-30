#include <unistd.h>
#include <stdio.h>
#include <strings.h>

int main(void){

  char pathname[100];
  int error;

  strcpy(pathname,"0_final.dat");

  error=unlink(pathname);

  printf("error=%d\n",error);

  return(0);
}
