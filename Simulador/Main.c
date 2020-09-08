#include <stdio.h>

#include "Simulador.h"

int main(int argc, char *argv[]){

	/*
	if(argc>2){
		printf("Número de parâmetros maior que o esperado!\n");
	}
	else if(argc<2){
		printf("Número de parâmetros menor que o esperado!\n");
	}
	else{	
		simula(argv[1]);
	}
	*/

	simula("saida.out");

	return 0;
}