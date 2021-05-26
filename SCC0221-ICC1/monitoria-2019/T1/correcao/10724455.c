/*Trabalho destinado a disciplina de ICC I
Nome: Yago Poletto Salgado                                      Número USP: 10724455
*/


/*#include <unistd.h> - biblio comentada por uso indisponivel no RunCodes*/
#include <stdio.h>
#include <stdlib.h>


void funcao_f(int seed);
void funcao_i(int seed);
void funcao_a(int seed);


int main(void){
    /*Declarando e recebendo variaveis iniciais de controle*/
    int seed;
    char dificuldade;
    scanf("%d", &seed);
    scanf(" %c", &dificuldade);

    /*Escolhendo uma das dificuldades de jogo e chamando sua respectiva funcao*/
    switch(dificuldade){
        case 'F':
            funcao_f(seed);
            break;
        case 'I':
            funcao_i(seed);
            break;
        case 'A':
            funcao_a(seed);
            break;
    }
    return 0;
}


/*Funcao que inicia um modo de jogo facil
*args: Seed para a random.
*/
void funcao_f(int seed){
    /*Declarando vetores e variaveis necessarias*/
    int vetor[5];
    int vetor_aux[5];
    int pmax, ptotal=0, pcontrol, teste=0, erro=0, tentativas=0, z=1, rodagem=0;
    srand(seed);
    
    /*Rodando n vezes, em que n é o numero relativo de vezes rodadas de cada caso.*/
    while(tentativas<3 && z<4){
        /*Trocando a sequencia, caso acerto*/
        if(rodagem!=z){
            for(int i=0; i<5; i++){
                vetor[i] = rand()%10;
            }
            pmax=50;
        }
        rodagem=z;
        
        /*Printando sequencia*/
        printf("Sequencia #%d:\n", z);
        for(int i=0; i<5; i++){
            printf("%d ",vetor[i]);
        }
        printf("\n");

        /*
        Utilizando funcao sleep() e system() para pausar o programa por 5 segundos
        e limpar a tela, respectivamente. Porém, apesar de funcionamento coerente quando
        executado no computador, apresentou incompatibilidade com o RunCodes, portanto, foi
        comentada.
        */
        //sleep(5);
        //system("clear");

        /*Recebendo inputs, e posteriormente verificando acertos*/
        for(int i=0; i<5; i++){
            scanf("%d", &vetor_aux[i]);
        }
        for(int i=0; i<5; i++){
            if(vetor[i]==vetor_aux[i]){
                teste++;
            }else {
                erro++;
            }
        }
        /*Atualizando Maximo valor da pontuacao em caso de erros*/
        pmax=pmax-(10*erro);
        if(pmax<0){
            pmax=0;
        }

        /*Verificando corretude dos inputs e mostrando na tela cada caso*/
        if(teste==5){
            z++;
            ptotal=ptotal+pmax;
            printf("Correto!\n");
            printf("Tentativas disponiveis: %d\n", (3-tentativas));
            printf("Pontuacao: %d\n", ptotal);
        }else{
            tentativas++;
            pcontrol=ptotal+pmax;
            printf("Incorreto!\n");
            printf("Tentativas disponiveis: %d\n", (3-tentativas));
            printf("Pontuacao: %d\n", pcontrol);
        }
        teste=0;
        erro=0;  
    }
    /*Se acabar o jogo ou acabarem as tentativas, printa na tela*/
    if(tentativas==3){

        printf("Nao ha mais tentativas disponiveis... Tente novamente!\n");

    }else{
        printf("Otima memoria! Parabens!!!\n");

    }
    return;
}


