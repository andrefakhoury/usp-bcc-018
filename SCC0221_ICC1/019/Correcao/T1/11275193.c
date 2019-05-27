#include <stdio.h>
#include<stdlib.h>
#include<unistd.h>
///////////////////////////////////////////////////////////////////////////////////////////////////

void zero(int myseed,int sizee, int* loca, int thefirst){
 //////////////////////////////////////////////////////////////////////////////////////////////////
    // 0.1 - o 'srand' serve para utilizar a seed . O primeiro 'for' serve para ignorar os 'n' primeiros resultados
    //       dos valores que o 'rand' gera, isso existe porque toda vez que utilizamos a mesma seed todos os valores
    //       vao seguir uma mesma ordem, todavia, quando vamos para sequencias posteriores a primeira, devemos ignorar
    //       os valores que vieram antes, ex.: na terceira sequencia de um teste 'F', ignoramos os 5 primeiros valores
    //       devido a primeira sequencia ja ter ido e do sexto ao decimo, devido a segunda sequencia ja ter ido.
    //       O segundo for itera por um tamanho igual ao tamanho de uma sequencia e da a esses valores o valor do 'rand'
    //       que e dividido por '10' para que os valores estejam compreendido entre e inclindo 0 a 9. O 'discartable' e o
    //       fato do valor do primeiro 'for' ter sido aumentado em '1' e o do segundo ter sido reduzido em '1' foi
    //       simplesmente para o run.codes nao dar variavel nao utilizada     
    int discartable;
    srand(myseed);
    if(thefirst){
        discartable=0;
        for(int i=0;i<thefirst+1;i++){
            discartable=rand()%10;
        }
        loca[0]=discartable;
        for(int j=1;j<sizee;j++){
            loca[j]=(rand()%10);
        }
    }
    else{
        for(int j=0;j<sizee;j++){
            loca[j]=(rand()%10);
        }
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////
                               
            // Nesse caso particular deveria ter sido enviado o 'first' que esta comentado
            // mas o run.codes nao aceita, entao foi utilizado o segundo, comentarei os dois


/*
void first(int sizee, int* loca, int thetime){
 //////////////////////////////////////////////////////////////////////////////////////////////////
    // 1.1.1 - a combinacao "print('\r')" e "fflush(stdout)" servem para respectivamente limpar toda a linha
    //         com o '\r' ja que nao substitue por nada e imprimir o que se encontra armazenado no buffer com
    //         o fflush(stdout)
    printf("\r");
    fflush(stdout);
    // 1.1.2 - Ocorre o 'for' com um tamanho igual ao tamanho da sequencia - 'sizee' - imprimindo a 'array' antes
    //          criada no 'zero' depois e dado um 'fflush(stdout)' para imprimir o resultado ja existente e depois
    //          de 5 segundos - com o 'sleep(5)' - e dado um '\r                   \r' para limpar o resultado da 
    //          linha e imprimir espaços em branco e voltar ao inicio da linha e por fim e impresso isso com o 
    //          'fflush(stdout)' novamente
    for(int j=0;j<sizee;j++){
        printf("%d ",*(loca+j));
    }
    fflush(stdout);
    sleep(thetime);
    printf("\r                   \r");
    fflush(stdout);
}
*/

void first(int sizee, int* loca){
 //////////////////////////////////////////////////////////////////////////////////////////////////
    // 1.2.1 - Esse caso simplesmente existe para cumpir com as exigencias do run.codes e so imprime os valores
    //         da sequencia da 'array' feita em 'zero'
    for(int j=0;j<sizee;j++){
        printf("%d ",*(loca+j));
    }
    printf("\n");
}

///////////////////////////////////////////////////////////////////////////////////////////////////

int second(int sizee, int* loca){
 //////////////////////////////////////////////////////////////////////////////////////////////////
    // 2.1 - E criado uma 'array' 'Test' para guardar os valores digitados pelos usuarios, o 'pos' 
    //       serve para definir na 'main' se sera um resultado correto - caso o 'pos' seja igual a '0' -
    //       ou quanto sera retirado do 'localpoints'
    int Test[9]={0};
    int pos;
    pos=0;
 //////////////////////////////////////////////////////////////////////////////////////////////////
    // 2.2 - Ocorre um 'for' com um numero de vezes igual ao tamanho da sequencia e ela e comparada com
    //       a 'array', caso seja igual nada acontece, caso seja diferente e adicionado um valor igual a '10'
    //       ao 'pos' e sera subtraido do 'localpoints' na main esse pos depois. o 'second' retorna o 'pos'    
    for(int i=0;i<sizee;i++){
        scanf("%d",&Test[i]);
        if(Test[i]!=(*(loca+i))){
            pos+=10;
        }
    }
    return pos;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

int main(void){
    // 3.1 - Sao declaradas diversas variaveis do tipo 'int' que serao utilizadas depois. O 'Fn' serve para a 'array' que
    //       ira guardar os valores das sequencias 
    int seeed,theoptions,times,lengthofa,counter,definer,tot,tocont,toend,points,localpoints;
    char level;
    int Fn[9]={0};
    int* loc=Fn;
    //int thetime;

 //////////////////////////////////////////////////////////////////////////////////////////////////
    // 3.2 - Nesse sao recebidos os valores referentes a seed desejada pelo usuario e a dificuldade, respectivamente
    scanf("%d %c",&seeed,&level);

 //////////////////////////////////////////////////////////////////////////////////////////////////
    // 3.3 - Aqui e feito um esquema no qual de acordo com a dificuldade e escolhido um numero, sendo o valor das dezenas
    //       a quantidade de repeticoes e o de unidades o tamanho da sequencia. O 'thetime' serve para definir o tempo do
    //       sleep
    if(level=='F'){
        theoptions = 35;
        //thetime=5;
    }
    else if(level=='I'){
        theoptions = 47;
        //thetime=7;
    }
    else{
        theoptions = 59;
        //thetime=10;
    }

 //////////////////////////////////////////////////////////////////////////////////////////////////
    // 3.4 - Aqui no 'counter' e dado o valor inicial de '3' que sera diminuido a cada erro e quando chegar ao '0' quer
    //       dizer que suas chances acabaram. No 'times' eu acho as dezenas ao dividir um 'int' por '10', e as dezenas
    //       representam a quantidade de repeticoes. No 'lengthofa' pega-se o 'resto' da divisao por '10' que representa
    //       as unidades e que por sua vez representa o tamanho da sequencia. O 'toend' tem valor inicial de '0', todavia
    //       se voce tiver 3 erros - e logo recebera a mensagem:'Não ha mais tentativas disponiveis... Tente novamente!'-
    //       o 'toend' recebe o valor de '1' apenas para facilitar os 'breaks'.O 'points' vai dizer quantos pontos voce tem
    counter=3;
    times=theoptions/10;
    lengthofa=theoptions%10;
    toend=0;
    points=0;
 //////////////////////////////////////////////////////////////////////////////////////////////////
    // 3.5 - o 'for' que vai de '0' ate menor que 'times', ou seja se repete 'times' vezes, serve pelo proposito de que
    // o 'times' simboliza o numero de repeticoes de uma sequencia
    for(int i=0;i<times;i++){
     //////////////////////////////////////////////////////////////////////////////////////////////
        // 3.6 - O 'tocont' que e a priori '0' serve para saber se eu posso ir para uma nova sequencia - caso seja '1' -
        //       ou repetir a mesma sequencia - caso seja '0' - para o usuario tentar responder ela certo de novo.
        //       'localpoints' e igual a '10' vezes o tamanho da sequencia('lengthofa') que e o valor maximo inicial
        //       daquela sequencia 
        tocont=0;
        localpoints=(10*lengthofa);
     //////////////////////////////////////////////////////////////////////////////////////////////
        // 3.7 - Como ja dito em '3.6' o 'while' aqui serve para so permitir ir para a outra sequencia se o usuario der a
        //       resposta certa - ou suas chances acabarem
        while(tocont==0){
         //////////////////////////////////////////////////////////////////////////////////////////
            // 3.8 - E printado os textos padrao das respostas e inicializada a funcao 'zero' que serve para criar a 'array'
            //       base para comparacao e o 'first' imprime os textos por um certo periodo de tempo e o 'second' compara
            //       eles - eles serao mais explicados nas suas funcoes logo a cima. 'tot' serve para manter a mesma 'seed' 
            //       e pegar os 'n' numeros desejados, tambem sera melhor explicado nas funcoes. O 'first' comentado é aquele
            //       que deveria ser utiizado caso fosse desejado utilizar o sleep. 
            printf("Sequencia #%d:\n",(i+1));
            tot=lengthofa*i;
            zero(seeed,lengthofa,loc,tot);
            //first(lengthofa,loc,thetime);
            first(lengthofa,loc);
            definer=second(lengthofa,loc);
         //////////////////////////////////////////////////////////////////////////////////////////
            // 3.9 - No 'if' temos uma resposta caso os resultados digitados pelo usuario sejam iguais aos gerados pelos
            //       valores aleatorios, alem disso o 'tocont' se tornando '1' simboliza que o 'while' deve acabar.
            //       O 'else' simboliza o fato de existir uma diferenca entre a sequencia gerada e a digitada pelo usuario
            //       onde ha uma reducao no 'counter' simbolizando a reducao no numero de chances existentes, ocorre uma 
            //       reducao do valor maximo da sequencia - 'localpoints' - de acordo com o 'definer' que e melhor explicado
            //       na funcao 'second' e caso o valor seja reduzido a '0' ele volta ao valor minimo de '0'. Tambem sao
            //       printados se esta correto ou nao, a pontuacao e as tentativas restantes. Tambem existe o 'if' seguinte
            //       que e ativado caso o 'counter' chegue a '0' e ao 'toend' e dado o valor de '1' que auxiliara nos 'breaks'
            //       para poder sair do 'while' e do 'for'
            if(definer==0){
                tocont=1;
                printf("Correto!\nTentativas disponiveis: %d\nPontuacao: %d\n",counter,(points+localpoints));
            }
            else{
                counter-=1;
                localpoints-=definer;
                if(localpoints<0){
                    localpoints=0;
                }
                printf("Incorreto!\nTentativas disponiveis: %d\nPontuacao: %d\n",counter,(points+localpoints));
            }
            if(counter<=0){
                toend=1;
                break;
            }
        }
     //////////////////////////////////////////////////////////////////////////////////////////////
        // 3.10 - Ao 'points' e finalmente adicionado o valor de 'localpoints' apos terem sido reduzidos ou nao devido a erros
        //        Novamente o 'toend' e utilizado para imprimir a resposta e dar um 'break'
        points+=localpoints;

        if(toend){
            printf("Nao ha mais tentativas disponiveis... Tente novamente!\n");
            break;
        }

    }
 //////////////////////////////////////////////////////////////////////////////////////////////////
    // 3.11 - Finalmente, caso o numero de erros tenha sido menor que 3 e dado a resposta de vitoria
    if(toend==0){
        printf("Otima memoria! Parabens!!!\n");
    }
}