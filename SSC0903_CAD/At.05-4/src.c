/**
------------------------------------------------------
--- SSC0903 - Computação de Alto Desempenho (2020) ---
------------------------------------------------------

Atividade 05-4: Maior frequência de uma string

Desenvolvida por:
- Grupo 1
-- André Luís Mendes Fakhoury
-- Debora Buzon da Silva
-- Gustavo Vinicius Vieira Silva Soares
-- Thiago Preischadt Pinheiro
*/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <omp.h>

// maximo de caracteres
#define MAXC 256
#define T 16

int main(int argc, char* argv[]) {
	// ler dados de entrada
	int n;
	scanf("%d", &n);
	getchar(); // ignora a primeira quebra de linha

	unsigned char* s = malloc(n * sizeof(unsigned char));
	for (int i = 0; i < n; i++) {
		scanf("%c", &s[i]);
	}

	int freq[MAXC] = {}; // vetor frequencia

	int max_freq = 0;

	// determina o caractere mais frequente
	#pragma omp parallel reduction(max: max_freq) num_threads(T) 
	{
		int loc_freq[MAXC] = {}; // vetor local de frequencia

		#pragma omp for
		for (int i = 0; i < n; i++) { // atualiza as frequencias locais
			loc_freq[(int) s[i]]++;
		}

		#pragma omp barrier

		#pragma omp critical
		for (int i = 0; i < MAXC; i++) { // atualiza as frequencias globais
			freq[i] += loc_freq[i];
		}

		#pragma omp barrier

		#pragma omp for
		for (int i = 0; i < MAXC; i++) { // calcula o maximo de frequencia
			if (freq[i] > max_freq) {
				max_freq = freq[i];
			}
		}
	}

	// imprime o(s) caractere(s) mais frequente(s)
	for (int i = 0; i < MAXC; i++) {
		if (freq[i] == max_freq) {
			printf("%c", i);
		}
	}
	puts("");

	free(s);
	return 0;
}