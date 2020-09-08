#include <stdio.h>

#include "Simulador.h"
#include "TAD_Fetch.h"
#include "TAD_Decode.h"
#include "TAD_Execute.h"

void simula(char *arq);

void inicia_simulador(Simulador *X){

	//inicia todos os registradores com 0;
	for (int i = 0; i < 32; ++i){
		X->reg[i]=0;
	}

	//inicia os contadores de programa para quando ser necessário a busca de uma instrução ela seja feita sem nenhum tipo de tratamento
	X->npc=0;
	X->pc=-1;
}

void print_bin(unsigned int teste){

	while(teste){
		if (teste&1){
			printf("1");
		}
		else{
			printf("0");
		}

		teste=teste>>1;
	}
	printf("\n");

	return;
}

void simula(char *arq){

	Simulador X;
	unsigned int inst;
	int tipo;

	busca_arquivo(arq,&X);
	inicia_simulador(&X);

	while(1){
		inst=busca_instrucao(&X);
		tipo=get_tipo(get_opcode(inst));

		if(tipo==1){
			execute1(inst,&X);
		}
		else if (tipo==2){
			execute2(inst,&X);
		}
		else {
			execute3(inst,&X);
		}	
	}
}