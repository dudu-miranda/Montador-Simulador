#ifndef Simulador_H
#define Simulador_H

typedef struct simulador{

	//São os 32 registradores
	int reg[32];

	//Memórias destinadas para código e dados respectivamente. E seus tamanhos
	unsigned int *memo_cod;
	int size_memcod;

	unsigned int *memo_data;
	int size_memdata;
	int topo_memdata;

	//Apontadores para qual parte do programa se está
	unsigned int pc;
	unsigned int npc;

}Simulador;

void simula(char *arq);
#endif