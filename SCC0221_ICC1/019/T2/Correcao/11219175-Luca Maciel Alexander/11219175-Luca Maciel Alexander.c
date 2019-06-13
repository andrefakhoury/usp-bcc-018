#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>


// declarando "bag of words"
float BoW[10][303];

// variaveis auxiliares
int foundVoid = 0;
int foundInBow = 0;





// funcao para interpretar as perguntas finais 
void questionInterpreter(char words[300][21], char itemMarca[10][42], int lastQuestionMaybe){

int productIndex, wordIndex;
char wordBuffer1[42] = {0};
char wordBuffer2[42] = {0};
char charBuffer1, charBuffer2;
int l;
int m = 0;
float percentage;

charBuffer1 = getchar();

// antecipando pergunta de "quantos ..."
if(charBuffer1 == 'q'){
  for(l = 0; l < 7; l++){
    // pulando a string "quantos "
    charBuffer1 = getchar();
  }

  // 'p' ou 'n':
  charBuffer1 = getchar();

  // pulando string "positivos " ou "negativos " e string "em "
	 for(l = 0; l < 12; l++){
	   charBuffer2 = getchar();
	 }

  // guardando nome do produto
  if(lastQuestionMaybe == 0){
	 do{
	   charBuffer2 = getchar();
		if (charBuffer2 == '\r') continue;
	   if((charBuffer2 != ' ')&&(charBuffer2 != '\n')){
		wordBuffer1[m] = charBuffer2;
		m++;
	   } 
	   if(charBuffer2 == '\n'){
		break;
	   }
	   else{
		 continue;
	   }
	 }
	 while(1);
  }

  else{
	 do{
	   charBuffer2 = getchar();
		if (charBuffer2 == '\r') continue;
	   if((charBuffer2 != ' ')&&(charBuffer2 != '\n')&&(charBuffer2 != EOF)){
		wordBuffer1[m] = charBuffer2;
		m++;
	   } 
	   if(charBuffer2 == EOF){
		break;
	   }
	   if(charBuffer2 == '\n'){
		break;
	   }
	   else{
		 continue;
	   }
	 }
	 while(1);
  }

// encontrando o indice do produto no Bag of Words
for(l = 0; l < 10; l++){
  if(strcmp(wordBuffer1, itemMarca[l]) == 0){
      productIndex = l;
      break;
  }
}

  // antecipando "positivos"
  if(charBuffer1 == 'p'){
      percentage = 100*(BoW[productIndex][300] / BoW[productIndex][302]);
      percentage = roundf(10*percentage)/10;
      printf("%0.1f%%\n", percentage);
  }
  // antecipando "negativos"
  else{
      percentage = 100*(BoW[productIndex][301] / BoW[productIndex][302]);
      percentage = roundf(10*percentage)/10;
      printf("%0.1f%%\n", percentage);
  }



}




// antecipando pergunta de "palavra ..."
else{
  // pulando a string "palavra "
  for(l = 0; l < 7; l++){
    charBuffer1 = getchar();
  }

  // guardando a palavra a ser encontrada
  do{
    charBuffer1 = getchar();

    if(charBuffer1 != ' '){
      wordBuffer2[m] = charBuffer1;
      m++;
    }
    else{
      m = 0;
      break;
    }
  }
  while(1);

  // pulando string "em "
  for(l = 0; l < 3; l++){
    charBuffer1 = getchar();
  }

  // guardando o produto em questao
  if(lastQuestionMaybe == 0){
  do{
   charBuffer1 = getchar();
   if (charBuffer1 == '\r') continue;
   if((charBuffer1 != ' ')&&(charBuffer1 != '\n')){
		wordBuffer1[m] = charBuffer1;
		m++;
   }
   if(charBuffer1 == '\n'){
		break;
   }
   else{
		continue;
   }
  }
  while(1);
  }

  else{
    do{
   charBuffer1 = getchar();
   if (charBuffer1 == '\r') continue;
   if((charBuffer1 != ' ')&&(charBuffer1 != '\n')&&(charBuffer1 != EOF)){
		wordBuffer1[m] = charBuffer1;
		m++;
   }
   if(charBuffer1 == EOF){
	break;
   }
   if(charBuffer1 == '\n'){
		break;
   }
   else{
		continue;
   }
  }
  while(1);
  }

// procurando indice do produto no Bag of Words
for(l = 0; l < 10; l++){
  if(strcmp(wordBuffer1, itemMarca[l]) == 0){
      productIndex = l;
      break;
  }
}

// procurando indice da palavra no Bag of Words
for(l = 0; l < 300; l++){
  if(strcmp(wordBuffer2, words[l]) == 0){
      wordIndex = l;
      break;
  }
}

  // respondendo a pergunta
  printf("%0.0f\n", BoW[productIndex][wordIndex]);

}




}





