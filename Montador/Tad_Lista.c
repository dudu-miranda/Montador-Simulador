/*	Aluno:Eduardo Gabriel Reis Miranda
	Matricula:0026495
	Data:31/05/2017
	Sinopse:Arquivo que contém as manipulações da lista encadeada.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Tad_Arquivo.h"

typedef struct{	

	int pos;
	char label[30];
	int local;
}tipo_label;
/*Definido que os labels não terão mais que 30 caracteres*/

struct celula{
	
	tipo_label info;
	struct celula *prox;
};
/*Cada celula conterá o tipo_label e um ponteiro apontando para a próxima celula*/

typedef struct celula *celula_ptr; 

/*Tipo abstrato de dados lista*/
typedef struct{
	
	celula_ptr prim;
    celula_ptr ult;
    int n_elem;
}lista;

//variavel global do tipo lista com primeiro, ultimo e número de elementos
lista fil;   

//Declarações de todas as funções
celula_ptr inicia_l(celula_ptr p);
void add_l(tipo_label x);
void delete_l();
void mostrar_l();
void acha_label();
int retorna_item(char *x);
void escreve_label(FILE *arq,int modo);

//       :::::::::::::::    :::::::::::::::::::::::::::::::::    :::              :::
//          :+:    :+:+:   :+:    :+:   :+:    :+:   :+:      :+: :+:            :+:
//         +:+    :+:+:+  +:+    +:+   +:+          +:+     +:+   +:+           +:+
//        +#+    +#+ +:+ +#+    +#+   +#+          +#+    +#++:++#++:          +#+
//       +#+    +#+  +#+#+#    +#+   +#+          +#+    +#+     +#+          +#+
//      #+#    #+#   #+#+#    #+#   #+#    #+#   #+#    #+#     #+#          #+#
// ##############    #####################################     #######################

/*Função para iniciação da lista onde primeiro e ultimo terão o endereço de p,
  e a proxima celula será definida como NULL*/
celula_ptr inicia_l(celula_ptr p){

	p =  malloc(sizeof(struct celula));

	fil.prim=p;
	fil.ult=p;

	p->prox=NULL;
	fil.n_elem=0;

	return p;
}

//           :::    ::::::::: :::::::::           :::
//        :+: :+:  :+:    :+::+:    :+:          :+:
//      +:+   +:+ +:+    +:++:+    +:+          +:+
//    +#++:++#++:+#+    +:++#+    +:+          +#+
//   +#+     +#++#+    +#++#+    +#+          +#+
//  #+#     #+##+#    #+##+#    #+#          #+#
// ###     ############ ######### ####################

/*Função para adicionar um novo label que será sempre inserido na ultima posição*/
void add_l(tipo_label x){

	celula_ptr aux;
	aux=malloc(sizeof(struct celula));

	aux->info=x;
	aux->prox=NULL;

	fil.ult->prox=aux;
	fil.ult=aux;
	fil.ult->prox=NULL;
	fil.n_elem++;
	
	return;
}

//       ::::::::: :::::::::::::       :::::::::::::::::::::::::::::::          :::
//      :+:    :+::+:       :+:       :+:           :+:    :+:                 :+:
//     +:+    +:++:+       +:+       +:+           +:+    +:+                 +:+
//    +#+    +:++#++:++#  +#+       +#++:++#      +#+    +#++:++#            +#+
//   +#+    +#++#+       +#+       +#+           +#+    +#+                 +#+
//  #+#    #+##+#       #+#       #+#           #+#    #+#                 #+#
// ######### ##############################    ###    ##############################

//Função que deletará toda a lista
void delete_l(){

	celula_ptr p=fil.prim;
	celula_ptr aux=p->prox;

	while(aux!=NULL){
		
		free(p);
		p=aux;
		aux=aux->prox;
	}

	free(p);

	return;

}

