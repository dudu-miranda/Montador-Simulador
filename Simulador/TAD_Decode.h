#ifndef TAD_Decode_H
#define TAD_Decode_H

unsigned int get_opcode(unsigned int x);
unsigned int get_register(unsigned int x,int tipo);
unsigned int get_shampt(unsigned int x);
unsigned int get_funct(unsigned int x);
unsigned int get_immediate(unsigned int x);
unsigned int get_adress(unsigned int x);
int get_tipo(unsigned int opcode);

#endif