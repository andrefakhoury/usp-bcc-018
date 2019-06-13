# include <stdio.h>
# include <stdlib.h>
# include <string.h>

char *alocapalavra (int tamanho); // Aloca vetor de char.
char *realocapalavra (int tamanho, char *palavra); // Realoca vetor de char.
char **alocafrase (int tamanho); // Aloca vetor de *char.
char **realocafrase (int tamanho, char **frase); // Realoca vetor de *char.
char ***alocatexto (int tamanho); // Aloca vetor de **char.

/* Obs: Não utilizei a técnica do BoW (eu acho). Não entendi e achei mais simples como eu fiz. Um texto é feito de frases
 que é feito de palavras que é feito de letras. */

int main () {
   char ***texto = NULL, ***perguntas = NULL; // Inicaliza os ponteiros.
   short int *quantos, nfrases, nperguntas, cond, quant, posi, neg, polaridade; // Short gasta menos memoria.
   scanf ("%hi %hi", &nfrases, &nperguntas);
   quantos = (short int *) malloc (sizeof (short int) * nfrases); // Guarda quantas palavras na frase, p/ usar no loop e free.
   if (quantos == NULL) {
      printf ("Faltou memoria\n");
      exit (1);
   }
   texto = alocatexto (nfrases); // Aloca as frases do texto, com exatamente nfrases.
   for (int i = 0; i < nfrases; i++) {
      cond = quantos[i] = 0;
      texto[i] = alocafrase (25); // Aloca as palavras das frases, inicialmente 25 palavras.
      for (int j = 0; j < 25; j++) 
         texto[i][j] = alocapalavra (20); // Aloca as letras das palavras, inicialmente 20 espaços.
      for (int j = 0; cond != 1; j++) {
         scanf ("%s", texto[i][j]); // Lê cada palavra separadamente em um vetor.
         if (strcmp(texto[i][j], "Ø") == 0) // Se a palavra no vetor for Ø, começa outra frase. (No meu computador Ø é O)
            cond = 1;
         quantos[i]++;
         texto[i][j] = realocapalavra (strlen (texto[i][j]) + 1, texto[i][j]); // Libera memoria não usada.
      }
      texto[i] = realocafrase (quantos[i], texto[i]); // Libera memoria não usada.
   }
   perguntas = alocatexto (nperguntas); // Aloca espaço para todas as perguntas.
   for (int i = 0; i < nperguntas; i++) { 
      perguntas[i] = alocafrase (5); // Sempre são cinco palavras na pergunta.
      for (int j = 0; j < 5; j++) {
         perguntas[i][j] = alocapalavra (20); // Aloca as letras.
         scanf ("%s", perguntas[i][j]);
         perguntas[i][j] = realocapalavra (strlen (perguntas[i][j]) + 1, perguntas[i][j]); // Libera memoria não usada.
      }
   }
   for (int i = 0; i < nperguntas; i++) { // Loop principal.
      if (strcmp (perguntas[i][0], "quantos") == 0) { // Pergunta de positivos e negativos.
         posi = neg = quant = polaridade = 0;
         for (int j = 0; j < nfrases; j++) {
            if ((strcmp (perguntas[i][3], texto[j][0]) == 0) && (strcmp (perguntas[i][4], texto[j][1]) == 0)) { 
            // Procura nome e marca iguais.
               quant++;
               for (int k = 0; k < quantos[j]; k++) { // Roda os vetores procurando as palavras chave.
                  polaridade--; // Calcula a distância da polaridade.
                  if (strcmp (texto[j][k], "nao") == 0 || strcmp (texto[j][k], "jamais") == 0
                  || strcmp (texto[j][k], "nunca") == 0) {
                     polaridade = 4;      
                  }
                  if (strcmp (texto[j][k], "bom") == 0 || strcmp (texto[j][k], "maravilho") == 0
                  || strcmp (texto[j][k], "otimo") == 0 || strcmp (texto[j][k], "sensacional") == 0 
                  || strcmp (texto[j][k], "excelente") == 0 || strcmp (texto[j][k], "adorei") == 0 
                  || strcmp (texto[j][k], "gostei") == 0 || strcmp (texto[j][k], "amei") == 0 
                  || strcmp (texto[j][k], "eficiente") == 0 || strcmp (texto[j][k], "boa") == 0 
                  || strcmp (texto[j][k], "maravilhosa") == 0 || strcmp (texto[j][k], "otima") == 0) {
                  if (polaridade <= 0) // Se a polaridade estiver longe ou não houver.
                     posi++; // Se achou faz a contangem e sai do loop.
                  else
                     neg++; // Se tiver polaridade perto.
                  break;
                  }
                  if (strcmp (texto[j][k], "detestei") == 0 || strcmp (texto[j][k], "odiei") == 0
                  || strcmp (texto[j][k], "ruim") == 0 || strcmp (texto[j][k], "pessimo") == 0
                  || strcmp (texto[j][k], "terrivel") == 0 || strcmp (texto[j][k], "raiva") == 0
                  || strcmp (texto[j][k], "odio") == 0 || strcmp (texto[j][k], "pessima") == 0
                  || strcmp (texto[j][k], "lento") == 0 || strcmp (texto[j][k], "lenta") == 0
                  || strcmp (texto[j][k], "fragil") == 0 || strcmp (texto[j][k], "desisti") == 0) {
                  if (polaridade <= 0) // Idem os de cima.
                     neg++; 
                  else
                     posi++;
                  break;
                  }
               }
            }
         }
         if (strcmp (perguntas[i][1], "positivos") == 0) // Se queria postivos.
            printf ("%.1f%%\n", (float)((float)posi / quant) * 100);
         else if (strcmp (perguntas[i][1], "negativos") == 0) // Se queria negativos.
            printf ("%.1f%%\n", (float)((float)neg / quant) * 100);
         else 
            printf ("Pergunta invalida\n"); // Se não queria nenhum dos dois.
      }
      else if (strcmp (perguntas[i][0], "palavra") == 0) { // Se a pergunta for quantas palavras.
         quant = 0;
         for (int j = 0; j < nfrases; j++) { 
            if (strcmp (perguntas[i][3], texto[j][0]) == 0 && strcmp (perguntas[i][4], texto[j][1]) == 0) { 
            // Procura nome e marca iguais.
               for (int k = 0; k < quantos[j]; k++) { // Roda os vetores procurando a palavra pedida.
                  if (strcmp (texto[j][k], perguntas[i][1]) == 0)
                     quant++;
               }
            }
         }
      printf ("%d\n", quant);
      }
      else 
        printf ("Pergunta invalida\n"); // Se a pergunta está errada.
   }
   for (int i = 0; i < nfrases; i++) { // Liberando todas as alocações. <- Começa aqui.
      for (int j = 0; j < quantos[i]; j++)             
         free (texto[i][j]);                              
      free (texto[i]);                                 
   }                                                   
   free (texto);                                       
   for (int i = 0; i < nperguntas; i++) {
      for (int j = 0; j < 5; j++)
         free (perguntas[i][j]);
      free (perguntas[i]);
   }
   free (perguntas);
   free (quantos);  // <- Termina aqui.
   return 0;
}
char *alocapalavra (int tamanho) { // Alocar vetor de char.
   char *palavra = NULL;
   palavra = (char *) malloc (sizeof (char) * tamanho);
   if (palavra == NULL) {
      printf ("Faltou memoria\n");
      exit (1);
   }
   return palavra;
}
char *realocapalavra (int tamanho, char *palavra) { // Realocar vetor de char.
   palavra = (char *) realloc (palavra, sizeof (char) * tamanho);
   if (palavra == NULL) {
      printf ("Faltou memoria\n");
      exit (1);
   }
   return palavra;
}
char **alocafrase (int tamanho) { // Alocar matriz de char.
   char **frase = NULL;
   frase = (char **) malloc (sizeof (char *) * tamanho);
   if (frase == NULL) {
      printf ("Faltou memoria\n");
      exit (1);
   }
   return frase;
}
char **realocafrase (int tamanho, char **frase) { // Realocar matriz de char.
   frase = (char **) realloc (frase, sizeof (char*) * tamanho);
    if (frase == NULL) {
      printf ("Faltou memoria\n");
      exit (1);
   }
   return frase;
}
char ***alocatexto (int tamanho) { // Alocar matriz de três dimensões de char.
   char ***texto = NULL;
   texto = (char ***) malloc (sizeof (char **) * tamanho);
   if (texto == NULL) {
      printf ("Faltou memoria\n");
      exit (1);
   }
   return texto;
}