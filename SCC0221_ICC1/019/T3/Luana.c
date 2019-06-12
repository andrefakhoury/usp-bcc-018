#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

int pertence(int x,int y,int c,int media,int** matriz){

  if(((matriz[x][y]-media)<=c)&&((matriz[x][y]-media)>=-c)){
    return 0;
  }
  else{
    return 1;
  }
}

void busca(int x,int y,int c,int media, int** matriz,/*int* regioesx,int* regioesy,*/int* j,int m,int n){
  if (x < 0 || y < 0 || x >= m || y >= n) return;

  printf("%d %d\n", x, y);

  if(matriz[x][y]!=-1){
    if(pertence(x,y,c,media,matriz)==0){
      /*regioesx[*j] = x;
      regioesy[*j] = y;*/
      j++;
    }
  }
  
  matriz[x][y] = -1;

  if(((y-1)>=0) && (matriz[x][y-1]!=-1)){
    // y = y - 1;
    busca(x,y-1,c,media,matriz,/*regioesx,regioesy,*/j,m,n);
  }
  if(((x+1)<m) && (matriz[x+1][y]!=-1)){
    // x = x + 1;;
  busca(x+1,y,c,media,matriz,/*regioesx,regioesy,*/j,m,n);
  }
  if(((y+1)<n) && (matriz[x][y+1]!=-1)){
    // y = y + 1;
  busca(x,y+1,c,media,matriz,/*regioesx,regioesy,*/j,m,n);
  }
  if(((x-1)>=0) && (matriz[x-1][y]!=-1)){
    // x = x + 1;
  busca(x+1,y,c,media,matriz,/*regioesx,regioesy,*/j,m,n);
  }

}

int main(void) {
  
 int k,i,j,m,n,l=0,ignorado,media=0;
 char nome[20],string;
 
 scanf("%s", nome );
 FILE* arquivo = fopen(nome, "r");

 scanf(" %d", &k);
 
 int* x = malloc(k*(sizeof(int)));
 int* y = malloc(k*(sizeof(int)));
 int* c = malloc(k*(sizeof(int)));
  
 for(i=0;i<k;i++){
   scanf(" %d %d %d", &x[i],&y[i],&c[i]);
 }

 fscanf(arquivo," %*s");

 fscanf(arquivo,"%d",&m);
 fscanf(arquivo,"%d",&n);

 fscanf(arquivo,"%*d");

 int** matriz = malloc(m*(sizeof(int*)));
 for(i=0;i<m;i++){
   matriz[i] = malloc((n*(sizeof(int))));
 }

 for(i=0;i<m;i++){
   for(j=0;j<n;j++){
     fscanf(arquivo, "%d", &matriz[i][j]);
   }
 }

/*int* regioesx = malloc(m*n*(sizeof(int)));
for(i=0;i<m*n;i++){
regioesx[i] = 0;
}

int* regioesy = malloc(m*n*(sizeof(int)));
for(i=0;i<m*n;i++){
regioesy[i] = 0;
}*/

int* bordax = malloc(m*n*(sizeof(int)));
int* borday = malloc(m*n*(sizeof(int)));

j = 0;

for(i=0;i<k;i++){
  busca(x[i],y[i],c[i],media,matriz,/*regioesx,regioesy,*/&j,m,n);
}


/*for(i=0;i<=j;i++){
if(((regioesx[i]-1)<0)||((regioesx[i]+1)==m)||((regioesy[i]-1)<0)||((regioesy[i]+1)==n)){
bordax[l] = regioesx[i];
borday[l] = regioesy[i];
l++;
}
else if((matriz[regioesx[i]-1][regioesy[i]] == -1)||(matriz[regioesx[i]][regioesy[i]-1] == -1)||(matriz[regioesx[i]+1][regioesy[i]] == -1)||(matriz[regioesx[i]][regioesy[i]+1] == -1)){
bordax[l] = regioesx[i];
borday[l] = regioesy[i];
l++;
}
}*/

for(i=0;i<m;i++){
  for(j=0;j<n;j++){
   if(matriz[i][j]==-1){
    if(((i-1)<0)||((j-1)<0)||((i+1)==m)||((j+1)==n)){
     bordax[l] = i;
     borday[l] = j;
     l++;
    }
    else if((matriz[i][j-1]!=-1)||(matriz[i-1][j]!=-1)||(matriz[i+1][j]!=-1)||(matriz[i][j+1]!=-1)){
     bordax[l] = i;
     borday[l] = j;
     l++;
    }
   }
  }
}

for(i=0;i<=l;i++){
  printf("(%d, %d)\n",bordax[i],borday[i]);
}

free(x);
free(y);
free(c);
free(matriz);
/*free(regioesx);
free(regioesy);*/
free(bordax);
free(borday);
fclose(arquivo);

  return 0;
}