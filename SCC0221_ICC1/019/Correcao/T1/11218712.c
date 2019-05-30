#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main(void){
    char dificuldade;
      
    int semente,acerto=0,sequencia=1,tentativa=3,valores=0,fases=0,vitorias=0,ponto=0,pontoMAX=0;
    //int tempo;
//escolha da aleatoriedade e da dificuldade.     
    scanf("%d %c",&semente,&dificuldade);

//inplementação da aleatoriedade.  
    srand(semente);

//início do jogo a partir da escolha de dificuldade.    
    if(dificuldade == 'F'){
      //quantidade de valores à apresentar.  
        valores = 5;
        fases = 3;
        //tempo = 5;
    }
    if(dificuldade == 'I'){
        //valores para Intermediario.
        valores = 7;
        fases = 4;
        //tempo = 7;
    }
    if(dificuldade == 'A'){
        //valores para Avançado.
        valores = 9;
        fases = 5;
        //tempo = 10;
    }    
    
    int N[valores],V[valores];

      

      //loop de sequências.
       for(int j=0;j<fases;j++){
           printf("Sequencia #%d:\n",sequencia);               
           int somador=0;
           pontoMAX = 0;
           
                //impressão e atribuição de valores. 
                for(int i=0;i<valores;i++){
                    V[i]=rand()%10;
                    printf("%d ",V[i]);                    
                    }
                /*apresenta os numeros por 5 segundos e depois os apaga.
                    sleep(tempo);
                    system("clear");*/
            
                //usuário digita os valores.
                for(int t=0;t<valores;t++){
                    scanf("%d ",&N[t]);
                    }
                printf("\n");

                //verifica se cada valor escrito corresponde ao imprimido.
                for(int x=0;x<valores;x++){
                    if(V[x] == N[x]){
                        somador = somador + 1;
                        }
                    }
                //verifica se todos os valores sao iguais.         
                if (somador == valores){
                        //somando pontos a partir da quantidade de valores acertados.
                        pontoMAX = 10*somador;
                        ponto += pontoMAX;
                        printf("Correto!\nTentativas disponiveis: %d\nPontuacao: %d\n",tentativa,ponto);
                        vitorias = vitorias + 1;
                        sequencia++;                        
                }else{
                    //somando pontos a partir da quantidade de valores acertados.
                    pontoMAX = 10*somador;
                    ponto += pontoMAX;
            
                    //na primeira jogada da primeira sequencia não retira-se pontos.
                    if(tentativa == 3){
                        ponto=ponto;
                        }else{
                            if(ponto<0){
                               ponto = 0; 
                                }
                            }
                    tentativa = tentativa - 1;
                    printf("Incorreto!\nTentativas disponiveis: %d\nPontuacao: %d\n",tentativa,ponto);

                    // loop que verifica se responde corretamente em relação as tentativas restantes.    
                    while(tentativa>0 && acerto == 0){
                          int somador=0;
                          acerto = 0;
                          printf("Sequencia #%d:\n",sequencia);

                            //impressão dos valores novamente. 
                            for(int i=0;i<valores;i++){                               
                                printf("%d ",V[i]);                    
                                }
                            /*apresenta os numeros por 5 segundos e depois os apaga.
                                sleep(5);
                                system("clear");*/
                        
                            //usuário digita os valores novamente.
                            for(int t=0;t<valores;t++){
                                scanf("%d ",&N[t]);
                                }
                            printf("\n");

                            //verifica se cada valor escrito corresponde ao imprimido.
                            for(int x=0;x<valores;x++){
                                if(V[x] == N[x]){
                                    somador = somador + 1;
                                    }

                                }
                            //verifica se todos os valores sao iguais.
                            if (somador == valores){                               
                                printf("Correto!\nTentativas disponiveis: %d\nPontuacao: %d\n",tentativa,ponto);
                                vitorias = vitorias + 1;
                                sequencia++;
                                //tem a função de parar o looping.
                                acerto++;
                            }else{
                                if(pontoMAX < somador){
                                    ponto = ponto;
                                }else{
                                ponto -= 10*(valores - somador);
                                }
                                if(ponto<0){
                                    ponto = 0;
                                }
                                tentativa = tentativa - 1;
                                printf("Incorreto!\nTentativas disponiveis: %d\nPontuacao: %d\n",tentativa,ponto);                                   
                                }
                        }
                    // para que o While possa ser acessado novamente.    
                    acerto = 0;    
                    }
                //finalização do jogo.        
                if(tentativa == 0){
                        printf("Nao ha mais tentativas disponiveis... Tente novamente!\n");
                        return 0; 
                    }
                if(vitorias == fases){
                        printf("Otima memoria! Parabens!!!\n");
                        return 0;
                    }   
                
            
        
       }   
    return 0;
}