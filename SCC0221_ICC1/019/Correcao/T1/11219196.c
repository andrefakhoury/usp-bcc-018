#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int seed, time, erros = 0, life=3, i=0, cont = 0, sequences_remaining, sequence = 1, pontos=0, numbers, game_on = 1, pontos_max=0, mat_comp[5][9], vet_player[9];
char dif;

//Função para mostrar as sequências, coletar as respostas do usuário e verificar o número de erros
int seq()
{
    printf("Sequencia #%d:\n", sequence);
    for(int j=0; j<numbers; j++)
    {
        printf("%d ", mat_comp[i][j]);
    }
    printf("\n");
    //sleep(time);
    //system("cls");
    for(int j=0; j<numbers; j++)
    {
        scanf("%d", &vet_player[j]);
    }
    for(int j=0; j<numbers; j++)
    {
        if (vet_player[j] != mat_comp[i][j])
            {
                erros++;
            }
    }
    return 1;
}

//Função que verifica as condições de vitória/derrota, calcula os pontos e o número de tentativas disponíveis
int victory_cond()
{
    if(erros == 0) //se o jogador acerta todos os números da sequência
    {
        printf("Correto!\n");
        sequence++;
        sequences_remaining--; //um subtrator para idêntificar quantas sequências ainda faltam ser resolvidas
        i++;
        cont = 0; //reseta o marcador de passagem pelo while
        pontos += pontos_max;
        pontos_max = numbers*10;
        printf("Tentativas disponiveis: %d\n", life);
        printf("Pontuacao: %d\n", pontos);

        if(sequences_remaining > 0) //chama a função seq() caso ainda possuam sequências a ser resolvidas
        {
            seq();
        }

        if(sequences_remaining == 0) //finaliza o jogo caso todas as sequências tenham sido resolvidas
        {
            printf("Otima memoria! Parabens!!!");
            game_on = 0;
            return 0;
        }      
    }
    while(erros != 0 && life > 1) //verifica se o jogador errou e ainda possui tentativas
    {
        printf("Incorreto!");
        cont = 1; //marca que o programa já passou por este while nesta sequência
        if (pontos_max - erros*10 < 0) //garante que a pontuação recebida em uma sequência não seja negativa
        {
            life--;
            pontos_max = 0;
            pontos += pontos_max; //soma a pontuação da rodada aos pontos totais
            erros = 0;
            printf("\nTentativas disponiveis: %d\nPontuacao: %d\n", life, pontos);
            pontos -= pontos_max; //retira a pontuação da rodada dos pontos totais para não soma-los mais de uma vez
            seq();
        }
        if (pontos_max - erros*10 >= 0)
        {
            life--;
            pontos_max -= erros*10; //soma a pontuação da rodada aos pontos totais
            pontos += pontos_max;
            erros = 0;
            printf("\nTentativas disponiveis: %d\nPontuacao: %d\n", life, pontos);
            pontos -= pontos_max; //retira a pontuação da rodada dos pontos totais para não soma-los mais de uma vez
            seq();
        }
    }
    if(life <= 1 && erros != 0) //verifica se o jogador e errou e não possui mais tentativas
    {
        if(cont == 0) //se o programa não passou pelo "while" ao menos uma vez naquela sequência
        {
            pontos += pontos_max - erros*10;
        }
        if(cont == 1) //se o programa já passou pelo "while" ao menos uma vez naquela sequência
        {
            pontos += pontos_max;
        }
        printf("Incorreto!\nTentativas disponiveis: 0\nPontuacao: %d\n", pontos); //Mensagem de derrota no jogo
        printf("Nao ha mais tentativas disponiveis... Tente novamente!"); //Mensagem de derrota no jogo
        game_on = 0;
        return 0;
    }
    return 1;
}

int main()
{    
    scanf("%d %c", &seed, &dif); //pega os valores de seed e dificuldade do jogo

    if(dif == 'F') //define os parâmetros para dificuldade fácil
    {
        sequences_remaining = 3;
        numbers = 5;
        time = 5;
        pontos_max = numbers*10;
    }
    
    if(dif == 'I') //define os parâmetros para dificuldade intermediário
    {
        sequences_remaining = 4;
        numbers = 7;
        time = 7;
        pontos_max = numbers*10;
    }

    if(dif == 'A') //define os parâmetros para dificuldade avançado
    {
        sequences_remaining = 5;
        numbers = 9;
        time = 10;
        pontos_max = numbers*10;
    }
    srand(seed); //utiliza o valor da seed para randomizar as sequências
    for(int i=0; i<sequences_remaining; i++) //define uma matriz com todas as sequências (uma por linha)
    {
        for(int j=0; j<numbers; j++)
        {
            mat_comp[i][j] = rand() % 10;
        }
    }
    
    seq(); //chama a função seq() pela primeira vez
    while(game_on == 1) //chama a função victory_cond() sempre que o jogo estiver "ligado"
    {
        victory_cond();
    }
return 0;
}