/*Funcao que inica um modo de jog intermediario
*args: Seed para a random.
*/
void funcao_i(int seed){
    /*Declarando vetores e variaveis necessarias*/
    int vetor[7];
    int vetor_aux[7];
    int pmax=70, ptotal=0, pcontrol=0, teste=0, erro=0, tentativas=0, z=1, rodagem=0;
    srand(seed);
    /*Rodando n vezes, em que n é o numero relativo de vezes rodadas de cada caso.*/
    while(tentativas<3 && z<5){
        /*Trocando a sequencia, caso acerto*/
        if(rodagem!=z){
            for(int i=0; i<7; i++){
                vetor[i] = rand()%10;
            }
        pmax = 70;
        }
        rodagem=z;

        /*Printando sequencia*/
        printf("Sequencia #%d:\n", z);
        for(int i=0; i<7; i++){
            printf("%d ",vetor[i]);
        }
        printf("\n");

        /*
        Utilizando funcao sleep() e system() para pausar o programa por 5 segundos
        e limpar a tela, respectivamente. Porém, apesar de funcionamento coerente quando
        executado no computador, apresentou incompatibilidade com o RunCodes, portanto, foi
        comentada.
        */
        //sleep(5);
        //system("clear");

        /*Recebendo inputs, e posteriormente verificando acertos*/
        for(int i=0; i<7; i++){
            scanf("%d", &vetor_aux[i]);
        }
        for(int i=0; i<7; i++){
            if(vetor[i]==vetor_aux[i]){
                teste++;
            }else {
                erro++;
            }
        }
        /*Atualizando Maximo valor da pontuacao em caso de erros*/
        pmax=pmax-(10*erro);
        if(pmax<0){
            pmax=0;

        }
        /*Verificando corretude dos inputs e mostrando na tela cada caso*/
        if(teste==7){
            z++;
            ptotal += pmax;
            printf("Correto!\n");
            printf("Tentativas disponiveis: %d\n", (3-tentativas));
            printf("Pontuacao: %d\n", ptotal);
        }else{
            tentativas++;
            pcontrol = ptotal + pmax;
            printf("Incorreto!\n");
            printf("Tentativas disponiveis: %d\n", (3-tentativas));
            printf("Pontuacao: %d\n", pcontrol);
        }
        teste=0;
        erro=0;
    }

    /*Se acabar o jogo ou acabarem as tentativas, printa na tela*/
    if(tentativas==3){
        printf("Nao ha mais tentativas disponiveis... Tente novamente!\n");
    }else{
        printf("Otima memoria! Parabens!!!\n");
    }
    return;
}


/*Funcao que inicia um modo de jogo avancado
*args: Seed para a random.
*/
void funcao_a(int seed){
     /*Declarando vetores e variaveis necessarias*/
    int vetor[9];
    int vetor_aux[9];
    int pmax=90, ptotal=0, pcontrol=0, teste=0, erro=0, tentativas=0, z=1, rodagem=0;
    srand(seed);
    /*Rodando n vezes, em que n é o numero relativo de vezes rodadas de cada caso.*/
    while(tentativas<3 && z<6){
        /*Trocando a sequencia, caso acerto*/
        if(rodagem!=z){
            for(int i=0; i<9; i++){
                vetor[i] = rand()%10;
            }
        pmax = 90;
        }
        rodagem=z;

        /*Printando sequencia*/
        printf("Sequencia #%d:\n", z);
        for(int i=0; i<9; i++){
            printf("%d ",vetor[i]);
        }
        printf("\n");

        /*
        Utilizando funcao sleep() e system() para pausar o programa por 5 segundos
        e limpar a tela, respectivamente. Porém, apesar de funcionamento coerente quando
        executado no computador, apresentou incompatibilidade com o RunCodes, portanto, foi
        comentada.
        */
        //sleep(5);
        //system("clear");

        /*Recebendo inputs, e posteriormente verificando acertos*/
        for(int i=0; i<9; i++){
            scanf("%d", &vetor_aux[i]);
        }
        for(int i=0; i<9; i++){
            if(vetor[i]==vetor_aux[i]){
                teste++;
            }else {
                erro++;
            }
        }
        /*Atualizando Maximo valor da pontuacao em caso de erros*/
        pmax=pmax-(10*erro);
        if(pmax<0){
            pmax=0;
        }
        /*Verificando corretude dos inputs e mostrando na tela cada caso*/
        if(teste==9){
            z++;
            ptotal += pmax;
            printf("Correto!\n");
            printf("Tentativas disponiveis: %d\n", (3-tentativas));
            printf("Pontuacao: %d\n", ptotal);
        }else{
            tentativas++;
            pcontrol = ptotal + pmax;
            printf("Incorreto!\n");
            printf("Tentativas disponiveis: %d\n", (3-tentativas));
            printf("Pontuacao: %d\n", pcontrol);
        }
        teste=0;
        erro=0;
    }
     /*Se acabar o jogo ou acabarem as tentativas, printa na tela*/
    if(tentativas==3){
        printf("Nao ha mais tentativas disponiveis... Tente novamente!\n");
    }else{
        printf("Otima memoria! Parabens!!!\n");
    }
    return;
}