// ler produto e conferir se ja foi lido antes
// retorna um int: o indice de onde achou/inseriu o nome do produto
int scanAndMaybeAddToItemMarca(char itemMarca[10][42]){

char buffer[42] = {0};
int buffersBuffer = {0};
int i = 0;
int j = 0;

// guardando o item e marca (produto) no buffer
do{
  buffersBuffer = getchar();
    if(buffersBuffer == ' '){
      continue;
    }
    if(buffersBuffer == ';'){
      break;
    }
    else{
      buffer[i] = buffersBuffer;
      i++;
    }
}
while(1);

// conferindo se produto ja foi encontrado e retornando indice
for(i = 0; i < 10; i++){
  if(strcmp(buffer, itemMarca[i]) == 0){
    // houve mais um review desse produto:
    BoW[i][302]++;
    // (retornando indice)
    return i;
  }
}

// caso NAO foi encontrado, adicionar! (e retornar indice)
for(i = 0; i < 10; i++){
  if(itemMarca[i][0] == '0'){
    for(j = 0; j < 42; j++){
    itemMarca[i][j] = buffer[j];
  }
  // houve mais um review desse produto:
  BoW[i][302]++;
  // (retornando indice)
  return i;
}

}

// erro
return -1;
}







// ler palavra e conferir se ja foi lida antes
// retorna um int: o indice de onde achou/inseriu a palavra
int scanAndMaybeAddToWords(char words[300][21], int firstIndex){

char buffer[21] = {0};
int buffersBuffer = {0};
int i = 0;
int j = 0;

// guardando a palavra no buffer
do{
  buffersBuffer = getchar();
    if((char)buffersBuffer == ' ' && i == 0){
      /*levando em conta um erro de formatacao em um caso teste fo run.codes*/
      continue;
    }
    if(buffersBuffer == 152 /*segundo byte do caracter especial*/){
      foundVoid = 1;
      break;
    }
    if(buffersBuffer == 195 /*primeiro byte to caracter especial*/){
      continue;
    }
    if((char)buffersBuffer == ' '){
      break;
    }
    else{
      buffer[i] = (char)buffersBuffer;
      i++;
    }
}
while(1);

// conferindo se palavra ja foi encontrado e retornando indice
for(i = 0; i < 300; i++){
  if(strcmp(buffer, words[i]) == 0){
    // (retornando indice pq ja encontramos essa palavra antes)
    // tambem incrementando BoW
    BoW[firstIndex][i]++;
    return i;
  }
}

// caso NAO foi encontrado, adicionar! (e retornar indice)
for(i = 0; i < 300; i++){
  if(words[i][0] == '0'){
    for(j = 0; j < 21; j++){
    words[i][j] = buffer[j];
  }
  // (retornando indice de onde adicionamos a palavra ao dicionario)
  // tambem incrementando BoW
  BoW[firstIndex][i]++;
  return i;
}

}

// erro
return -1;
}





