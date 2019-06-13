
#include <stdio.h>
#include <string.h>

#define ROW_BOW 100
#define COL_BOW 212

char rowBow[ROW_BOW][100];
char colBow[COL_BOW][100];
int bow[ROW_BOW][COL_BOW];
int tamRow, tamCol;
char *negativos[12] = {"detestei", "odiei", "ruim", "pessimo", "terrivel", "raiva", "odio", "pessima", "lento", "lenta", "fragil", "desisti"};
char *positivos[12] = {"bom", "maravilhoso", "otimo", "sensacional", "excelente", "adorei", "gostei", "amei", "eficiente", "boa", "maravilhosa", "otima"};
char *adv[3] = {"nao", "jamais", "nunca"};
int pos[ROW_BOW], neg[ROW_BOW], total[ROW_BOW];

int getRow(char *x){
  for (int i = 0; i < tamRow; i++)
    if (!strcmp(x, rowBow[i])) return i;
  strcpy(rowBow[tamRow], x);
  return tamRow++;
}

int getCol(char *x){
  for (int i = 0; i < tamCol; i++)
    if (!strcmp(x, colBow[i])) return i;
  strcpy(colBow[tamCol], x);
  return tamCol++;
}

int find(char *r, char *c){
  int row = getRow(r), save = tamRow;
  if (tamRow != save){
    tamRow = save;
    return 0;
  }
  int col = getCol(c);
  save = tamCol;
  if (tamCol != save){
    tamCol = save;
    return 0;
  }
  return bow[row][col];
}

int findPosNeg(char *x, int p){
  for (int i = 0; i < 12; i++){
    if (p && !strcmp(x, positivos[i])) return i;
    else if (!p && !strcmp(x, negativos[i])) return i;
  }
  return -1;
}

double findPerc(char *p, int n){
  int save = tamRow;
  
  int row = getRow(p);
  if (tamRow != save){
    tamRow = save;
    return 0.0;
  }

  return 100.0 * (double)(n ? pos[row] : neg[row]) / (double)(total[row]);
}

int main ()
{
  int n_sent, n_perg;
  char produto[100], aux[50];
  
  tamRow = 0;
  tamCol = 0;

  scanf ("%d %d", &n_sent, &n_perg);
  
  for (int i = 0; i < ROW_BOW; i++){
    for (int j = 0; j < COL_BOW; j++)
      bow[i][j] = 0;
    pos[i] = neg[i] = total[i] = 0;
  }

  while (n_sent--){
    produto[0] = '\0';
    while (scanf ("%s", aux) && strcmp(aux, ";")){
      strcat(produto, aux);
      strcat(produto, " ");
    }
    produto[strlen(produto)-1] = '\0';
    
    int row = getRow(produto);
    int invert = 0, lastAdv = -1, change = 0, k = 0;
    while (scanf ("%s", aux) && strcmp(aux, "Ø")){
      if (!change && findPosNeg(aux, 0) != -1){
	neg[row]++;
	change = 1;
	if (lastAdv != -1 && k - lastAdv <= 3) invert = 1;
      }
      else if (!change && findPosNeg(aux, 1) != -1){
	pos[row]++;
	change = 2;
	if (lastAdv != -1 && k - lastAdv <= 3) invert = 1;
      }
      else if (!strcmp(aux, adv[0]) || !strcmp(aux, adv[1]) || !strcmp(aux, adv[2]))
	lastAdv = k;
      bow[row][getCol(aux)]++;
      k++;
    }
    if (invert && change == 1){ 
      neg[row]--; pos[row]++;
    }
    else if (invert && change == 2){ 
      neg[row]++; pos[row]--;
    }
    total[row]++;
  }

  while (n_perg--){
    char pergunta[50], palavra[50], lixo[10];
    scanf ("%s %s %s %[^\r]", pergunta, palavra, lixo, produto);
    if (!strcmp(pergunta, "palavra")) printf("%d\n", find(produto, palavra));
    else{
      if (!strcmp(palavra, "negativos")) printf("%.1lf%%\n", findPerc(produto, 0));
      else printf("%.1lf%%\n", findPerc(produto, 1));
    }
  }
  
  return 0;
}
