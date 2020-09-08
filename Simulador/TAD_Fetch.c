#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Simulador.h"

void busca_arquivo(char *NomeArq, Simulador *X);
unsigned int busca_instrucao(Simulador *X);

void busca_arquivo(char *NomeArq, Simulador *X){

	FILE *arq;
	// Abre um arquivo TEXTO para LEITURA
	arq = fopen(NomeArq,"rt");
	char linha[11];
	//variavel que dirá se o hexadecimal a ser lido é uma instrução ou um dado estático
	int est=1;
	//variaveis que controlarão o preenchimento das memórias
	int i=0,j=0;

	while (!feof(arq)){
		//pega-se a linha
		fgets(linha,11,arq);

		//tratamento caso seja um label ou qualquer outra coisa que deva ser ignorada
		if (linha[0]=='=' || linha[0]==' ' || linha[0]=='\n' || linha[0]=='\0'){	
		}

		//tratamento caso seja um indicativo
		else if(linha[0]=='.'){

			char *temp;

			//caso seja .data
			if (strstr(linha,"end")==NULL && strstr(linha,"data")!=NULL){				
				//pega-se o numero que acompanha o .data
				temp=strchr(linha,' ');
				temp=temp+1;

				//tamanho da memoria de dados +200 para dados que precisem ser alocados
				int tamanho=strtol(temp,NULL,10)+200;

				//aloca-se os dados
				X->memo_data=malloc(tamanho*sizeof(int));
				//coloca-se o topo da memória de dados onde os mesmos serão alocados inicialmente
				X->topo_memdata=tamanho;
				//coloca-se o tamanho da memória total dos dados 
				X->size_memdata=tamanho;				
	 		}

			//caso seja .text
			else if (strstr(linha,"end")==NULL && strstr(linha,"text")!=NULL){				
				//pega-se o numero acompanhado do .text e coloca ele em uma variavel
				temp=strchr(linha,' ');
				temp=temp+1;
				int tamanho=strtol(temp,NULL,10);

				//aloca-se esta memória e atribui-se a variavel do tamanho da memória de texto
				X->memo_cod=malloc(tamanho*sizeof(int));	
				X->size_memcod=tamanho;
				//troca-se o estado para 2 indicando que os hexadecimais que virão agora são instruções
				est=2;			
			}

		}

		//tratamento das instruçoes
		else{
			//da-se o tratamento de dados e posteriormente de instruções para a atribuição das memórias
			if(est==1){
				X->memo_data[i]=strtol(linha,NULL,16);
				i++;
			}

			else{
				X->memo_cod[j]=strtol(linha,NULL,16);
				j++;
			}

		}//fim tratamento das instruções

	}//fim while eof

}

unsigned int busca_instrucao(Simulador *X){

	X->pc++;
	X->npc++;

	return X->memo_cod[X->pc];
}