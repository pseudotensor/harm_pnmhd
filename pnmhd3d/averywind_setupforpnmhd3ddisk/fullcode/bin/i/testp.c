#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <memory.h>
#include <stdlib.h>


static char command[100];

void main(void){

  FILE *fp;
  FILE *out;
  char ch;
  sprintf(command,"gunzip < testin.gz");

  if ((fp = popen(command, "r")) == NULL){
    fprintf(stderr,"Can't open file via pipe '%s'\n",command);
    return(NULL);
  }
  if( (out=fopen("testout.ppm","wt"))==NULL){
    printf("failed to open testout\n");
    exit(NULL);
  }
  while(!feof(fp)){
    ch=fgetc(fp);
    fprintf(out,"%c",(short)ch);
  }
  pclose(fp);
  fclose(out);
  printf("successful\n");
}
