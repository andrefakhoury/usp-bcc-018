// to compile: gcc 11encontra_max_barrier.c -o mainbarrier -fopenmp
// to execute: mainbarrier <num_elements>

#include <stdlib.h>
#include <stdio.h>
#include <omp.h>

#define T 4

int main(int argc,char **argv)
{
    int i, *vetor, maior, tam, num_threads;
    double wtime;

    if ( argc  != 2)
    {
		printf("Wrong arguments. Please use main <amount_of_elements>\n");
		exit(0);
    }

    tam = atoi(argv[1]);
    //tam = 90000000;   // 90M
    //tam = 10

    printf("Amount of vetor=%d\n", tam);
    fflush(0);

    vetor=(int*)malloc(tam*sizeof(int)); //Aloca o vetor da dimensão lida

    // getting start time after malloc.
    wtime = omp_get_wtime();

    #pragma omp parallel num_threads(T) shared (maior)
    {
	int i, my_id, my_range, my_first_i, my_last_i;
	int localmaior;

	omp_lock_t mylock;
	omp_init_lock(&mylock);

	// determina o nr da thread
	my_id = omp_get_thread_num();

	// determina o nr de threads
	num_threads = omp_get_num_threads();

	my_range = tam/num_threads;
		
	my_first_i = my_range * my_id;
		
	if (my_id < num_threads-1)
	{
	  my_last_i = my_first_i + my_range; // na verdade eh o primeiro do proximo range
	}
	else
	{
		my_last_i = tam; // a ultima thread fica com o resto, caso divisao N/num_threads não for exata
	}


	// iniciando vetor com nrs aleatorios e fixando o maior valor para validacao
        for(i = my_first_i; i < my_last_i; i++)
	{
//		vetor[i] = rand() % 10000;
		vetor[i] = my_first;	// gera todos nrs da faixa com o ID da thread. Para verificação apenas.
	}
    vetor[tam/2] = 10001;
      
	// sync point
	#pragma omp barrier
	
	localmaior = maior = -1;
		
//        for(i = my_first_i; i < my_last_i; i++)
	for(i = my_id; i < tam; i=i+T)
	{
//	    printf("thread id:%d, i=%d \n", my_id, i);
	    if(vetor[i] > localmaior)
	    {
                localmaior=vetor[i];
	    }
        }
//      printf("thread:%d, my_first:%d, my_last:%d, localmaior:%d\n", my_id, my_first_i, my_last_i, localmaior);
//	fflush(0);

	
	omp_set_lock(&mylock);
	if (localmaior > maior)
	{
		maior = localmaior;
	}
	omp_unset_lock(&mylock);

    }  // end parallel region

    wtime = omp_get_wtime() - wtime;

/*  // imprimindo o vetor para conferencia
    for(i = 0; i < tam; i++)
    {
	printf("vetor[%d]=%d\n",i,vetor[i]);
    }
    printf("\n");
*/
	
    printf("PAR LOCK: Tam=%d, Num_Threads=%d, maior=%d, Elapsed wall clock time = %f  \n", tam, num_threads, maior, wtime);
    free(vetor); //Desaloca o vetor
	
    return 0;
}