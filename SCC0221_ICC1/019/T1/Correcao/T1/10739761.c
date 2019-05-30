#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main()
{
    int i,erro = 0,n_seq=1,usuario_errou=0,acerto=0,vidas=3,pontuacao_total,valor_novo;
    int valor_maximo=50;
    char C;

    int sequencia[9];

        int semente;
        // escolhendo a semente conseguiremos fazer gerar a sequencia aletoria
       // printf("Escolha a sua semente e sua classe de jogador\n"); 
        scanf("%d %c", &semente,&C);


        /*Todo comentario feito com relacao a parte F (nivel facil) tem relacao analoga com as demais
        partes do codigo (I e A), portanto comentarei apenas o item F.*/

        if( C=='F') {
            valor_maximo=50;
            pontuacao_total = 0;
            srand(semente);

            // Como coloquei que n_seq = 1, como para o nivel facil precisamos
            // de 3 sequencias, coloco a codicao while ate, pois 4 - 1 = 3
            while(n_seq != 4 ){

                printf("Sequencia #%d:\n",n_seq);

                // Faco os passos abaixo para gerar a sequencia aleatoria baseada na semente escohida pelo usuario.

                for (i = 0; i < 5; i++){
                    if( usuario_errou == 0){
                        sequencia[i] = rand()%10;
                        printf("%d ", sequencia[i]);

                // caso o usuario erre, a mesma sequencia devera aparecer, portanto nao gero nova sequencia, apeas imprimo a anterior

                    }else {
                        for(i = 0;i<5;i++){
                            printf("%d ",sequencia[i]);
                        }
                    }
                }

                printf("\n");
                // apos 5 segundos a sequencia e apagada
                //sleep(5);
                //system("clear");

                // armazeno a sequencia digitada pelo usuario em um vetor de i posicoes
                //faco isso para poder comparar a sequencia digitada com a impressa

                int usuario[5];
                for (i = 0; i < 5; i++){
                    scanf("%d",&usuario[i]);
                }

                /*faco a comparacao entre a sequencia digitada e a impressa utilizando uma "flag"
                para dividir os casos possiveis (usuario_errou), se usuario_errou for igual a 0,
                 significa que o usuario nao errou, ja se for iual a 1 significa que o usuario errou 
                */

                for (i= 0; i<5;i++){
                    if (sequencia[i] == usuario[i]){
                        acerto++;
                    } else erro++;
                    if (acerto == 5){
                        usuario_errou = 0;
                       pontuacao_total = pontuacao_total + valor_maximo;
                        valor_maximo = 50;
                        n_seq++;
                    } else {
                            usuario_errou = 1;
                        }
                    }
                
            /*Se usuario acertou a sequencia o numero de acertos dele deve ser igual a 5, nesse caso,
            e entao uma nova sequencia deve aparecer para que ele continue o jogo, caso ele erre, seus 
            acertos serao menores que 5 e a mesma sequencia deve aparecer para que ele tente denovo*/

                if (acerto== 5){
                    printf("Correto!\n");
                } else {
                    printf("Incorreto!\n");
                }

            // Cada vez que o usuario erra, ele perde uma vida e sua pontuacao diminui.

                if (usuario_errou == 1){
                    vidas--;
                    valor_novo = valor_maximo - 10*erro;
                    valor_maximo = valor_novo;
                } 

                if (vidas > 0){
                    printf("Tentativas disponiveis: %d\n",vidas);
                } else {
                    printf("Tentativas disponiveis: %d\n",vidas);
                    printf("Pontuacao: %d\n",pontuacao_total + valor_maximo);
                    printf("Nao ha mais tentativas disponiveis... Tente novamente!\n");
                    break;
                }


                if (acerto == 5 && pontuacao_total >0){
                printf("Pontuacao: %d\n",pontuacao_total);
                } else{
                    if (pontuacao_total + valor_maximo >0){
                     printf("Pontuacao: %d\n",pontuacao_total + valor_maximo);
                    } else printf("Pontuacao: 0\n");
                }
                 acerto = 0;

                erro =0;
            }
             if (vidas > 0){
                printf("Otima memoria! Parabens!!!\n");
            }


    }


    if( C=='I') {
            valor_maximo=70;
            pontuacao_total = 0;
            srand(semente);

            while(n_seq != 5 ){

                printf("Sequencia #%d:\n",n_seq);

                for (i = 0; i < 7; i++){
                    if( usuario_errou == 0){
                        sequencia[i] = rand()%10;
                        printf("%d ", sequencia[i]);

                    }else {
                        for(i = 0;i<7;i++){
                            printf("%d ",sequencia[i]);
                        }
                    }
                }

                printf("\n");
                //sleep(7);
                //system("clear");

                int usuario[7];
                for (i = 0; i < 7; i++){
                    scanf("%d",&usuario[i]);
                }
                for (i= 0; i<7;i++){
                    if (sequencia[i] == usuario[i]){
                        acerto++;
                    } else erro++;
                    if (acerto == 7){
                        usuario_errou = 0;
                       pontuacao_total = pontuacao_total + valor_maximo;
                        valor_maximo = 70;
                        n_seq++;
                    } else {
                            usuario_errou = 1;
                        }
                    }
                
                if (acerto== 7){
                    printf("Correto!\n");
                } else {
                    printf("Incorreto!\n");
                }


                if (usuario_errou == 1){
                    vidas--;
                    valor_novo = valor_maximo - 10*erro;
                    valor_maximo = valor_novo;
                } 

                if (vidas > 0){
                    printf("Tentativas disponiveis: %d\n",vidas);
                } else {
                    printf("Tentativas disponiveis: %d\n",vidas);
                    if (pontuacao_total + valor_maximo >0){
                        printf("Pontuacao: %d\n",pontuacao_total);
                    } else printf("Pontuacao: 0\n");
                    printf("Nao ha mais tentativas disponiveis... Tente novamente!\n");
                    break;
                }

                if (acerto == 7 && pontuacao_total >0){
                printf("Pontuacao: %d\n",pontuacao_total);
                } else{
                    if (pontuacao_total + valor_maximo >0){
                     printf("Pontuacao: %d\n",pontuacao_total + valor_maximo);
                    } else printf("Pontuacao: 0\n");
                }
                    
                 acerto = 0;


                erro =0;
            }
             if (vidas > 0){
                printf("Otima memoria! Parabens!!!\n");
            }


    }


    if( C=='A') {
            valor_maximo=90;
            pontuacao_total = 0;
            srand(semente);

            while(n_seq != 6 ){

                printf("Sequencia #%d:\n",n_seq);

                for (i = 0; i < 9; i++){
                    if( usuario_errou == 0){
                        sequencia[i] = rand()%10;
                        printf("%d ", sequencia[i]);

                    }else {
                        for(i = 0;i<9;i++){
                            printf("%d ",sequencia[i]);
                        }
                    }
                }

                printf("\n");
                //sleep(9);
                //system("clear");

                int usuario[9];
                for (i = 0; i < 9; i++){
                    scanf("%d",&usuario[i]);
                }
                for (i= 0; i<9;i++){
                    if (sequencia[i] == usuario[i]){
                        acerto++;
                    } else erro++;
                    if (acerto == 9){
                        usuario_errou = 0;
                       pontuacao_total = pontuacao_total + valor_maximo;
                        valor_maximo = 90;
                        n_seq++;
                    } else {
                            usuario_errou = 1;
                        }
                    }
                
                if (acerto== 9){
                    printf("Correto!\n");
                } else {
                    printf("Incorreto!\n");
                }

                if (usuario_errou == 1){
                    vidas--;
                    valor_novo = valor_maximo - 10*erro;
                    valor_maximo = valor_novo;
                } 

                if (vidas > 0){
                    printf("Tentativas disponiveis: %d\n",vidas);
                } else {
                    printf("Tentativas disponiveis: %d\n",vidas);
                    printf("Pontuacao: %d\n",pontuacao_total + valor_maximo);
                    printf("Nao ha mais tentativas disponiveis... Tente novamente!\n");
                    break;
                }


                if (acerto == 9 && pontuacao_total >0){
                printf("Pontuacao: %d\n",pontuacao_total);
                } else{
                    if (pontuacao_total + valor_maximo >0){
                     printf("Pontuacao: %d\n",pontuacao_total + valor_maximo);
                    } else printf("Pontuacao: 0\n");
                }
                
                 acerto = 0;

                erro =0;
            }
             if (vidas > 0){
                printf("Otima memoria! Parabens!!!\n");
            }


    }
      
 return 0;
}
