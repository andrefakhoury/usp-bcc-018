#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h> 

#define szPop 5	//maximum population size
#define mutRatio 1	//mutation ratio
#define INF 1<<48	//infinite

double ind[31];		 //individuals array
double fit[szPop+1]; //fitness array	

void initPop() {
	//a primeira coisa que tem que fazer eh iniciar a populacao
	for (int i = 1; i <= szPop; i++)
		ind[i] = (rand()%20000-10000)/10.0;
}

void testPop() {
	//tem que avaliar a populacao de acordo com o que vc quer
	//faz um array de f(x) para cada x (O(n))

	for (int i = 1; i <= szPop; i++)
		fit[i] = ind[i]*ind[i]*-1;
}

void selectPop() { //elitismo -> melhor transa com todos
	//seleciona o melhor e transa ele com todos os outros

	//Achar o melhor
	int best = 1;
	for (int i = 1; i <= szPop; i++)
		if (fit[i] > fit[best]) best = i;

	//Crossover
	for (int i = 1; i <= szPop; i++)
		ind[i] = (ind[i]+ind[best])/2.0;

	//Mutacao
	for (int i = 1; i <= szPop; i++)
		if (i != best) ind[i] *= (rand()%mutRatio+1);

	printf("[%.2lf:%.2lf] ", ind[best], fit[best]);

	testPop();
}

void printPop() { //imprimir a populacao e seu f(x)
	for (int i = 1; i <= szPop; i++)
		printf("%.2lf:%.2lf ", ind[i], fit[i]);
	printf("\n\n");
}

int main() { //this is the main function
	srand(time(NULL));

	initPop();
	testPop();

	/* 3 tipos mais famosos de selecao: 
			.Roleta
			   Faz uma roleta, cada X vai ter uma casinha de tamanho
			   que quem tem maior f(x) seja maior. Roda a roleta
			   duas vezes (pai e mae). Quem cair em cada um vai transar
			.Melhor transa com todos
				Pega o melhor e transa ele com todos os outros
			.Torneio
				Pega 2 aleatorios. Pega o melhor deles.
				Pega mais 2 aleatorios. Pega o melhor deles.
				Transa os dois vencedores */


	while(1) {
		selectPop();
		printPop();
		usleep(450000);
	}
	return 0;
}