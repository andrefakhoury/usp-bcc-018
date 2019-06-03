#include <stdio.h>
#include <stdlib.h>

int main(void){
  
  int semente,i,vetorF[10],digitadoF[10],num,pont,pontuacao1=0,pontuacaomax1,pontuacao2=0,pontuacaomax2,pontuacao3=0,pontuacaomax3,pontuacaototal,pontuacao4=0,pontuacaomax4,pontuacao5=0,pontuacaomax5,tentativa=3;
  char nivel;
  scanf("%d %c",&semente,&nivel);
  srand(semente);
  
  if(nivel=='F'){//nivel facil
    num=5;
    pont=50;
  }
  if(nivel=='I'){//nivel intermediario
    num=7;
    pont=70;
  }
  if(nivel=='A'){
    num=9;
    pont=90;
  }

    printf("Sequencia #1:\n");
    for(i=0;i<num;i++){//gerando a sequencia #1
      vetorF[i]=rand()%10;
      printf("%d ",vetorF[i]);
    }//ESPERA DE: 5s PARA F;7s PARA I;9s PARA A;
    printf("\n");
    for(i=0;i<num;i++){//armazenando os valores digitados da sequencia #1
       scanf("%d",&digitadoF[i]);
    }
    for(i=0;i<num;i++){//comparando os valores gerados com os digitados da sequencia #1
      if(vetorF[i]==digitadoF[i]){
        pontuacao1+=10;
        }
      }
      if(pontuacao1==pont){//se acertar todas
        printf("Correto!\nTentativas disponiveis: %d\n",tentativa);
        printf("Pontuacao: %d\n",pontuacao1);
        printf("Sequencia #2:\n");
        for(i=0;i<num;i++){//gerando a sequencia #2
        vetorF[i]=rand()%10;
        printf("%d ",vetorF[i]);
          }
        printf("\n");
        }else
      if(pontuacao1!=pont){//se errar pelo menos uma
        tentativa-=1;
        printf("Incorreto!\nTentativas disponiveis: %d\n",tentativa);
        printf("Pontuacao: %d\n",pontuacao1);
        pontuacaomax1=pontuacao1;
        printf("Sequencia #1:\n");
        for(i=0;i<num;i++){//reescrevendo a sequencia #1
          printf("%d ",vetorF[i]);
        }//ESPERA DE: 5s PARA F;7s PARA I;9s PARA A;
        printf("\n");
        for(i=0;i<num;i++){
          scanf("%d",&digitadoF[i]);        
        }
        for(i=0;i<num;i++){//comparando os valores reescritos com os digitados da sequencia #1
        if(vetorF[i]!=digitadoF[i]){
        pontuacao1-=10;
          }
        }
        if(pontuacao1==pontuacaomax1){//se acertar todas
        printf("Correto!\nTentativas disponiveis: %d\n",tentativa);
        printf("Pontuacao: %d\n",pontuacao1);
        printf("Sequencia #2:\n");
        for(i=0;i<num;i++){//gerando a sequencia #2
        vetorF[i]=rand()%10;
        printf("%d ",vetorF[i]);
          }
          printf("\n");
        }else
      if(pontuacao1!=pontuacaomax1){//se errar pelo menos uma
        if(pontuacao1<0){
          pontuacao1=0;
        }
        tentativa-=1;
        printf("Incorreto!\nTentativas disponiveis: %d\n",tentativa);
        printf("Pontuacao: %d\n",pontuacao1);
        pontuacaomax1=pontuacao1;
        printf("Sequencia #1:\n");
        for(i=0;i<num;i++){//reescrevendo a sequencia #1
        printf("%d ",vetorF[i]);
          }//ESPERA DE: 5s PARA F;7s PARA I;9s PARA A;
        printf("\n");
        for(i=0;i<num;i++){
          scanf("%d",&digitadoF[i]);        
        }
        for(i=0;i<num;i++){//comparando os valores reescritos com os digitados da sequencia #1
        if(vetorF[i]!=digitadoF[i]){
        pontuacao1-=10;
          }
        }
        if(pontuacao1==pontuacaomax1){//se acertar todas
        printf("Correto!\nTentativas disponiveis: %d\n",tentativa);
        printf("Pontuacao: %d\n",pontuacao1);
        printf("Sequencia #2:\n");
        for(i=0;i<num;i++){//gerando a sequencia #1
        vetorF[i]=rand()%10;
        printf("%d ",vetorF[i]);
          }//ESPERA DE: 5s PARA F;7s PARA I;9s PARA A;
        printf("\n");  
        }else
      if(pontuacao1!=pontuacaomax1){//se errar pelo menos uma
        if(pontuacao1<0){
          pontuacao1=0;
        }
        tentativa-=1;
        printf("Incorreto!\nTentativas disponiveis: %d\n",tentativa);
        printf("Pontuacao: %d\n",pontuacao1);
        printf("Nao ha mais tentativas disponiveis... Tente novamente!\n");
        return 0;
        }
      }
      }
    
    
    //ESPERA DE: 5s PARA F;7s PARA I;9s PARA A;
    for(i=0;i<num;i++){
      scanf("%d",&digitadoF[i]);
    }
    for(i=0;i<num;i++){//comparando os valores gerados com os digitados da sequencia #2
      if(vetorF[i]==digitadoF[i]){
        pontuacao2+=10;
        }
      }
    pontuacaototal=pontuacao1+pont;
    if(pontuacao2+pontuacao1==pontuacaototal){//se acertar todas
        printf("Correto!\nTentativas disponiveis: %d\n",tentativa);
        pontuacao2+=pontuacao1;
        printf("Pontuacao: %d\n",pontuacao2);
        printf("Sequencia #3:\n");
        for(i=0;i<num;i++){//gerando a sequencia #3
        vetorF[i]=rand()%10;
        printf("%d ",vetorF[i]);
          }
        printf("\n");
        }else
      if(pontuacao2+pontuacao1!=pontuacaototal){//se errar pelo menos uma
        tentativa-=1;
        printf("Incorreto!\nTentativas disponiveis: %d\n",tentativa);
        pontuacaototal=pontuacao2+pontuacao1;
        printf("Pontuacao: %d\n",pontuacaototal);
        if(tentativa==0){
          printf("Nao ha mais tentativas disponiveis... Tente novamente!\n");
          return 0;
        }
        pontuacaomax2=pontuacao2+pontuacao1;
        printf("Sequencia #2:\n");
        for(i=0;i<num;i++){//reescrevendo a sequencia #2
          printf("%d ",vetorF[i]);
        }//ESPERA DE: 5s PARA F;7s PARA I;9s PARA A;
        printf("\n");
        for(i=0;i<num;i++){
          scanf("%d",&digitadoF[i]);        
        }
        for(i=0;i<num;i++){//comparando os valores reescritos com os digitados da sequencia #2
        if(vetorF[i]!=digitadoF[i]){
        pontuacaototal-=10;
          }
        }
        if(pontuacaototal==pontuacaomax2){//se acertar todas
        printf("Correto!\nTentativas disponiveis: %d\n",tentativa);
        printf("Pontuacao: %d\n",pontuacaototal);
        printf("Sequencia #3:\n");
        for(i=0;i<num;i++){//gerando a sequencia #3
        vetorF[i]=rand()%10;
        printf("%d ",vetorF[i]);
          }
          printf("\n");
        }else
      if(pontuacaototal!=pontuacaomax2){//se errar pelo menos uma
        tentativa-=1;
        printf("Incorreto!\nTentativas disponiveis: %d\n",tentativa);
        printf("Pontuacao: %d\n",pontuacaototal);
        if(tentativa==0){
          printf("Nao ha mais tentativas disponiveis... Tente novamente!\n");
          return 0;
        }
        pontuacaomax2=pontuacaototal;
        printf("Sequencia #2:\n");
        for(i=0;i<num;i++){//reescrevendo a sequencia #2
        printf("%d ",vetorF[i]);
          }//ESPERA DE: 5s PARA F;7s PARA I;9s PARA A;
        printf("\n");
        for(i=0;i<num;i++){
          scanf("%d",&digitadoF[i]);        
        }
        for(i=0;i<num;i++){//comparando os valores reescritos com os digitados da sequencia #2
        if(vetorF[i]!=digitadoF[i]){
        pontuacaototal-=10;
          }
        }
        if(pontuacaototal==pontuacaomax2){//se acertar todas
        printf("Correto!\nTentativas disponiveis: %d\n",tentativa);
        printf("Pontuacao: %d\n",pontuacaototal);
        printf("Sequencia #3:\n");
        for(i=0;i<num;i++){//gerando a sequencia #3
        vetorF[i]=rand()%10;
        printf("%d ",vetorF[i]);
          }
        printf("\n");  
        }else
      if(pontuacaototal!=pontuacaomax2){//se errar pelo menos uma
        if(pontuacaototal<0){
          pontuacaototal=0;
        }
        tentativa-=1;
        printf("Incorreto!\nTentativas disponiveis: %d\n",tentativa);
        printf("Pontuacao: %d\n",pontuacaototal);
        printf("Nao ha mais tentativas disponiveis... Tente novamente!\n");
        return 0;
        }
      }
      }
    
    //ESPERA DE: 5s PARA F;7s PARA I;9s PARA A;
    for(i=0;i<num;i++){
      scanf("%d",&digitadoF[i]);
    }
    for(i=0;i<num;i++){//comparando os valores gerados com os digitados da sequencia #3
      if(vetorF[i]==digitadoF[i]){
        pontuacao3+=10;
        }
      }
    pontuacaomax3=pontuacaototal+pont;
    pontuacaototal+=pontuacao3;
    if(pontuacaototal==pontuacaomax3){
      printf("Correto!\nTentativas disponiveis: %d\n",tentativa);
        printf("Pontuacao: %d\n",pontuacaototal);
        if(nivel=='F'){
          printf("Otima memoria! Parabens!!!\n");
          return 0;
        }
        printf("Sequencia #4:\n");
        for(i=0;i<num;i++){//gerando a sequencia #4
        vetorF[i]=rand()%10;
        printf("%d ",vetorF[i]);
          }
        printf("\n");
    }else
    if(pontuacaototal!=pontuacaomax3){
      pontuacaomax3=pontuacaototal;
      tentativa-=1;
        printf("Incorreto!\nTentativas disponiveis: %d\n",tentativa);
        printf("Pontuacao: %d\n",pontuacaomax3);
        if(tentativa==0){
          printf("Nao ha mais tentativas disponiveis... Tente novamente!\n");
          return 0;
      }
      printf("Sequencia #3:\n");
      for(i=0;i<num;i++){//reescrevendo a sequencia #3
        printf("%d ",vetorF[i]);
      }//ESPERA DE: 5s PARA F;7s PARA I;9s PARA A;
        printf("\n");
      for(i=0;i<num;i++){
          scanf("%d",&digitadoF[i]);        
        }
      for(i=0;i<num;i++){//comparando os valores reescritos com os digitados da sequencia #3
        if(vetorF[i]!=digitadoF[i]){
        pontuacaototal-=10;
          }
      }
      if(pontuacaototal==pontuacaomax3){//se acertar todas
        printf("Correto!\nTentativas disponiveis: %d\n",tentativa);
        printf("Pontuacao: %d\n",pontuacaototal);
        if(nivel=='F'){
          printf("Otima memoria! Parabens!!!\n");
          return 0;
        }
        printf("Sequencia #4:\n");
        for(i=0;i<num;i++){//gerando a sequencia #4
        vetorF[i]=rand()%10;
        printf("%d ",vetorF[i]);
          }
        printf("\n");  
        }else
      if(pontuacaototal!=pontuacaomax3){//se errar pelo menos uma
        if(pontuacaototal<0){
          pontuacaototal=0;
        }
        tentativa-=1;
        printf("Incorreto!\nTentativas disponiveis: %d\n",tentativa);
        printf("Pontuacao: %d\n",pontuacaototal);
        if(tentativa==0){
        printf("Nao ha mais tentativas disponiveis... Tente novamente!\n");
        return 0;
        }
        pontuacaomax3=pontuacaototal;
        printf("Sequencia #3:\n");
        for(i=0;i<num;i++){//reescrevendo a sequencia #3
        printf("%d ",vetorF[i]);
          }//ESPERA DE: 5s PARA F;7s PARA I;9s PARA A;
        printf("\n");
        for(i=0;i<num;i++){
          scanf("%d",&digitadoF[i]);        
        }
        for(i=0;i<num;i++){//comparando os valores reescritos com os digitados da sequencia #3
        if(vetorF[i]!=digitadoF[i]){
        pontuacaototal-=10;
          }
        }
        if(pontuacaototal==pontuacaomax3){//se acertar todas
        printf("Correto!\nTentativas disponiveis: %d\n",tentativa);
        printf("Pontuacao: %d\n",pontuacaototal);
        if(nivel=='F'){
          printf("Otima memoria! Parabens!!!\n");
          return 0;
        }
        printf("Sequencia #4:\n");
        for(i=0;i<num;i++){//gerando a sequencia #4
        vetorF[i]=rand()%10;
        printf("%d ",vetorF[i]);
          }
        printf("\n");  
        }else
      if(pontuacaototal!=pontuacaomax3){//se errar pelo menos uma
        if(pontuacaototal<0){
          pontuacaototal=0;
        }
        tentativa-=1;
        printf("Incorreto!\nTentativas disponiveis: %d\n",tentativa);
        printf("Pontuacao: %d\n",pontuacaototal);
        printf("Nao ha mais tentativas disponiveis... Tente novamente!\n");
        return 0;
        }
      }

    }


  //ESPERA DE: 7s PARA I;9s PARA A;
    for(i=0;i<num;i++){
      scanf("%d",&digitadoF[i]);
    }
    for(i=0;i<num;i++){//comparando os valores gerados com os digitados da sequencia #4
      if(vetorF[i]==digitadoF[i]){
        pontuacao4+=10;
        }
      }
    pontuacaomax4=pontuacaototal+pont;
    pontuacaototal+=pontuacao4;
    if(pontuacaototal==pontuacaomax4){
      printf("Correto!\nTentativas disponiveis: %d\n",tentativa);
        printf("Pontuacao: %d\n",pontuacaototal);
        if(nivel=='I'){
          printf("Otima memoria! Parabens!!!\n");
          return 0;
        }
        printf("Sequencia #5:\n");
        for(i=0;i<num;i++){//gerando a sequencia #5
        vetorF[i]=rand()%10;
        printf("%d ",vetorF[i]);
          }
        printf("\n");
    }else
    if(pontuacaototal!=pontuacaomax4){
      pontuacaomax4=pontuacaototal;
      if(pontuacaototal<0){
          pontuacaototal=0;
        }
      tentativa-=1;
        printf("Incorreto!\nTentativas disponiveis: %d\n",tentativa);
        printf("Pontuacao: %d\n",pontuacaomax4);
        if(tentativa==0){
          printf("Nao ha mais tentativas disponiveis... Tente novamente!\n");
          return 0;
      }
      printf("Sequencia #4:\n");
      for(i=0;i<num;i++){//reescrevendo a sequencia #4
        printf("%d ",vetorF[i]);
      }//ESPERA DE: 7s PARA I;9s PARA A;
        printf("\n");
      for(i=0;i<num;i++){
          scanf("%d",&digitadoF[i]);        
        }
      for(i=0;i<num;i++){//comparando os valores reescritos com os digitados da sequencia #4
        if(vetorF[i]!=digitadoF[i]){
        pontuacao4-=10;
          }
      }
      if(pontuacaototal+pontuacao4==pontuacaomax4){//se acertar todas
        printf("Correto!\nTentativas disponiveis: %d\n",tentativa);
        printf("Pontuacao: %d\n",pontuacaototal);
        if(nivel=='I'){
          printf("Otima memoria! Parabens!!!\n");
          return 0;
        }
        printf("Sequencia #5:\n");
        for(i=0;i<num;i++){//gerando a sequencia #5
        vetorF[i]=rand()%10;
        printf("%d ",vetorF[i]);
          }
        printf("\n");  
        }else
      if(pontuacaototal+pontuacao4!=pontuacaomax4){//se errar pelo menos uma
        if(pontuacao4<0){
          pontuacao4=0;
        }
        tentativa-=1;
        printf("Incorreto!\nTentativas disponiveis: %d\n",tentativa);
        pontuacaototal+=pontuacao4;
        printf("Pontuacao: %d\n",pontuacaototal);
        if(tentativa==0){
        printf("Nao ha mais tentativas disponiveis... Tente novamente!\n");
        return 0;
        }
        pontuacaomax4=pontuacaototal;
        printf("Sequencia #4:\n");
        for(i=0;i<num;i++){//reescrevendo a sequencia #4
        printf("%d ",vetorF[i]);
          }//ESPERA DE:7s PARA I;9s PARA A;
        printf("\n");
        for(i=0;i<num;i++){
          scanf("%d",&digitadoF[i]);        
        }
        for(i=0;i<num;i++){//comparando os valores reescritos com os digitados da sequencia #4
        if(vetorF[i]!=digitadoF[i]){
        pontuacaototal-=10;
          }
        }
        if(pontuacaototal==pontuacaomax4){//se acertar todas
        printf("Correto!\nTentativas disponiveis: %d\n",tentativa);
        printf("Pontuacao: %d\n",pontuacaototal);
        if(nivel=='I'){
          printf("Otima memoria! Parabens!!!\n");
          return 0;
        }
        printf("Sequencia #5:\n");
        for(i=0;i<num;i++){//gerando a sequencia #5
        vetorF[i]=rand()%10;
        printf("%d ",vetorF[i]);
          }
        printf("\n");  
        }else
      if(pontuacaototal!=pontuacaomax4){//se errar pelo menos uma
        if(pontuacaototal<0){
          pontuacaototal=0;
        }
        tentativa-=1;
        printf("Incorreto!\nTentativas disponiveis: %d\n",tentativa);
        printf("Pontuacao: %d\n",pontuacaototal);
        printf("Nao ha mais tentativas disponiveis... Tente novamente!\n");
        return 0;
        }
      }


//ESPERA DE: 7s PARA I;9s PARA A;
    }
    for(i=0;i<num;i++){
      scanf("%d",&digitadoF[i]);
    }
    for(i=0;i<num;i++){
      if(vetorF[i]==digitadoF[i]){
        pontuacao5+=10;
      }
    }
    pontuacaomax5=pontuacaototal+pont;
    pontuacaototal+=pontuacao5;
    if(pontuacaototal==pontuacaomax5){
      printf("Correto!\nTentativas disponiveis: %d\n",tentativa);
        printf("Pontuacao: %d\n",pontuacaototal);
        printf("Otima memoria! Parabens!!!\n");
        return 0;
    }else
    if(pontuacaototal!=pontuacaomax5){
      pontuacaomax5=pontuacaototal;
      if(pontuacaototal<0){
          pontuacaototal=0;
        }
      tentativa-=1;
        printf("Incorreto!\nTentativas disponiveis: %d\n",tentativa);
        printf("Pontuacao: %d\n",pontuacaomax5);
        if(tentativa==0){
          printf("Nao ha mais tentativas disponiveis... Tente novamente!\n");
          return 0;
      }
      printf("Sequencia #5:\n");
      for(i=0;i<num;i++){//reescrevendo a sequencia #5
        printf("%d ",vetorF[i]);
      }//ESPERA DE: 7s PARA I;9s PARA A;
        printf("\n");
      for(i=0;i<num;i++){
          scanf("%d",&digitadoF[i]);        
        }
      for(i=0;i<num;i++){//comparando os valores reescritos com os digitados da sequencia #5
        if(vetorF[i]!=digitadoF[i]){
        pontuacaototal-=10;
          }
      }
      if(pontuacaototal==pontuacaomax5){//se acertar todas
        printf("Correto!\nTentativas disponiveis: %d\n",tentativa);
        printf("Pontuacao: %d\n",pontuacaototal);
        printf("Otima memoria! Parabens!!!\n");
        return 0;
        }else
      if(pontuacaototal!=pontuacaomax5){//se errar pelo menos uma
        if(pontuacaototal<0){
          pontuacaototal=0;
        }
        tentativa-=1;
        printf("Incorreto!\nTentativas disponiveis: %d\n",tentativa);
        printf("Pontuacao: %d\n",pontuacaototal);
        if(tentativa==0){
        printf("Nao ha mais tentativas disponiveis... Tente novamente!\n");
        return 0;
        }
        pontuacaomax5=pontuacaototal;
        printf("Sequencia #5:\n");
        for(i=0;i<num;i++){//reescrevendo a sequencia #5
        printf("%d ",vetorF[i]);
          }//ESPERA DE: 7s PARA I;9s PARA A;
        printf("\n");
        for(i=0;i<num;i++){
          scanf("%d",&digitadoF[i]);        
        }
        for(i=0;i<num;i++){//comparando os valores reescritos com os digitados da sequencia #5
        if(vetorF[i]!=digitadoF[i]){
        pontuacaototal-=10;
          }
        }
        if(pontuacaototal==pontuacaomax5){//se acertar todas
        printf("Correto!\nTentativas disponiveis: %d\n",tentativa);
        printf("Pontuacao: %d\n",pontuacaototal);
        printf("Otima memoria! Parabens!!!\n");
        return 0;
        }else
      if(pontuacaototal!=pontuacaomax5){//se errar pelo menos uma
        if(pontuacaototal<0){
          pontuacaototal=0;
        }
        tentativa-=1;
        printf("Incorreto!\nTentativas disponiveis: %d\n",tentativa);
        printf("Pontuacao: %d\n",pontuacaototal);
        printf("Nao ha mais tentativas disponiveis... Tente novamente!\n");
        return 0;
        }
      }
    }
  return 0;
}