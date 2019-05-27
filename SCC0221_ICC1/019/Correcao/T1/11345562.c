//Erick Barcelos
//Nº USP: 11345562

//bibliotecas
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main(){
	int valores_seq[45], valores_resp[45], semente = 0, acertos = 0, inicio= 0, value_max_f = 5, value_max_i = 7, value_max_a = 9, chances = 3, marc=0, pont_max = 0, pont_g = 0;
	char nivel;

	scanf("%d %c", &semente, &nivel); //digitar semente e o nivel

	srand(semente);

	for (int i= 0; i<54; i++) //alocar 54 espaços na memoria
	{
		valores_seq[i]= rand() % 10; // randomizar os valores da sequencia
	}

    switch(nivel){//para escolher os niveis
    	case 'F':
			for (int i= 0; i<3; i++)// loop para as tres sequencias
			{
				acertos = 0; //iniciar acertos
				marc=1; // iniciar marcador(qual vez o usuario passou pelo loop de sequencia)

        while(acertos !=5 && chances!=0)//enquantos os acertos forem diferentes de cinco e as chances de 0, o loop continua
				{
					acertos = 0;
          printf("Sequencia #%d:\n", i+1); //imprimir numero da sequencia
					for (int i= inicio; i<value_max_f; i++)//pecorrer os valores da sequencia
					{
						printf("%d ", valores_seq[i] ); // imprimir valores da sequencia
						//fflush(stdout); // executar o printf antes do sleep
					}
					//sleep(5); //aparecer por 5 seg
					//system("clear"); limpar tela
					printf("\n");
					for (int i= inicio; i<value_max_f; i++) //pecorrer os valores das respostas
					{
						scanf("%d", &valores_resp[i] ); // digitar valores das respostas
					}
					for (int i= inicio; i<value_max_f; i++) // percorrer respostas e sequencias
					{
						if(valores_resp[i]==valores_seq[i]) // para encontrar valores iguais entre as duas
						{
							acertos++; // se tiver acrescenta acertos
						}
					}
					if(acertos == 5) // se acertos forem iguais...
					{
              printf("Correto!");// imprime 'correto'

              if(marc==1) // se o usuario passou pela primeira vez pela sequencia
              {
                pont_g += acertos*10; //pontos gerais sao iguais a multiplicaçao de acertos por 10 (se o usuario acertou todas as respostas)
              }
					}
						else // se acertos nao forem iguais a 5...
						{
							printf("Incorreto!"); //... imprime 'incorreto' e diminue as tentativas (nao acertou todas as respostas)
							chances--; //chances = tentativas
              if(marc==1) // se ele errou pela primeira vez...
              {
                pont_max=acertos*10; //pontos maximos sao iguais a multiplicaçao de acertos por 10
                pont_g+=pont_max; // e pontos gerais ficam igual a pontos gerais mais pontos maximos
              }
              else // se nao for a primeira vez
              {
                if(pont_max!=0) // e se ponto maximo for diferente de 0
                {
                  pont_g -= (5-acertos)*10; // pontos gerais sao iguais a 5 menos quantos acertos ele teve multiplicado por 10 (seria a pontuacao com erros)
                }
              }
            }

            if(pont_g<0) // no jogo da memoria nao pode ter uma pontucao negativa, esse if serve pra zerar os numeros negativos
            {
              pont_g=0;
            }

            printf("\nTentativas disponiveis: %d", chances); //imprimir tentativas disponiveis
            printf("\nPontuacao: %d\n", pont_g); // imprimir pontuacao

            marc=2; // declarando 2 para gravar que é a segunda vez q o usuario vai passar pela sequencia

			  }
				inicio+=5; // alocar mais 5 espaços na memoria
				value_max_f+=5; // aumentar o valor maximo

      }
	    break; // parar caso facil


  case 'I':// similar ao primeiro caso so que com mudança no numero de sequencias, numero de valores e segundos que a sequencia aparece
			for (int i= 0; i<4; i++)// de 3 para 4 sequencias
			{
				acertos = 0;
				marc=1;

        while(acertos !=7 && chances!=0) // 7 valores
				{
					acertos = 0;
          printf("Sequencia #%d:\n", i+1);
					for (int i= inicio; i<value_max_i; i++)
					{
						printf("%d ", valores_seq[i] );
						//fflush(stdout);
					}
					//sleep(7);
					//system("clear");
					printf("\n");
					for (int i= inicio; i<value_max_i; i++)
					{
						scanf("%d", &valores_resp[i] );
					}
					for (int i= inicio; i<value_max_i; i++)
					{
						if(valores_resp[i]==valores_seq[i])
						{
							acertos++;
						}
					}

					if(acertos == 7)
					{
              printf("Correto!");

              if(marc==1)
              {
                pont_g += acertos*10;
              }
					}
						else
						{
							printf("Incorreto!");
							chances--;
              if(marc==1)
              {
                pont_max=acertos*10;
                pont_g+=pont_max;
              }
              else
              {
                if(pont_max!=0)
                {
                  pont_g -= (7-acertos)*10;
                }
              }
            }

            if(pont_g<0)
            {
              pont_g=0;
            }

            printf("\nTentativas disponiveis: %d", chances);
            printf("\nPontuacao: %d\n", pont_g);

            marc=2;

			  }
				inicio+=7;
				value_max_i+=7;

      }
	    break;


case 'A': // igual aos anteriores, com mudança nos mesmos valores do caso 'I'
			for (int i= 0; i<5; i++)
			{
				acertos = 0;
				marc=1;

        while(acertos !=9 && chances!=0)
				{
					acertos = 0;
          printf("Sequencia #%d:\n", i+1);
					for (int i= inicio; i<value_max_a; i++)
					{
						printf("%d ", valores_seq[i] );
						//fflush(stdout);
					}
					//sleep(10);
					//system("clear");
					printf("\n");
					for (int i= inicio; i<value_max_a; i++)
					{
						scanf("%d", &valores_resp[i] );
					}
					for (int i= inicio; i<value_max_a; i++)
					{
						if(valores_resp[i]==valores_seq[i])
						{
							acertos++;
						}
					}
					if(acertos == 9)
					{
              printf("Correto!");

              if(marc==1)
              {
                pont_g += acertos*10;
              }
					}
						else
						{
							printf("Incorreto!");
							chances--;
              if(marc==1)
              {
                pont_max=acertos*10;
                pont_g+=pont_max;
              }
              else
              {
                if(pont_max!=0)
                {
                  pont_g -= (9-acertos)*10;
                }
              }
            }

            if(pont_g<0)
            {
              pont_g=0;
            }

            printf("\nTentativas disponiveis: %d", chances);
            printf("\nPontuacao: %d\n", pont_g);

            marc=2;

			  }
				inicio+=9;
				value_max_a+=9;

      }

			break;

			default:
				return 0; //se nao digitar nenhum valor valido para nivel, encerra o jogo
    }

    if(chances == 0) //quando acabar as chances
			{
				printf("Nao ha mais tentativas disponiveis... Tente novamente!\n");//imprime que nao ha mais tentativas
      }
      else{
        printf("Otima memoria! Parabens!!!\n"); // se o usuario terminar sem acabar com a chances ele ganha
      }

    return 0;
  }
