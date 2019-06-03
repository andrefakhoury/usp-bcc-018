#include <stdio.h>  //biblioteca para linux
#include <stdlib.h> //biblioteca da funçao rand
#include <unistd.h> //biblioteca da funçao system

int main(){

	/*variáveis*/
	int k, i, errou=0, s=1, seed, seq, tentativas=3, pontos=0, total=0;
	char nivel;
	int sequencia[9], resposta[9];

	scanf("%d %c", &seed, &nivel);	//entradas que vão definir o rumo do jogo
    srand(seed);	//semente para gerar números aleatorios
     
	 /*parâmetros de cada nível*/
    if(nivel=='F'){
        seq=3;
        i=5;
        //seg=5; //tempo que o jogador deve esperar
	}else
    if(nivel=='I'){
        seq=4;
        i=7;
        //seg=7;
    }
    if(nivel=='A'){
        seq=5;
        i=9;
        //seg=10;
    }

	do{
	 	seq--; //tira um da sequência

		for(k=0;k<i;k++){
			sequencia[k] = rand()%10; //atribui os números de rand a um vetor
		}

		pontos=i*10; //máximo de pontos da sequência

		do{
			errou=0;
			printf("Sequencia #%d:\n", s++); //diz qual sequência está para ser decorada

        	for(k=0;k<i;k++){
		 	printf("%d ", sequencia[k]); // imprime a sequência
		 	}
			 	printf("\n");
			    //sleep(seg); 		//espera alguns segundos antes de prosseguir lendo o código
             	//system("clear"); //limpa a tela
		      
   		   	for(k=0;k<i;k++){
   		 	scanf("%d", &resposta[k]); //lê a resposta do jogador
   		   }
   		   
			/*sistema de pontuação*/
			for(k=0;k<i;k++){
				
		 		if(sequencia[k]!=resposta[k]){ //caso o jogador erre
					pontos-=10;	 //subtrai 10 da pontuação total sempre que o jogador errar
					errou+=1; 	//contador que controla o laço

					if(pontos<0){ //impede que a pontuação fique negativa
						pontos=0;
					}
				}
				
			}	
				
			if(errou!=0){ 		 //quando o jogador erra essas condições devem ser compridas
				s--; 			//contador que representa a sequência que o jogador está
				tentativas-=1; //tira uma chance sempre que o jogador erra
				printf("Incorreto!\n");
				printf("Tentativas disponiveis: %d\n", tentativas);
				printf("Pontuacao: %d\n",total+pontos);
			}
			if(errou==0){
				total+=pontos;
				printf("Correto!\n");
				printf("Tentativas disponiveis: %d\n", tentativas);
				printf("Pontuacao: %d\n",total);
			}
				
			if(tentativas==0){ //quando o jogador perder todas as chances o laço será terminado
				errou=0;
			}

		}while(errou>0); //caso o jogador erre o laço ira se repetir desde que reste tentativas

	}while(seq>0 && tentativas!=0); //condições para que o jogo continue

	if(tentativas!=0){ 
		printf("Otima memoria! Parabens!!!\n");	 //caso o jogador vença o jogo 
	}
	else{
		printf("Nao ha mais tentativas disponiveis... Tente novamente!\n"); //caso ele erre além do número de tentativas
	}
		
    return 0;
}
