/*          TRABALHO ICC - 1
            JOGO DE  MEMÓRIA
            ALUNO:VICTOR RODRIGUES RUSSO 
            NUSP:11218855
*/
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<unistd.h>
/*biblioteca unistd.h tem a função sleep no Linux*/
int main(void)
{
    int seed,num_seq,num_valores,chances=3,seq[9],aux,cont,pontuacao=0,max_pont;
    //int tempo;//variavel que controla o tempo do sleep, declarada comentada para não dar erro no run.codes
    int i,j;//iteradores
    char nivel;
    scanf("%d %c",&seed,&nivel);
    switch(nivel)//nesse switch os parametros são ajustados de acordo com a dificuldade
    {
        case 'F':
                num_seq=3;
                num_valores=5;
                //tempo=5;
                break;
        case 'I':
                num_seq=4;
                num_valores=7;
                //tempo=7;
                break;
        case 'A':
                num_seq=5;
                num_valores=9;
               // tempo=10;
                break;  
        default:num_seq=3;//caso o usuário digite uma opção inválida, o padrão é fácil
                num_valores=5;
                //tempo=5;

    }
    srand(seed);//geração da semente baseada no input do usuário
    for(i=1;i<=num_seq;i++)//for principal onde ocorre o jogo
    {
        for(j=0;j<num_valores;j++)//nesse for são sorteadas os valores da sequencia
        {
            seq[j]=rand()%10;
        }
        max_pont=num_valores*10;
        do//do while para cada sequência, caso o jogador erre fica preso no laço até acertar ou as chances acabarem
        {
            cont=0;
            printf("Sequencia #%d:\n",i);
            for(j=0;j<num_valores;j++)//nesse for são impressos os valores da sequencia
            {
                printf("%d ",seq[j]);
            }
            /*fflush(stdout);//limpa o buffer de saída garantindo que a sequencia é impressa antes do sleep
            sleep(tempo);//funçao sleep, pausa o processamento por uma quantidade tempo de segundos(OBS:no Windows essa função é dada em milisegundos)
            printf("\r                               \r");//limpa a sequencia após o sleep*/
            printf("\n");
            for(j=0;j<num_valores;j++)//nesse for o jogador digita os valores que já são conferidos
            {
                scanf("%d",&aux);
                if(aux==seq[j])//confere se o jogador acertou
                    cont++;
            }
            if(cont==num_valores)//sequencia totalmente certa
            {
                printf("Correto!\n");
            }
            else//sequencia errda
            {
                printf("Incorreto!\n");
                chances--;
                max_pont-=((num_valores-cont)*10);//reduz a quantidade de chances e define uma nova pontuação max
                if(max_pont<0)//confere pontuação negativa
                    max_pont=0;
            }
            printf("Tentativas disponiveis: %d\n",chances);
            printf("Pontuacao: %d\n",pontuacao+max_pont);
            if(chances==0)//sai do laço quando as chances se esgotam
                break;
        }while(cont!=num_valores);//preso no laço enquanto nao acertar toda a sequencia
        pontuacao+=max_pont;
        if(chances==0)//sai do laço quando as chances se esgotam
            break;
    }
    if(i==num_seq+1)//se o jogador acertou todas as sequencias
        printf("Otima memoria! Parabens!!!\n");
    else//caso o jogador perca todas as chances
        printf("Nao ha mais tentativas disponiveis... Tente novamente!\n");
}