#include <stdio.h>

int main(void){
  FILE*ener_file;

  long fpos,origfpos;
  
  if((ener_file = fopen("0_ener.dat","at+"))==NULL) {
    fprintf(stderr,"error opening energy output file\n") ;
    exit(1) ;
  }
  
  origfpos=ftell(ener_file); // position to continue writting at

  fseek(ener_file,0,SEEK_SET);
  //rewind(ener_file);
  fpos=ftell(ener_file); // position to continue writting at
  printf("%ld\n",fpos);

  // now that done, go back
  fseek(ener_file,origfpos,SEEK_SET);
  fpos=ftell(ener_file); // position to continue writting at
  printf("%ld\n",fpos);

  fclose(ener_file);
  return(0);
}
