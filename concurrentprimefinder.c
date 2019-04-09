#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include "timer.h"

int nprimos = 0;
pthread_mutex_t mutexCounter, mutexPrimos; //variavel de lock para exclusao mutua
long long int max, counter = 1;

int ehPrimo(long long int n) {
  int i;
  if (n<=1) return 0;
  if (n==2) return 1;
  if (n%2==0) return 0;
  for (i=3; i<sqrt(n)+1; i+=2)
  if(n%i==0) return 0;
  return 1;
}

void *contaPrimos(){
  long long int i;
  while(counter <= max){
    pthread_mutex_lock(&mutexCounter);
    i = counter;
    counter = counter + 1;
    pthread_mutex_unlock(&mutexCounter);

    if((i <= max) && ehPrimo(i)){
      pthread_mutex_lock(&mutexPrimos);
      nprimos = nprimos + 1;
      pthread_mutex_unlock(&mutexPrimos);
    }
  }
  pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
  double ini, fim;
  int t, nThreads = atoi(argv[2]);
  max = atoll(argv[1]);
  pthread_t tid[nThreads];

  GET_TIME(ini);

  //--inicilaiza o mutex (lock de exclusao mutua)
  pthread_mutex_init(&mutexCounter, NULL);
  pthread_mutex_init(&mutexPrimos, NULL);

  for(t=0; t<nThreads; t++) {
    if (pthread_create(&tid[t], NULL, contaPrimos, NULL)) {
      printf("--ERRO: pthread_create()\n"); exit(-1);
    }
  }
  //--espera todas as threads terminarem
  for (t=0; t<nThreads; t++) {
    if (pthread_join(tid[t], NULL)) {
         printf("--ERRO: pthread_join() \n"); exit(-1);
    }
  }

  pthread_mutex_destroy(&mutexCounter);
  pthread_mutex_destroy(&mutexPrimos);

  GET_TIME(fim);

  printf("Numero de primos = %d\n", nprimos);
  printf("Tempo = %lf\n", fim-ini);
  return 0;
}