int main(void) {

// posNegBuf para ver se frase foi negativa ou positiva
// advNegBuf para ver se adverbio muda polaridade do posNegBuf
int nFrases, nPerguntas, posNegBuf = 0, advNegBuf = 0;
int i, j;
// coordenadas do Bag of Words
int firstIndexBuf, secondIndexBuf;

int a = 0;

char advNeg[3][21] = {{"nao"},{"jamais"},{"nunca"}};
char negativas[12][21] = {{"detestei"},{"odiei"},{"ruim"},{"pessimo"},{"terrivel"},{"raiva"},{"lento"},{"odio"},{"pessima"},{"lenta"},{"fragil"},{"desisti"}};
char positivas[12][21] = {{"bom"},{"maravilhoso"},{"otimo"},{"sensacional"},{"excelente"},{"adorei"},{"gostei"},{"amei"},{"eficiente"},{"boa"},{"maravilhosa"},{"otima"}};

// lugar para guardar os produtos e palavras encontrados
char itemMarca[10][42] = {0}, words[300][21] = {0};

// inicializando words e itemMarca   
int k;
for(k = 0; k < 10; k++){
  itemMarca[k][0] = '0';
}
for(k = 0; k < 300; k++){
  words[k][0] = '0';
}

scanf("%d%d", &nFrases, &nPerguntas);

// eliminando o primeiro '\n'
char *temp = (char*)malloc(sizeof(char));
*temp = getchar(); //  \r
*temp = getchar(); //  \n
free(temp);


// iniciando o algoritmo

for(i = 0; i < nFrases; i++){

posNegBuf = 0;
advNegBuf = 0;

// conferindo o produto da dada linha e incrementando a quantidade de 
// vezes que o produto tem review (BoW[algo][202])
firstIndexBuf = scanAndMaybeAddToItemMarca(itemMarca);

//(eliminando o ' ' antes da primeira palavra do review em si)
char *temp1 = (char*)malloc(sizeof(char));
*temp1 = getchar();
free(temp1);



do{

// conferindo a palavra individual e incrementando BoW
secondIndexBuf = scanAndMaybeAddToWords(words, firstIndexBuf);

// contando review positivo, negativo e considerando adverbios

//adverbios
for(j = 0; j < 3; j++){
  if(strcmp(words[secondIndexBuf], advNeg[j]) == 0){
    advNegBuf = 1;
  }
}
//positivas
for(j = 0; j < 12; j++){
  if(strcmp(words[secondIndexBuf], positivas[j]) == 0){
      if(advNegBuf == 0){
        posNegBuf = 1; /*'1' eh positivo, '2' eh negativo, '0' eh erro*/
      }
      else{
        posNegBuf = 2;
      }
  }
}
//negativas
for(j = 0; j < 12; j++){
  if(strcmp(words[secondIndexBuf], negativas[j]) == 0){
      if(advNegBuf == 0){
        posNegBuf = 2; /*'1' eh positivo, '2' eh negativo, '0' eh erro*/
      }
      else{
        posNegBuf = 1;
      }
  }
}
//cuidados com o advNegBuf:
if(advNegBuf > 0 && advNegBuf < 4){
  advNegBuf++;
}
else{
  advNegBuf = 0;
}

}
while(foundVoid == 0);



// preparando para entrar na proxima linha
foundVoid = 0;
// eliminando o \n no final da ultima palavra
char *temp2 = (char*)malloc(sizeof(char));
*temp2 = getchar(); //  \r
*temp2 = getchar(); //  \n
free(temp2);

// incrementando BoW (quantos positivos e negativos?)
// Bow[...][300] = (+), BoW[...][301] = (-)
if(posNegBuf == 1){
  BoW[firstIndexBuf][300]++;
}
if(posNegBuf == 2){
  BoW[firstIndexBuf][301]++;
}

}




// FIM DA MONTAGEM DA BAG OF WORDS
// INICIO DA INTERPRETACAO DAS PERGUNTAS 

//(possivelmente inserir nova linha aqui)

for(i = 0; i < nPerguntas; i++){

if(i == nPerguntas - 1){
  a = 1;
}

// respondendo pergunta
questionInterpreter(words, itemMarca, a);

}


return 0;
}
