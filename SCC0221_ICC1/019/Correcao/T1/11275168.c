#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void game(int seed, int ndv, int nds, int tempo) { 
   int cont, maxima, total = 0, erro, seq = 1, valor[9], resp[9], flag = 1, tentativas = 3; 
    srand(seed);    // Atribui a semente a srand
    while (tentativas > 0 && seq < nds + 1){ // Enquanto ainda restarem tentativas e sequências, continue o jogo
      erro = 0; // Erro 0 significa que ainda não errei a sequência
      cont = ndv; // Contador inicial valendo 'ndv' (número de valores)
      // printf("\e[H\e[2J");  Apaga toda a tela
      printf("Sequencia #%d:\n", seq); // Sequência 'seq' na tela
      
      for (int i = 0; i < ndv; i++){
        valor[i] = (rand() % 10);    // Esse loop imprime 'ndv' valores, sendo que cada um é armazenado como um elemento do vetor 'valor'
        printf("%d ", valor[i]);
      }
      
      printf("\n");
      // sleep(tempo); Congela o programa por 'tempo' segundos  
      // Apaga a linha anterior, no caso a sequência impressa
      // printf("\033[A\33[2K"); 
      
      for (int j = 0; j < ndv; j++){
        /* Esse loop lê os valores digitados pelo usuário, em ordem comparada com a ordem dos 
        valores impressos inicialmente. Caso algum valor digitado seja diferente do valor correspondente
        na sequência, do contador inicial é descontada uma unidade e a flag indica que houve pelo menos uma resposta errada. */
        scanf("%d", &resp[j]);
        if (resp[j] != valor[j]){    
          flag = 0;                         
          cont -= 1;
        }
      }
      if (flag == 0){ 
      /* Se houve erro, a pontuação máxima da sequência recebe o nº de acertos * 10 e 
        à pontuação total soma-se essa pontuação máxima*/
      maxima = cont * 10; 
      total += maxima;      
      }
        // Enquanto errar a sequência e ainda houverem tentativas disponíveis
      while (flag == 0 && tentativas > 0){
        erro = 1; // Registra que houve alguma resposta errada e, portanto, não há mais como alcançar a pontuação de 50 
        flag = 1;   /* A flag recebe 1 pois a segunda tentativa dessa sequencia ainda não foi mostrada,
        então não tem como o usuário já ter errado */
        tentativas -= 1; // Como errou, desconta-se uma unidade das tentativas
        printf("Incorreto!\n");
        printf("Tentativas disponiveis: %d\n", tentativas); // Mostra-se que houve erro, o numero de tentativas e a pontuação total
        printf("Pontuacao: %d\n", total);
        // sleep(2); Congela o programa para mostrar as informações por 2 segundos
        // printf("\e[H\e[2J"); Apaga toda a tela 
        
        //Se ainda há tentativas disponíveis
        if (tentativas > 0){
          printf("Sequencia #%d:\n", seq);
          for (int i = 0; i < ndv; i++)
            printf("%d ", valor[i]);            // Mostra novamente a mesma sequência

          printf("\n");
          // sleep(tempo); Congela o programa por 'tempo' segundos 
          // printf("\033[A\33[2K"); Apaga a linha anterior, no caso a sequência impressa

          for (int j = 0; j < ndv; j++){
            scanf("%d", &resp[j]);
            /* Aqui lemos os valores novamente. Se algum valor foi resposta errada,
                a flag recebe 0, pois houve erro, e descontam-se 10 pontos da pontuação máxima
                dessa sequência. Enquanto essa máxima não for negativa, descontam-se os mesmos 10
                da pontuação total. Assim, não temos pontuação negativa no jogo, pois a mínima possível é 0. */
            if (resp[j] != valor[j]){
              flag = 0;                 
              maxima -= 10;
                if (maxima >= 0)
                  total -= 10;
            }
          }
        }
      }
        //
      if (flag == 1 && tentativas > 0){
        /* Se acertei a sequência de primeira, soma-se à pontuação total a pontuação ideal, de ndv * 10. 
        Caso contrário, a pontuação total é aquela correspondente ao caso de resposta errada (com pontuação máxima da sequência) */
        if (erro == 0)  
          total += cont * 10; 
        printf("Correto!\n");   // Indica resposta correta
        printf("Tentativas disponiveis: %d\n", tentativas); 
        printf("Pontuacao: %d\n", total);
        // sleep(2); Congela o programa para mostrar as informações por 2 segundos
        seq += 1;   // Avança para a próxima sequência
      }    
    }
      if (tentativas == 0)  // Se o programa terminou porque não há mais tentativas disponíveis
        printf("Nao ha mais tentativas disponiveis... Tente novamente!");
      else {    // Se terminou porque todas as sequências foram respondidas corretamente
        // printf("\e[H\e[2J"); Apaga toda a tela
        printf("Otima memoria! Parabens!!!");
      }
    }


int main(void) {
  int seed;
  char dif;
    scanf("%d %c", &seed, &dif); // Lê a semente e a dificuldade

    if (dif == 'F')
        game(seed, 5, 3, 5);
    else if (dif == 'I')
        game(seed, 7, 4, 7);
    else if (dif == 'A')
        game(seed, 9, 5, 10);
    
    return 0;
}