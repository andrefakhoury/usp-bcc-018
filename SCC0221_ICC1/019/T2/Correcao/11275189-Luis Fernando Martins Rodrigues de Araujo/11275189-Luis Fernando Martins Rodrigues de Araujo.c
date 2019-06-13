#include<stdio.h>
#include<string.h>
/* professor, não consegui criar com sucesso toda a lógica do trabalho. De uma olhada geral.
     if( voce acha que algo pode ser considerado)
      continuar correcao;
      else
        poupar seu tempo e partir para o proximo;
      printf("obrigado e desculpe pelo transtorno");
*/

	     
/*segue a pre definicao do nome dos 10 produtos:
        tv motorola
        celular motorola
        tv lg
        celular lg
        tv samsumg
        celular samsung
        tv sony
        celular sony
        tv apple
        celular apple
*/


int main (void){
	int ns, np;
	scanf("%d %d", &ns, &np);
	char name[ns][30], cmnt[ns][400], prgnt[np][100];
	char **ec[ns], **ep[np] ;
	int f, i=0, k;
	int p, n, r=0;
	
// entrada nomes e comentarios
for(int a=0;a<=ns;a++){
	scanf("%[^;]s", name[a]);
	fgets(*(cmnt+a), 400, stdin);
}
for(int c=0; c<=ns; c++){
    *(ec+c) = strtok(*(cmnt+c), " ");
}

// entrada perguntas
	
for(int b=0; b<=np; b++){
	fgets(**(prgnt+b), 100, stdin);
}

for(int d=0; d<=np; d++){
	*(ep+d) = strtok(*(prgnt+d), " ");
	}
	
//determinando qual sera o tipo de pergunta

	for(int e=0;e<=np;e++){
		 switch(*(ep+e))	{
			case "palavra":               
			for(int g=0; g<=ns;g++){
				f=strlen(*(ec + g));    //determina o num de palavras de cada comentario
			    for(int h=0;h<=f;h++){
			    if( *(*(ep+e)+1) == *(*(ec+g)+h) ) // compara a segunda palavra da pergunta com todas as palavras de cada comentario
				i++;
				}
			    
				}
			
			
			
			
			
			
			
			
			
			break;
			case "quantos":
				for(g=0; g<=ns;g++){
					
				k = strlen(*(ec+g));
				r =strcmp(*(*(ep+e)+1) == "positivos"); //faria o mesmo processo para os negativos
				if(r==0){
					for(int s=0;s<=k;s++){  // compara palavra por palavra com uma string que comtem tds as palavras positivas
						l = strcmp(*(*(ep+e)+s), )
						if()
					}
				}
			
					
					
				}
	}			
				
	printf("%d", i);	
	    }
	
	}
	
	
	
	
	
	
	













return 0;


}

