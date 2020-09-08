#ifndef Tad_Lista_H
#define Tad_Lista_H

//Tipo da estrutura que contém o label.
typedef struct{	
	int pos;
	char label[30];
	int local;
}tipo_label;

//Ponteiro para célula que contém o label
typedef struct celula *celula_ptr; 

/*Esta função inicializará a lista encadeada que conterá os labels posteriormente.*/
celula_ptr inicia_l(celula_ptr p);

/*Esta função irá adicionar um label na lista encadeada.*/
void add_l(tipo_label x);

/*Esta função irá destruir toda a lista encadeada.*/
void delete_l();

/*Esta função irá mostrar toda a lista encadeada a partir do inicio.*/
void mostrar_l();

/*	De acordo com uma string que foi passada por parâmetro, esta função irá retornar um inteiro que será equivalente ao endereço desta label,
  caso esta label não esteja na lista o retorno padrão será 0.*/
int retorna_item(char *x);

void escreve_label(FILE *arq,int modo);

#endif