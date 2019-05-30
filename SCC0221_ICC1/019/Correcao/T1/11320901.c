#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
 
int fileCmp(int *file1, int *file2, int terms)
{
	int counter = 0;
  	//Funcao que atraves de uma iteração compara os vetores
  	// Quando os valores indexado por i nos vetores são iguais //a função retorna 0, e quando são diferentes, ela retorna //1.
    
	for (int i = 0; i < terms; i++)
        if (file1[i] != file2[i])
            counter++;


    return counter;
}
void printFila(int *fila, int terms){
  //Printa todos os elementos da fila de uma matriz
    for (int i = 0; i < terms; i++)
        if(i == terms -1)printf("%d", fila[i]);
        else printf("%d ", fila[i]);
    printf("\n");
    return;
}
int scaneiaFila(int *vet, int terms)
{
  //Escaneia a fileira que vai ser comparada com a que vai ser gerada aleatoriamente
    for (int i = 0; i < terms; i++)
        scanf("%d", &vet[i]);
 
    return 0;
}
 
void opF(int seed, int lin, int col, int ponto){
  //Seed é a semente recebida pelo usuario
    srand(seed);
  //Declaracao de variaveis
    int flag = 1;
    int mat[lin][col];
    int ans[col];
    int pontos = 0;
    int aux = -1;
	int tentativas = 3;
    int flag2 = 0;
	int vence = 0;

	//iteração usando "for" para gerar e armazenar os numeros aleatórios
    for (int i = 0; i < lin; i++)
    {
        pontos += ponto;
        for (int j = 0; j < col; j++)
        {
            aux = (rand() % 10);
            mat[i][j] = aux;
        }
        
        //Uso do while para rodar as funções dos programa, caso a tentativa e a fileira tenha os mesmos numeros vai ser retornado uma flag com valor 0
        while (flag != 0)
        {
            printf("Sequencia #%d:\n",i+1);
            printFila(mat[i], col);
            //usleep(5000000);
            //printf("\033[H\033[J");
            scaneiaFila(ans, col);
            
            flag = fileCmp(ans, mat[i], col);


            if (flag2 != 1)
                pontos -= (flag * 10);
            
            
            if (flag == col)
               flag2 = 1;
            if (pontos < 0)
            {
                pontos = 0;
            }

            //Condições de funcionamento do jogo
            if(flag == 0){
				printf("Correto!\n");
				printf("Tentativas disponiveis: %d\n",tentativas);
				printf("Pontuacao: %d\n",pontos);
				vence++;
				if(vence == lin)
				{
					printf("Otima memoria! Parabens!!!");
					return;
				}
            }else{
             	tentativas -= 1;
                printf("Incorreto!\n");
             	printf("Tentativas disponiveis: %d\n",tentativas);
              	if(tentativas == 0)
				{
                    

                    printf("Pontuacao: %d\n",pontos);
                    printf("Nao ha mais tentativas disponiveis... Tente novamente!\n");
                    return;
                }
                

                printf("Pontuacao: %d\n",pontos);
            }
            
 
        }
        
        flag = 1;
        flag2 = 0;
    }
 
}
 
 
int main(int argc, char const *argv[])
{
    int seed = -1;
 
    char op = '0';
  //Escaneia a entrada da semente e do nivel escolhido do jogo
    scanf("%d %c", &seed, &op);
 
    switch (op)
    {
    case 'F':
        opF(seed, 3, 5, 50);
        break;
    case 'I':
        opF(seed, 4, 7, 70);
        break;
    case 'A':
        opF(seed, 5, 9, 90);
        break;
 
 
    default:
        break;
    }
 
 
    return 0;
}