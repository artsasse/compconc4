#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include "timer.h"

int nprimos = 0;

int ehPrimo(long long int n) {
  int i;
  if (n<=1) return 0;
  if (n==2) return 1;
  if (n%2==0) return 0;
  for (i=3; i<sqrt(n)+1; i+=2)
  if(n%i==0) return 0;
  return 1;
}

int main(int argc, char *argv[]) {
  double ini, fim;
  int k;
  long long int n = atoll(argv[1]);

  GET_TIME(ini);

  for(k=1; k <= n; k++){
    if(ehPrimo(k)) nprimos++;
  }

  GET_TIME(fim);

  printf("Numero de primos = %d\n", nprimos);
  printf("Tempo = %lf\n", fim-ini);
  return 0;
}
