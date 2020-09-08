#include <stdio.h>

unsigned int get_opcode(unsigned int x);
unsigned int get_register(unsigned int x,int tipo);
unsigned int get_shampt(unsigned int x);
unsigned int get_immediate(unsigned int x);
unsigned int get_adress(unsigned int x);
unsigned int get_funct(unsigned int x);
int get_tipo(unsigned int opcode);

unsigned int get_opcode(unsigned int x){

	x=x&(63<<26);

	return 	x>>26;
}

unsigned int get_register(unsigned int x,int tipo){

	if (tipo==1){
		x=x&(31<<21);
		return x>>21;
	}

	else if (tipo==2){
		x=x&(31<<16);
		return x>>16;
	}

	else {
		x=x&(31<<11);
		return x>>11;
	}
}

unsigned int get_shampt(unsigned int x){
	x=x&(31<<6);
	return x>>6;
}

unsigned int get_immediate(unsigned int x){
	return x&(0xffff);
}

unsigned int get_adress(unsigned int x){
	return x&(0x3ffffff);
}

unsigned int get_funct(unsigned int x){
	x=x&(63);
	return x;
}

int get_tipo(unsigned int opcode){
	//Retorna se a instrução é do tipo R
	if (opcode==0){
		return 1;
	}

	//Retorna se a instrução é do tipo J
	else if (opcode==2 || opcode==3){
		return 3;
	}

	//Retorna se a instrução é do tipo I
	else{
		return 2;
	}
}