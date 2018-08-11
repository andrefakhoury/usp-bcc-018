/*
	Trabalho que calcula uma possivel nota por um sistema de recomendacao.
	Trabalho 2 da materia de ICC-1.
	
	Andre Fakhoury - 4482145
	USP Sao Carlos

*/

#include <stdio.h>
#include <math.h> //biblioteca para a funcao sqrt

int main(int argc, char* argv[]) {
	int numUser, numFilmes;    // numero de usuarios e numero de itens (no PDF, n e i)
	double limiar;    // limiar (no PDF, t)
 	
	//pega o numero de usuarios e itens
	scanf("%d %d %lf", &numUser, &numFilmes, &limiar);
	
	int notas[numUser][numFilmes];  //matriz de tamanho usuarios x itens
	double modulo[numUser]; //vetor que armazena o modulo das notas de cada usuario
	double media[numUser];  //vetor que armazena a media das notas de cada usuario 
	double sim[numUser];    //vetor que armazena as similaridades (reseta pra cada usuario)
	
	int user1, filme1, user2, filme2; //usados nas repeticoes
	
	//pega as notas
	for (user1 = 0; user1 < numUser; user1++) {
		for (filme1 = 0; filme1 < numFilmes; filme1++) {
			scanf("%d", &notas[user1][filme1]);
		}
	}
	
	//calculo do modulo e da media
	int soma, qtdMedia;
	for (user1 = 0; user1 < numUser; user1++) {
		soma = 0;
		media[user1] = 0;
		qtdMedia = 0;
		for (filme1 = 0; filme1 < numFilmes; filme1++) {
			soma += ((notas[user1][filme1]) * notas[user1][filme1]); //calculo do modulo
			if (notas[user1][filme1] != 0) { //calculo da media, sao desconsideradas as notas 0
				media[user1] += notas[user1][filme1];
				qtdMedia++;
			}
		}
		modulo[user1] = sqrt(soma);
		media[user1] = media[user1]/(double)qtdMedia;
	}
	
	//calcular a similaridade
	int qtd0 = 0; // quantidade de notas nao atribuidas (para o printf)
	double num, den; //numerador e denominador do calculo da nota
	for (user1 = 0; user1 < numUser; user1++) {
		for (user2 = 0; user2 < numUser; user2++) {
			sim[user2] = 0;
			if (user2 == user1) sim[user2] = -1; //proprio usuario
			else {
				for (filme2 = 0; filme2 < numFilmes; filme2++) {
					sim[user2] += (notas[user1][filme2] * notas[user2][filme2]);
				}
				sim[user2] = (sim[user2])/(modulo[user1] * modulo[user2]);
			}
		}
		
		//calculo da nota
		for (filme1 = 0; filme1 < numFilmes; filme1++) {
			if (notas[user1][filme1] == 0) { //so ira calcular uma nota para um filme nao atribuido do usuario
				num = 0; den = 0;
				qtd0++;
				
				for (user2 = 0; user2 < numUser; user2++) {
					if (user1 != user2 && sim[user2] >= limiar) {
						if (notas[user2][filme1] != 0) { //notas nao atribuidas de outros usuarios sao desconsideradas
							num += ((sim[user2]) * (notas[user2][filme1] - media[user2]));
							den += sim[user2];
						}
					}
				}
				
				if (den != 0) { //nao pode ter divisao por 0
					printf("%.2lf ", media[user1] + (num/den));	
				}
				else {
					printf("DI "); //nao houveram dados suficientes
				}
			}
		}
		if (qtd0 > 0) { //print de um \n para o output ficar mais visivel
			qtd0 = 0;
			printf("\n");		
		}
	}
	
	return 0;
}
