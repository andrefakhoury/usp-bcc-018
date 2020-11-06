// para compilar: gcc vet-estat-seq.c -o vet-estat-seq -lm -fopenmp
// para executar: vet-estat-seq
//
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <omp.h>

#define N 100000000  //100M

double soma(double *vet) 
{
  long long i;
  double sum = .0;

  for(i = 0; i < N; i++) 
  {
    sum = sum + vet[i];
  }
  return(sum);
}

double maximo(double *vet)
{
  long long i;
  double max = -1;

  for( i = 0; i < N; i++)
  {
    if (vet[i] > max)
    {
      max = vet[i];
    }
  }
  return(max);
}

double minimo(double *vet)
{
  long long i;
  double min = (double)999999999;

  for( i = 0; i < N; i++)
  {
    if (vet[i] < min)
    {
      min = vet[i];
    }
  }
  return(min);
}


double media(double *vet)
{
  long long i;
  double sum = .0, avg = .0;

  for(i = 0; i < N; i++) 
  {
    sum += vet[i];
  }
  avg = sum / N;

  return(avg);
}


double desviopadrao(double *vet)
{
  long long i;
  double sum = .0, avg = .0, dp= .0, var;

  for(i = 0; i < N; i++) 
  {
    sum += vet[i];
  }
  avg = sum / N;

  sum = .0;
  for(i = 0; i < N; i++)
  {
     sum += pow((vet[i]-avg), 2);
  }
  var = sum / N;
  
  dp = sqrt(var);

  return(dp);
}


int main(void) {
	long long i;


	double *vet;
	double sum, max, min, avg, dp, wtime;

	vet = (double *) malloc(N * sizeof(double));
	if (vet == NULL) {
	  printf ("malloc error com N=%ld \n",N);
	  exit (-1);
	}
	
	for (i = 0; i < N; i++)
	{
//	    vet[i] = (double) (rand() % 100);
	    vet[i] = 1; //N-i;
	}
	printf("Tamanho do Vetor: %ld \n", N);
	fflush(0);

//	for (i = 0; i < N; i++)
//	{
//	    printf("vet[%d] = %f \n", i, vet[i]);
//	}

	wtime = omp_get_wtime ( );
	
//	printf("soma(vet)\n ");
	sum = soma(vet);

//	printf("maximo(vet)\n");
	max = maximo(vet);
	
//	printf("minimo(vet)\n");
	min = minimo(vet);
	
//	printf("media(vet)\n");
	avg = media(vet);

//	printf("desviopadrao(vet)\n");
	dp = desviopadrao(vet);
	
	wtime = omp_get_wtime ( ) - wtime;

	printf("Soma=%.3f, Máximo=%.3f, Mínimo=%.3f, Media=%.3f, Dsv Padrão=%.3f WTime=%.3f \n", sum, max, min, avg, dp, wtime);
	fflush(0);

	return(0);

} // main()
