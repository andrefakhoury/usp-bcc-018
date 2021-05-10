/*
Programa exemplo para gravar bits de um código binário em arquivo.

O código está *propositalmente* incompleto para que os alunos façam
os ajustes necessários.

A representação de um bitstream binário ( sequência de zeros e uns) é feita em 
memória normalmente usando inteiros (int ou char/unsigned char), que possuem 8 
ou até 32 bits por símbolo. Seria um desperdício de espaço gravar o bitstream 
em disco como inteiros em vez de gravar como bits.

Este exemplo mostra como um bitstream pode ser gravado em disco como bits.

Autor: Rudinei Goularte (2021)
*/
#include <stdio.h>
int main(void){
    char bitstream[9] = {'0','1','1','0','0','1','1','1','\0'}; /* 103 em binário*/
    unsigned char buffer = 0; /* ocupa um byte de espaço de memória*/
    int i;
    
    FILE *out, *out2; /* Arquivos para gravar o bitstream*/
    
     /*===> AQUI <======
      Código para transferir o conteúdo do bitstream para um byte, no caso, para 
      a variável buffer.
     */

    for (int i = 0; i < 8; i++) buffer |= (bitstream[i] - '0') << (7 - i);
       
    printf("\n%d", buffer);
   
    out2 = fopen("out.txt","w"); /*grava o bitstream como caracter -> 64 bits*/
    for(i=0;i<8;i++)
       fputc(bitstream[i], out2);
    fclose(out2);

    out = fopen("out.bin","wb"); /* grava o bitstream como bits -> 8 bits*/
    fwrite(&buffer,1,sizeof(buffer), out);
    fclose(out);
    
   
    /* Compare o tamanho dos arquivos gerados: out.txt e out.bin!
       Abra o arquivo out.txt e veja o que está gravado!
    */

    // 1 vs 8 bytes!
    
    /*PERGUNTA: E se o bitstream tivesse mais de 8 bits? Como fazer para gravar no
      arquivo?
    */
    // vai indo ate onde da, de 8 em 8
        
    printf("\n");
}