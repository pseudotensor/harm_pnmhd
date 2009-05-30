#define N1 10
#define N2 10
#define N3 10

#define BUFFERMAP ((k*N2*N1+j*N1+i)*numcolumns+nextbuf++)
#define BUFFERINIT if(mpicombine==1) nextbuf=0

//  gcc -o crap crapola.c 

#include <stdio.h>


int main(void){
  int i,j,k,nextbuf,mpicombine,numcolumns;

  mpicombine=1;
  numcolumns=2;

  for(k=0;k<N3;k++)  for(j=0;j<N2;j++)  for(i=0;i<N1;i++){
    //    x=BUFFERMAP;
    BUFFERINIT;
    fprintf(stdout,"%d %d %d : %d\n",k,j,i,BUFFERMAP);
    fprintf(stdout,"%d %d %d : %d\n",k,j,i,BUFFERMAP);
  }

}
