#include <stdio.h>   // p/ funções básicas, como printf() e scanf().
#include <stdlib.h> // P/ as funções rand() e srand().
#include <time.h>  // P/ as funções time() e clock() e a constante CLOCKS_PER_SEC.
#include <unistd.h>

//protótipos: 
/*void temporizador (int tempo);*/
/* A função acima exercerá o papel de pausar o programa pelo
tempo necessário e, fazer com que os valores apresentados sumam
na tela, para que o usuário não veja a sequência após o tempo 
determinado. */ 
void comparador (char D, int seq, int seed, int val, int seg);

/*void temporizador (int tempo) {
	float t1, t2=0;
    t1 = (float)clock()/(float)CLOCKS_PER_SEC; 
    //   Como a funcão clock() retorna o valor desde o início do programa
    // em milissegundos, t1 foi dividido pela constante CLOCKS_PER_SEC 
	// que equivale 1000, para transformar seu valor em segundos. 
    while (t2-t1<tempo) 
    	t2 = (float)clock()/(float)CLOCKS_PER_SEC;
    // O while irá rodar até que a diferença entre o tempo de início 
	//da função temporizador e o início do programa ser maior ou igual
	//o valor em segundos definido. 
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
	// Para a sequência "sumir" após sair do while, foi optado o recurso de pular várias linhas.
	return ;
} */


void comparador (char D, int seq, int seed, int val, int seg){

	int m, n = 0, k = 3, L[val], pontuacao = 0, resposta;
	int i, j, l[val], erro, diferenca;
	srand (seed);
	
	while (n < seq){
		j = 0, erro = 0;
		diferenca = val*10;
		pontuacao = pontuacao + val * 10;
		printf("Sequencia #%d:\n", n+1);
	
		for (i = 0; i < val; i++){ // Aqui é gerada uma lista a partir da função rand(), de acordo com a seed plotada na função srand().
			L[i] = rand()%10; 
			printf("%d ", L[i]);
		}
	
		printf("\n");	
		//temporizador(seg); ///////////////////// Função que passa "seg" segundos./////////////////////

		if (D == 'F') // De acordo com a dificuldade, é pedido ao usuário digitar a sequência que memorizou.
			scanf("%d %d %d %d %d", &l[0], &l[1], &l[2], &l[3], &l[4]);
		else if (D == 'I')
			scanf("%d %d %d %d %d %d %d", &l[0], &l[1], &l[2], &l[3], &l[4], &l[5], &l[6]);
		else if (D == 'A')
			scanf("%d %d %d %d %d %d %d %d %d", &l[0], &l[1], &l[2], &l[3], &l[4], &l[5], &l[6], &l[7], &l[8]);

		while (j < val){ //
			if (l[j] != L[j]){
				resposta = 1;                     //   Caso a resposta seja diferente a da lista, um erro é contabilizado e a variável "resposta" recebe
				erro = erro + 1;                  // o valor de 1. 
			}                                     
			if (j+1 == val && erro == 0)          //   Caso o usuário acerte toda a sequência, sem errar, é atribuído 2 à variável "resposta". 
				resposta = 2;
			j++;
		}
		
		if (resposta == 1 && k != 0){
	
			while (resposta == 1 && k != 0){
				k = k - 1;                      //   "k" iniciou valendo 3, que é o número de tentativas restantes.
				m = 0;                          //   Como resposta vale 1, houve pelo menos um erro, portanto é descontado o valor de
												// 1 no número de tentativas.
				while (m < erro){
					diferenca = diferenca - 10; //   Neste caso, o "while" exerce o papel de testar, caso o erro exceda o número máximo
					if (diferenca < 0 )         // permitido, que no caso é o valor de val*10.
						erro = 0;               //   Caso exceda, o erro é tomado como o menor número antes de da diferença ser igual a 0, podendo ser 0.
					else if (diferenca == 0)
						erro = m + 1;
				
					m++;
				}
	
				pontuacao = pontuacao - erro*10;
	
				if (pontuacao < 0) //  Este "if" impede com que o valor da pontuação seja negativo.
					pontuacao = 0;

				printf("Incorreto!\n");
				printf("Tentativas disponiveis: %d\n", k);
				printf("Pontuacao: %d\n", pontuacao);
			
				if (k != 0)
					printf("Sequencia #%d:\n", n + 1);
	
				if (k == 0){                            //  Caso o número de tentativas chegue a 0, é imprimido a mensagem abaixo, e terminado a função.
					printf("Nao ha mais tentativas disponiveis... Tente novamente!\n");
					return ;
				}
		
				for (m = 0; m < val; m++) //   Caso o erro ocorra após outro erro, é imprimida a mesma sequência e solicitado novamente para que
					printf("%d ", L[m]);  // o usuário digite o que memorizou.
				
				printf("\n");
				//temporizador(seg);  ///////////////////// Função que passa "seg" segundos./////////////////////
			
				if (D == 'F')
					scanf("%d %d %d %d %d", &l[0], &l[1], &l[2], &l[3], &l[4]);
				else if (D == 'I')
					scanf("%d %d %d %d %d %d %d", &l[0], &l[1], &l[2], &l[3], &l[4], &l[5], &l[6]);
				else if (D == 'A')
					scanf("%d %d %d %d %d %d %d %d %d", &l[0], &l[1], &l[2], &l[3], &l[4], &l[5], &l[6], &l[7], &l[8]);
					
				m = 0, erro = 0;
				while (m < val){
					if (l[m] != L[m]){             //   Novamente, os erros são somados na variável "erro".
						erro = erro + 1;           //   Caso acerte, o valor de "resposta" torna-se 2 e o códico "sai" do 
					}                              // "while (resposta == 1 && k != 0)" e do "if (resposta == 1 && k != 0)".
					if (erro == 0 && m+1 == val){
						resposta = 2;
					}
					m++;
				}
			}
		}
	
		if (resposta == 2){
			printf("Correto!\n");                  //   Quando "resposta" vale 2, muda-se a sequência de números.
			n = n + 1;
			printf("Tentativas disponiveis: %d\n", k);
			printf("Pontuacao: %d\n", pontuacao);
			if (n == seq){
				printf("Otima memoria! Parabens!!!\n"); //   Chegando-se a acertar a última sequência do jogo, o usuário recebe 
				return ;                                // tal mensagem, e a função é terminada.
			}
		}
	}
}

int main(void){
    sleep(1);
    printf("oie\n");
	
	int i = 0, seed;
	char dif;
	
	while ( i != 1 ){
	
		scanf("%d %c", &seed, &dif ); 	// Leitura da semente e da dificuldade do jogo.
										// A função comparador() é chamada diferentemente, de acordo com o valor de "dif".	
		if (dif == 'F'){
			comparador (dif, 3, seed, 5, 5);
			return 0;
		}
		else if (dif == 'I'){
			comparador (dif, 4, seed, 7, 7);
			return 0;
		}
		else if (dif == 'A'){
			comparador (dif, 5, seed, 9, 10);
			return 0;
		}
		else // Caso o usuário digite uma letra ou número inválida, a mensagem abaixo é exibida e é solocitado novamente os valores pelo usuário.
			printf("Digite um valor e dificuldade valido. \n");
	}
}
