#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    char nivel;
    int seed, tentativas = 3, quantidade_valores, quantidade_sequencias, maxscore, totscore, sequencia = 1;
    scanf("%d %c", &seed, &nivel);
    srand(seed);
    switch(nivel) {
        case 'F':
            quantidade_sequencias = 3;
            quantidade_valores = 5;
            maxscore = 50;
            break;
        case 'I':
            quantidade_sequencias = 4;
            quantidade_valores = 7;
            maxscore = 70;
            break;
        case 'A':
            quantidade_sequencias = 5;
            quantidade_valores = 9;
            maxscore = 90;
            break;
        default: break;
    }
    while (tentativas && quantidade_sequencias) {
        int valores_sequencia[quantidade_valores];
        for (int i = 0; i < quantidade_valores; i++) valores_sequencia[i] = rand()%10;
        int score = maxscore, erros = 1;
        while (erros && tentativas) {
            erros = 0;
            printf("Sequencia #%d:\n", sequencia);
            for (int j = 0; j < quantidade_valores; j++) printf("%d ", valores_sequencia[j]);
	    fflush(stdout);
            printf("\n");
            int input[quantidade_valores];
            for (int j = 0; j < quantidade_valores; j++) scanf("%d", &input[j]);
            for (int j = 0; j < quantidade_valores; j++) if (input[j] != valores_sequencia[j]) erros++;
            if (erros) {printf("Incorreto!\n"); score -= 10 * erros; if (score < 0) score = 0; tentativas--;}
            else {printf("Correto!\n"); sequencia++; quantidade_sequencias--;}
            printf("Tentativas disponiveis: %d\nPontuacao: %d\n", tentativas, totscore + score);
        }
        totscore += score;
    }
    if (tentativas) printf("Otima memoria! Parabens!!!\n");
    else printf("Nao ha mais tentativas disponiveis... Tente novamente!\n");
    
    return 0;
}