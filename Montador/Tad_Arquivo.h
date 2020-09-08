#ifndef Tad_Arquivo_H
#define Tad_Arquivo_H

/*   Esta função tem retorno do tipo ponteiro para arquivo, tem por parâmetros o nome do arquivo e o modo que ele deve ser aberto, leitura ou escrita.*/
FILE *inicia_arquivo(char *NomeArq, char *Modo);

/*   Esta função tem como parâmetro uma string que passará a conter a linha atual do arquivo, um ponteiro para arquivo que fará o controle da leitura 
  do mesmo, e um ponteiro para inteiro que dirá se o arquivo atingiu seu fim ou não.*/
void carrega_arquivo(char *linha, FILE *arq, int *x);

/*   Esta função tem como parâmetro uma string que será salva diretamente no arquivo caso o inteiro flag seja impar, caso flag seja par essa string que foi
  passada por parâmetro será um numero binário de 32 digitos em forma de string, então se a flag é par é feita a tradução de binario para hexadecimal para
  somente então ser salvo no arquivo a tradução, e o ultimo parâmetro é o ponteiro do arquivo de saída que dirá onde escrever no arquivo.*/
void salva_arquivo(char *bin, FILE *arq,int flag);

#endif