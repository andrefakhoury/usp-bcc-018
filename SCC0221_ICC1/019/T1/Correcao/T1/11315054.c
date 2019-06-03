#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <stdlib.h>
int main (void){
    
    int A[45], B[45], seed, seq=1, vet, erros=0, vidas=3, pts=0, total=0, inic=1;
    //int temp;
    char dif;

    //printf ("Selecione uma semente e a dificuldade:\n");
    scanf ("%d %ch", &seed, &dif); //entrada da semente
    //scanf ("%ch", &dif); //entrada da dificuldade
    
    
    srand (seed);
    
    switch (dif){ //switch case foi ultilizado para definir a dificuldade
        case 'F' :{ //exemplo; fácil, define quantas sequencias, o tamanho da sequencia e o tempo de exibição da sequência
            seq=3;
            vet=5;
            //temp=5;
            }
            break;
        case 'I' :{
            seq=4;
            vet=7;
            //temp=7;
            }
            break;
        case 'A' :{
            seq=5;
            vet=9;
            //temp=10;
            }
            break;
    }

    do { //esta condição do do while determina que o jogador apenas vence o jogo se completar corretamente todas as sequências
        for (int v=0; v<seq; v++){ //esta condição determina quantas sequencias o jogador deve acertar antes de terminar o jogo
            for (int i=0; i<vet; i++){ //esta condição determina as novas sequencia desde a #1 e as próximas, caso tenha acertado as anteriores
                    A[i]= rand() %10; 
            }
            total=pts; //variavel para evitar que desconte em excesso
            pts=pts+(vet*10); //inicialemente o jogador possui a pontuação máxima, ao longo do jogo, caso erre, será descontado do total o equivalente ao erro
            
            do {
                printf ("Sequencia #%d:\n", inic);
                for (int i=0; i<vet; i++){ //esta condição exibe a sequencia anterior novamente caso o jogador tenha errado
                    printf ("%d ", A[i]);
                    }

                printf ("\n"); //esta linha em branco é necessaria pois o clear limpa tudo antes da ultima linha exibida
                //sleep (temp); // neste caso antes da linha em branco seria a sequencia, logo, caso não houvesse uma linha em branco, ela (a sequencia) continuaria em exibição, e tudo antes dela seria excluido
                //system ("clear"); //a função de limpar a tela varia de sistema operacional
                    
                for (int j=0; j<vet; j++){ //esta condição cria um vetor para armazenar cada tentativa do jogador
                    scanf ("%d", &B[j]);
                }
                erros=0; //essa condição redefine os erros, pois ele é um contador e se manteria acumulando, atrapalhando a contagem
    
                for (int i=0; i<vet;i++){ //os dois vetores, sequencia e tentativa, são comparados, posição a posição para verificar se há erros
                    if (A[i]!=B[i]){
                        erros++; //caso ocorram, o contador é incrementado
                    }
                }

                if (erros==0){ // se não houver erros, o contador inic determina o avanço do jogador
                    inic++;
                    printf ("Correto! \nTentativas disponiveis: %d\nPontuacao: %d\n", vidas, pts);
                }

                else{
                    vidas--; //caso erros sejam diferente de 0, será descontado uma vida, tentativa, do jogador
                    pts+=-(erros*10); //além disso caso existam erros, eles serão descontados da pontuação inicial da rodada (sequência)
                    
                    if (pts<total)
                        pts=total;
                    if (pts<0) //essa condição garante que não exista pontuação negativa
                        pts=0;
                    printf("Incorreto! \nTentativas disponiveis: %d\nPontuacao: %d\n", vidas, pts);
                }
                    if (vidas==0){ //caso as vidas, tentativas, alcancem 0, o jogo se encerra
                        printf ("Nao ha mais tentativas disponiveis... Tente novamente!\n");
                        return 0;
                    }
                }
            
            while (erros!=0); //o jogador apenas avança se acertar todos os valores da sequencia
        }
    }
    while (inic<=seq); //caso tenha passado com exito por todas as sequencias, o jogador vence o jogo
    printf ("Otima memoria! Parabens!!!\n");
return 0;
}
