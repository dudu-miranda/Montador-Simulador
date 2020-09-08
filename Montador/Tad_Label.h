#ifndef Tad_Label_H
#define Tad_Label_H

/*	  Está função tem como parâmetro a linha atual e um ponteiro para um inteiro, tratamento4 diz que se trata do tratamento das diretivas
   e _c se trata da contagem dos endereços, dessa forma o inteiro que é passado possui o endereço do contador que cada label irá possuir.
*/
void tratamento4_c(char *linha,int *cont);

/*	  Está função tem como parâmetro a linha atual e um ponteiro para um inteiro, tratamento5 diz que se trata do tratamento das pseudo-instruções
   e _c se trata da contagem dos endereços, dessa forma o inteiro que é passado possui o endereço do contador que cada label irá possuir.
*/
void tratamento5_c(char *linha,int *cont);

/*	  A função acha_label é a que percorrerá todo o arquivo e guardará todos os labels contidos no mesmo. Essa função tem como parâmetro 
  o nome do arquivo que deverá ser aberto para leitura.
*/
void acha_label(char *arq1,int *mem_data,int *mem_text);


//	A função adquire_label inicializará uma lista encadeada e fará a chamada da função acha_label. Tem como parâmetro o arquivo a ser aberto.
void adquire_label(char *arq1,int *mem_data,int *mem_text);
#endif