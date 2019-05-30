#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){
    //system("clear");

    int seed, num_seq=0, tam_seq=0, tent=3, new_seq=1, cont=1, pontos=0, first=1;
    //int t=0; tempo que a sequencia fica na tela
    int seq[10], player_seq[10];
    
    char nivel;

    //le a semente e a dificuldade
    scanf("%d %c", &seed, &nivel);

    srand(seed);

    //define as caracteristicas da dificuldade escolhida
    if(nivel=='F'){
        num_seq=3;
        tam_seq=5;
        //t=5;
    }else if(nivel=='I'){
        num_seq=4;
        tam_seq=7;
        //t=7;
    }else if(nivel=='A'){
        num_seq=5;
        tam_seq=9;
        //t=9;
    }

    //continua jogando enquanto tiver tentativas sobrando e sequencias para acertar
    while(tent>0 && num_seq>=cont){

        //gera uma nova sequencia
        if(new_seq==1){
            //define que nao deve gerar uma nova sequencia
            new_seq = 0;
            
            for(int i=0; i<tam_seq; i++){
                seq[i]=rand()%10;
            }

            //guarda que sera a primeira tentativa
            first = 1;
        }

        //mostra a sequencia atual
        printf("Sequencia #%d:\n", cont);

        for(int i=0; i<tam_seq; i++){
            printf("%d ", seq[i]);
        }
        printf("\n");

        //espera o tempo definido e apaga
        //sleep(t);
        //system("clear");

        //le a tentativa do jogador
        for(int i=0; i<tam_seq; i++){
            scanf("%d", &player_seq[i]);
        }

        //olha se é a primeira tentativa
        if(first==1){
            //checa o numero de acertos
            int acertos=0;
            for(int i=0; i<tam_seq; i++){
                if(seq[i]==player_seq[i]) acertos++;
            }

            if(acertos<tam_seq){
                //guarda que nao sera mais a primeira tentativa e penaliza o jogador em case de erro
                first = 0;
                tent--;
                printf("Incorreto!\n");
            }else{
                //define que deve ser gerada uma nova sequencia em caso de acerto
                new_seq=1;
                cont++;
                printf("Correto!\n");
            }

            //adiciona os pontos obtidos
            pontos += acertos*10;
        }else{
            //checa o numero de acertos
            int acertos=0;
            for(int i=0; i<tam_seq; i++){
                if(seq[i]==player_seq[i]) acertos++;
            }

            if(acertos<tam_seq){                
                //penaliza o jogador em caso de erro
                tent--;

                if(tent>0) pontos-=10*(tam_seq-acertos);
                if(pontos<0) pontos=0;

                printf("Incorreto!\n");
            }else{  
                //diz que deve ser gerada uma nova sequencia em caso de acerto
                new_seq=1;
                cont++;
                printf("Correto!\n");
            }
        }

        printf("Tentativas disponiveis: %d\n", tent);
        printf("Pontuacao: %d\n", pontos);

        //sleep(2);
        //system("clear");
    }

    if(tent==0){
        printf("Nao ha mais tentativas disponiveis... Tente novamente!\n");
    }else{
        printf("Otima memoria! Parabens!!!\n");
    }

    //getchar();

    return 0;
}