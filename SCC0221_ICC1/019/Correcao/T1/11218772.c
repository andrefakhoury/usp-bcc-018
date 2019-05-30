#include <stdio.h>

#include <stdlib.h> //funçao srand()

#include <unistd.h> //funçao sleep()

int main() {
    int seed;
    scanf("%d", & seed); //le a seed do numero aleatorio
    srand(seed);
    char nivel;
    scanf(" %c", & nivel); //le a dificuldade escolhida
    int resposta; 
    int num_sequencias; // dependendo do nivel é alterada
    int tamanho_sequencia; //dependendo do nivel é alterada
    //int tempo; seria para alterar o tempo de sleep dependendo do nivel
    int somador = 0; // libera os pontos de cada sequencia
    int erro = 0;
    int pontos = 0; //pontos por sequencia
    int total_pontos = 0; //soma de todos os pontos
    int i = 0;
    int tentativas = 3;
    int matriz[5][9];

    //alteram o tamanho e quantidade de sequencias dependendo do nivel  
    if (nivel == 'F') { 
        num_sequencias = 3;
        tamanho_sequencia = 5;
        //tempo=5;
    }
    if (nivel == 'I') {
        num_sequencias = 4;
        tamanho_sequencia = 7;
        //tempo=7;
    }
    if (nivel == 'A') {
        num_sequencias = 5;
        tamanho_sequencia = 9;
        //tempo=10;
    }

    //cria a matriz de numeros aleatorios a ser lembrada 
    for (int i = 0; i < num_sequencias; i++) {  
        for (int k = 0; k < tamanho_sequencia; k++) {
            matriz[i][k] = rand() % 10;
        }
    }
    //imprime a primeira sequencia a ser adivinhada
    printf("Sequencia #1:\n"); 
    for (int k = 0; k < tamanho_sequencia; k++) {
        printf("%d ", matriz[0][k]);
    }
    printf("\n");
    //sleep(tempo);
    //system("clear");

    while (i < num_sequencias) {
        if (somador == 0) { 
            pontos = (tamanho_sequencia * 10); 
            //o maximo de pontos por sequencia é seu tamanho*10
            //logo o somador adiciona esse valor a cada sequencia
            // entretando caso haja erro o valor permanece constante
            //limitando os pontos de cada tentativa
        }
        //le a resposta
        for (int k = 0; k < tamanho_sequencia; k++) { 
            scanf("%d", & resposta);
            if (resposta != matriz[i][k]) {
                erro += 10; // conta  os erros
            }
        }
        //caso haja erro
        if (erro >= 10) { 
            tentativas = tentativas - 1;
            pontos = pontos - erro; //subtrai os erros do total de pontos
            //impede pontos negativos
            if (pontos <= 0) { 
                pontos = 0;
            }
            somador = 1; //impede que a soma de pontos ocorra
            erro = 0; // reseta o erro
            printf("Incorreto!\nTentativas disponiveis: %d\nPontuacao: %d\n", tentativas, total_pontos + pontos);
            //para o loop caso nao haja tentatticas disponiveis 
            if (tentativas == 0) {
                printf("Nao ha mais tentativas disponiveis... Tente novamente!");
                break; 
            }
            printf("Sequencia #%d:\n", i + 1); // imprime a sequencia novamente
            for (int k = 0; k < tamanho_sequencia; k++) {
                printf("%d ", matriz[i][k]);
            }
            printf("\n");
            //sleep(tempo);
            //system("clear");

            // caso nao tenha erro proceder para a proxima sequencia
        } else { 
            somador = 0; //permite a liberaçao de pontos da proxima sequencia
            total_pontos += pontos;
            printf("Correto!\nTentativas disponiveis: %d\nPontuacao: %d\n", tentativas, total_pontos);
            i++;
            //acertadas as n sequencias termina o programa
            if (i == num_sequencias) { 
                printf("Otima memoria! Parabens!!!");
                break;
            }
            //imprime a proxima sequencia
            printf("Sequencia #%d:\n", i + 1); 
            for (int k = 0; k < tamanho_sequencia; k++) {
                printf("%d ", matriz[i][k]);
            }
            printf("\n");
            //sleep(tempo);
            //system("clear");
        }
    }
    return 0;
}