#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *contPalavras(void* c){
  char *argv = (char *) c;
  FILE *f;
  f = fopen(argv, "r");
  if(f==NULL){
      printf("O arquivo %s não pode ser lido\n",argv);
     return NULL;
  }
  char * buffer = 0;
  long length;
  fseek (f, 0, SEEK_END);
  length = ftell (f);
  fseek (f, 0, SEEK_SET);
  buffer = malloc (length);
  if (buffer)
  {
    fread (buffer, 1, length, f);
  }
  int count = 0;
  int letras = 0;
  int j = 0;
  int teste = 0;
  for(int i = 0; i < length; i++){
    letras = 0;
    j = i;
    teste = 0;
    for(; j < length && teste==0; j++){
      if(buffer[j] == '\n' || buffer[j] == '\t' || buffer[j] == ' ') {
        teste = 1;
        break;
        }
      letras++;
    }
    if(letras != 0) count++;
    i = j;
  }
  printf("O arquivo %s contem %d Palavras\n",argv,count);
  fclose(f);
  free(buffer);
  return NULL;
}

int main(int argc, char*  argv[]){
    if ( argc < 2 )
    {
        printf("Você precisa passar pelo menos um argumento\n");
        exit(1);
    }
    pthread_t t[argc-1];
    for(int i = 0; i < argc-1; i++) pthread_create(&t[i], NULL,contPalavras, argv[i+1]);
    for(int i = 0; i < argc-1; i++) pthread_join(t[i], NULL);
    
    exit(0);
}