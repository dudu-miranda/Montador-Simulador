#ifndef Tad_String_H
#define Tad_String_H

/*   Esta função tem como parâmetro um ponteiro para inteiro que fará o controle do local em que se está na string, uma string que contém o comando atual,
  e uma string que conterá um registrador ou instrução ou imediato ou shampt dependerá da linha.*/
void avancar(int *i,char *linha,char *x);

/*   Esta função tem como parâmetro uma string, e na saida dela caso haja algum comentário na string que foi passada, este será excluido.*/
void apaga_comentario(char *x);

/*   Esta função tem como parâmetro uma string, e ela apagará espaços desnecessários para que a função avançar funcione corretamente.*/
void apaga_espaco(char *str);

/*   Esta função tem como parâmetro uma string, e ela apagará toda e qualquer identação desnecessária para que a função avancar funcione char corretamente.*/
void tira_ident(char *str);

/*   Esta função tem como parâmetro uma string, e ela chama as três funções acima.*/
void limpa_str(char *str);

/*   Esta função serve somente para as instruções do tipo R, ela tem como parâmetro 6 strings que são o que compõe as instruções do tipo R, e uma 
  sétima string que conterá após a saida da função o binário completo. Esta função existe pois na época em que foi feita eu não conhecia a função
  strcat e resolvi fazer a minha. XD*/
void juntar1(char *opcode, char *r1, char *r2, char *r3, char *shamp, char *funct,char *x);

/*   Esta função serve somente para as instruções do tipo I, ela tem como parâmetro 4 strings que são o que compõe as instruções do tipo I, e uma 
  quita string que conterá após a saida da função o binário completo. Esta função existe pois na época em que foi feita eu não conhecia a função
  strcat.*/
void juntar2(char *opcode, char *r1, char *r2, char *immediate,char *x);

/*   Esta função serve somente para as instruções do tipo J, ela tem como parâmetro 2 strings que são o que compõe as instruções do tipo J, e uma 
  terceira string que conterá após a saida da função o binário completo. Esta função existe pois na época em que foi feita eu não conhecia a função
  strcat.*/
void juntar3(char *opcode,char *adress,char *x);

/*   Esta função tem como parâmetro uma string que conterá algo, ela tem como objetivo dizer se este algo é um número escrito em hexa decimal, caso seja
  ela dará o retorno 0, caso contrário o retorno será 1.*/
int identifica_hex(char *inst);

/*   Esta função tem como parâmetro uma string que conterá algo, ela tem como objetivo dizer se este algo é uma label, caso seja  ela dará o retorno 1,
  caso contrário o retorno será 0. Normalmente esta função é chamada logo após chamarmos a função acima pela sua forma de funcionamento.*/
int identifica_lab(char *inst);

/*   Esta função tem como parâmetro um número que será convertido para binário, uma string que conterá o número em binário traduzido, e um inteiro que é
  referente a que tamanho este binário possui. O método utilizado para conversão foi de divisões sucessivas.*/
void decimal_binario(int num, char *vet,int tam);

/*   Esta função tem como parâmetro uma string de tamanho 5, que conterá um número em binário e o '\0', ela tem como retorno um char, que será exatamente
  a tradução em hexadecimal do numero binário que foi passado.*/
char bin_hexa(char *v);

/*   Esta função tem como parâmetro uma string que possuirá uma instrução, ela dará retorno 1 caso seja uma instrução do tipo R, retorno 2 para instruções
  do tipo I, retorno 3 para instruções do tipo J, retorno 4 para diretivas e retorno 5 para pseudo instruções.*/
int identifica_tipo(char *inst);

#endif

