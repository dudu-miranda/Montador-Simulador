#ifndef Tad_Traducao_H
#define Tad_Traducao_H

/*    Esta função tem como parâmetros a instrução a ser traduzida, o tipo de instrução que se trata, e uma string que conterá o binário referente
  a instrução que foi passada, ela tem um retorno inteiro pois algumas instruções do tipo I e J possuem algumas particularidades e não seguem exatamente
  o mesmo padrão, enquanto da-se o retorno de um inteiro para saber o que se deve fazer.*/
int get_opcode(char *inst, int tipo,char *x);

/*   Esta função tem como parâmetros a instrução a ser traduzida, a string que conterá o binário referente a tradução e um inteiro que se chama estado,
  este inteiro funciona de maneira similar ao retorno da função acima, porém essa função é somente utilizada nas instruções do tipo R.*/
void get_func(char *inst,char *x, int *estado);

/*   Esta função tem como parâmetro uma string que conterá o registrador e uma string que conterá o binário referente a este registrador. O retorno
  padrão é "00000".*/
void get_register(char *reg,char *x);

/*   Esta função serve para somente as instruções do tipo R, tem por parâmetro um número ou um hexa decimal ou uma label, uma string que contém o 
  binário equivalente e um inteiro estado que serve para diferenciar o que deve ser feito, pois em 5 das 6 vezes o retorno será "00000"*/
void get_shamp(char *inst,char *x,int estado);

/*   Esta função serve para somente as instruções do tipo I, tem por parâmetro a um número ou um hexa decimal ou uma label e uma string que contém o 
  binário equivalente ao que foi passado.*/
void get_immediate(char *inst,char *imm);

/*   Esta função serve para somente as instruções do tipo J, tem por parâmetro a um número ou um hexa decimal ou uma label e uma string que contém o 
  binário equivalente ao que foi passado.*/
void get_adress(char *inst,char *adress);

/*   Esta função tratará as instruções do tipo R, ela tem como parâmetro a linha a ser traduzida e uma string de tamanho 33 que conterá o binário da
  word.*/
void tratamento1(char *linha,char *z);

/*   Esta função tratará as instruções do tipo I, ela tem como parâmetro a linha a ser traduzida e uma string de tamanho 33 que conterá o binário da
  word.*/
void tratamento2(char *linha,char *z);

/*   Esta função tratará as instruções do tipo J, ela tem como parâmetro a linha a ser traduzida e uma string de tamanho 33 que conterá o binário da
  word.*/
void tratamento3(char *linha,char *z);

/*   Esta função tratará a tradução das diretivas, ela tem como parâmetro a linha a ser traduzida o ponteiro do arquivo que está sendo salvo os 
  números em hexadecimal e uma string de tamanho 33 que conterá o binário da word. O ponteiro é necessário pois as diretivas não tem ao certo quantas 
  words precisarão ser salvas, dessa maneira se faz necessário salvar uma ou mais words no arquivo então para não ter que ser feitas checagens desnecessárias
  salva-se no arquivo as devidas traduções diretamente na função.*/
void tratamento4(char *linha,FILE *arq,char *z);

/*   Esta função tratará a tradução diretivas, ela tem como parâmetro a linha a ser traduzida, uma string de tamanho 33 que conterá o binário da word e
  o ponteiro do arquivo que está sendo salvo os números em hexadecimal. O ponteiro é necessário pois a maioria das pseudo-instruções se dividem em duas,
  dessa maneira se faz necessário salvar duas words no arquivo então para não ter que ser feitas checagens desnecessárias salva-se no arquivo as
  devidas traduções diretamente na função.*/
void tratamento5(char *linha,char *z,FILE *arq_saida);

#endif