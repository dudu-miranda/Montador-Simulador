/*	Aluno:Eduardo Gabriel Reis Miranda
	Matricula:0026495
	Data:31/05/2017
	Sinopse:Arquivo que chamará o passo 1 e passo 2 do montador passando como parâmetros os arquivos a serem abertos e variaveis
	que armazenarão a memória da parte de dados e da parte de texto.
*/

#include "Tad_Label.h"
#include "Tad_Tradutora.h"
#include <string.h>

void montador(char *arq_entrada,char *arq_saida);

void montador(char *arq_entrada,char *arq_saida){

	strcpy(arq_entrada,"arq.txt"); strcpy(arq_saida,"saida.out");	
	int mem_data,mem_text;

	adquire_label(arq_entrada,&mem_data,&mem_text);
	tradutor(arq_entrada,arq_saida,mem_data,mem_text);
}