//       ::::::::: ::::::::::::::::::::::::::::: ::::::::: ::::    :::    :::              ::::::::::::::::::::::::::::::::  :::   :::
//      :+:    :+::+:           :+:   :+:    :+::+:    :+::+:+:   :+:  :+: :+:                :+:        :+:    :+:        :+:+: :+:+:
//     +:+    +:++:+           +:+   +:+    +:++:+    +:+:+:+:+  +:+ +:+   +:+               +:+        +:+    +:+       +:+ +:+:+ +:+
//    +#++:++#: +#++:++#      +#+   +#+    +:++#++:++#: +#+ +:+ +#++#++:++#++:              +#+        +#+    +#++:++#  +#+  +:+  +#+
//   +#+    +#++#+           +#+   +#+    +#++#+    +#++#+  +#+#+#+#+     +#+              +#+        +#+    +#+       +#+       +#+
//  #+#    #+##+#           #+#   #+#    #+##+#    #+##+#   #+#+##+#     #+#              #+#        #+#    #+#       #+#       #+#
// ###    #############    ###    ######## ###    ######    #######     ########################    ###    #############       ###

//Função que retornará a posição da label que foi passada por parâmetro
int retorna_item(char *x){

	celula_ptr aux;
	aux=fil.prim;

	while(aux!=NULL && strcmp(aux->info.label,x)!=0){
		aux=aux->prox;
	}

	if(aux==NULL){
		return 0;
	}

	return aux->info.pos;

}

//         :::   :::   ::::::::  ::::::::::::::::::::::::::::     :::    :::::::::           :::
//       :+:+: :+:+: :+:    :+::+:    :+:   :+:    :+:    :+:  :+: :+:  :+:    :+:          :+:
//     +:+ +:+:+ +:++:+    +:++:+          +:+    +:+    +:+ +:+   +:+ +:+    +:+          +:+
//    +#+  +:+  +#++#+    +:++#++:++#++   +#+    +#++:++#: +#++:++#++:+#++:++#:           +#+
//   +#+       +#++#+    +#+       +#+   +#+    +#+    +#++#+     +#++#+    +#+          +#+
//  #+#       #+##+#    #+##+#    #+#   #+#    #+#    #+##+#     #+##+#    #+#          #+#
// ###       ### ########  ########    ###    ###    ######     ######    #######################

/*Função que mostrará todos os labels e seus endereços começando do primeiro.*/
void mostrar_l(){

	celula_ptr p;

	p=fil.prim->prox;

	while (p!=NULL){
		printf("Label:%s - Posição:%d\n",p->info.label,p->info.pos);
		p=p->prox;
	}

	printf("A lista tem tamanho:%d\n\n",fil.n_elem);

	return;

}

//       ::::::::::::::::::  :::::::: ::::::::: :::::::::::::     :::::::::::::          :::           :::    ::::::::: :::::::::::::
//      :+:      :+:    :+::+:    :+::+:    :+::+:       :+:     :+::+:                 :+:         :+: :+:  :+:    :+::+:       :+:
//     +:+      +:+       +:+       +:+    +:++:+       +:+     +:++:+                 +:+        +:+   +:+ +:+    +:++:+       +:+
//    +#++:++# +#++:++#+++#+       +#++:++#: +#++:++#  +#+     +:++#++:++#            +#+       +#++:++#++:+#++:++#+ +#++:++#  +#+
//   +#+             +#++#+       +#+    +#++#+        +#+   +#+ +#+                 +#+       +#+     +#++#+    +#++#+       +#+
//  #+#      #+#    #+##+#    #+##+#    #+##+#         #+#+#+#  #+#                 #+#       #+#     #+##+#    #+##+#       #+#
// ##################  ######## ###    #############    ###    #################################     ############ ####################

void escreve_label(FILE *arq,int modo){

	celula_ptr x=fil.prim;


	if (modo==1){
		x=x->prox;
		
		while(x!=NULL && x->info.local!=2){
			char string[30];
			strcpy(string,"");

			strcat(string,x->info.label);
			strcat(string,": ");

			char y[10];
			sprintf(y, "%i", x->info.pos);

			strcat(string,y);
			strcat(string,"\0");

			salva_arquivo(string,arq,3);
			x=x->prox;
		}
	}

	else{

		x=x->prox;
		while(x!=NULL && x->info.local!=2){
			x=x->prox;
		}

		while(x!=NULL){
			char string[30];
			strcpy(string,"");

			char y[10];
			sprintf(y, "%i", x->info.pos);

			strcat(string,x->info.label);
			strcat(string,": ");
			strcat(string,y);
			strcat(string,"\0");

			salva_arquivo(string,arq,3);
			x=x->prox;
		}

	}

	return;

}