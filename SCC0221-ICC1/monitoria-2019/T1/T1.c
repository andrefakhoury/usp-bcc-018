#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
	int seed; scanf("%d", &seed);
	char dif; scanf(" %c", &dif);

	srand(seed);

	int numElementos, numSequencias;
	int arr[9];

	if (dif == 'F') numElementos = 5, numSequencias = 3;
	if (dif == 'I') numElementos = 7, numSequencias = 4;
	if (dif == 'A') numElementos = 9, numSequencias = 5;
	// tempo = dif == 'A' ? 10 : numElementos;

	int tentativas = 3, seqAtual = 1, errosSeguidos = 0;
	int valorMaximo = 10 * numElementos, pontuacaoT = 0;

	while (tentativas > 0 && seqAtual <= numSequencias) {
		printf("Sequencia #%d:\n", seqAtual);
		int valorAtual = valorMaximo;

		for (int i = 0; i < numElementos; i++) {
			arr[i] = errosSeguidos ? arr[i] : rand()%10;
			printf("%d ", arr[i]);
		}

		printf("\n");

		int dig[9];
		for (int i = 0; i < numElementos; i++) {
			scanf("%d", &dig[i]);
			if (dig[i] != arr[i]) valorAtual -= 10;
		}

		if (valorAtual != valorMaximo) {
			printf("Incorreto!\n");
			tentativas--;
			errosSeguidos++;

			if (errosSeguidos == 1) {
				pontuacaoT += valorAtual;
			} else if (tentativas > 0) {
				pontuacaoT -= valorMaximo - valorAtual;
				pontuacaoT = pontuacaoT < 0 ? 0 : pontuacaoT;
			}

			valorMaximo = errosSeguidos == 1 ? valorAtual : valorMaximo;
		} else {
			printf("Correto!\n");
			pontuacaoT += errosSeguidos ? 0 : valorAtual;

			valorMaximo = 10 * numElementos;
			errosSeguidos = 0;
			seqAtual++;
		}

		printf("Tentativas disponiveis: %d\n", tentativas);
		printf("Pontuacao: %d\n", pontuacaoT);
	}

	if (tentativas > 0) printf("Otima memoria! Parabens!!!\n");
	else printf("Nao ha mais tentativas disponiveis... Tente novamente!\n");
}