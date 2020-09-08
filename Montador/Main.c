/*	Aluno:Eduardo Gabriel Reis Miranda
	Matricula:0026495
	Data:31/05/2017
	Sinopse:Arquivo que chamará o montador caso seja passado dois nomes de arquivo por parâmetro.
*/

//Trocar os \n do arquivo por '\n' pra dar a diferença e colocar um '\0' sempre no fim.

#include <stdio.h>
#include "Tad_Montador.h"

int main(int argc, char *argv[]){

	char str[20];	char str2[20]; argc=3;
	if(argc==3){
		montador(str,str2);
		//montador(argv[1],argv[2]);
	}

	else if(argc<3){
		printf("Número de argumentos insuficientes.\n" );
	}

	else{
		printf("Número de argumentos excede a quantidade necessária.\n" );
	}

	return 0;
}