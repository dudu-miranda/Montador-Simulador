/*	Aluno:Eduardo Gabriel Reis Miranda
	Matricula:0026495
	Data:31/05/2017
	Sinopse:Arquivo que irá ler todo o arquivo pela primeira vez, guardar os labels e seus respectivos endereços em uma lista encadeada
	e irá retornar a quantidade de memória que devem ser guardada pra parte de texto e para a parte de dados. 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Tad_Lista.h"
#include "Tad_Arquivo.h"
#include "Tad_String.h"

void tratamento4_c(char *linha,int *cont);
void tratamento5_c(char *linha,int *cont);
void acha_label(char *arq1,int *mem_data,int *mem_text);
void adquire_label(char *arq1,int *mem_data,int *mem_text);

//   ::::::::::::::::::::     :::::::::::::::::      :::   :::  ::::::::::::::    ::::::::::::::::::::::     :::              ::::::::
//      :+:    :+:    :+:  :+: :+:  :+:  :+: :+:   :+:+: :+:+: :+:       :+:+:   :+:    :+:   :+:    :+:   :+:              :+:    :+:
//     +:+    +:+    +:+ +:+   +:+ +:+ +:+   +:+ +:+ +:+:+ +:++:+       :+:+:+  +:+    +:+   +:+    +:+  +:+ +:+           +:+
//    +#+    +#++:++#: +#++:++#++:+#++#++:++#++:+#+  +:+  +#++#++:++#  +#+ +:+ +#+    +#+   +#+    +:+ +#+  +:+           +#+
//   +#+    +#+    +#++#+     +#++#++#+     +#++#+       +#++#+       +#+  +#+#+#    +#+   +#+    +#++#+#+#+#+#+         +#+
//  #+#    #+#    #+##+#     #+##+##+#     #+##+#       #+##+#       #+#   #+#+#    #+#   #+#    #+#      #+#           #+#    #+#
// ###    ###    ######     #########     ######       ################    ####    ###    ########       ###  ##################

//Tratamento das diretivas
void tratamento4_c(char *linha,int *cont){

	if(strstr(linha,".asciiz")!=NULL){

		linha=strchr(linha,'"');
		linha=linha+1;

		int i=0;
		while(linha[i]!='"'){
			*cont=*cont+1;
			i++;
		}

		while(*cont%4!=0){
			*cont=*cont+1;
		}

	}

	else if(strstr(linha,".byte")!=NULL){
		//começando big end vai colocando os bytes numeros que o usuario passará multiplo x4

		linha=strchr(linha,' ');
		linha=linha+1;
		int i=0;
		char temp[20];

		avancar(&i,linha,temp);
		while(linha[i]!='\0'){
			*cont=*cont+1;
			avancar(&i,linha,temp);		
		}

		while(*cont%4!=0){
			*cont=*cont+1;
		}

	}

	else if(strstr(linha,".word")!=NULL){
		//vai guardando os numeros que o usuario deseja em 32 bits

		linha=strchr(linha,' ');
		linha=linha+1;
		int i=0;

		if(strchr(linha,',')==NULL){
			*cont=*cont+4;
		}

		else{

			char temp[20];
			while(linha[i]!='\0'){
				
				*cont=*cont+4;
				avancar(&i,linha,temp);
			}
		}	
	}

	else if(strstr(linha,".space")!=NULL){
		//vai guardar N bytes que o usuario mandar e preencher tudo com 0
		char *x=strchr(linha,' ');
			x=x+1;

			*cont=*cont+strtol(x,NULL,10);

			while(*cont%4!=0){
			*cont=*cont+1;
			}
			
	}	

	return;

}

//   ::::::::::::::::::::     :::::::::::::::::      :::   :::  ::::::::::::::    :::::::::::::::::::::: ::::::::::          ::::::::
//      :+:    :+:    :+:  :+: :+:  :+:  :+: :+:   :+:+: :+:+: :+:       :+:+:   :+:    :+:   :+:    :+::+:    :+:         :+:    :+:
//     +:+    +:+    +:+ +:+   +:+ +:+ +:+   +:+ +:+ +:+:+ +:++:+       :+:+:+  +:+    +:+   +:+    +:++:+                +:+
//    +#+    +#++:++#: +#++:++#++:+#++#++:++#++:+#+  +:+  +#++#++:++#  +#+ +:+ +#+    +#+   +#+    +:++#++:++#+          +#+
//   +#+    +#+    +#++#+     +#++#++#+     +#++#+       +#++#+       +#+  +#+#+#    +#+   +#+    +#+       +#+         +#+
//  #+#    #+#    #+##+#     #+##+##+#     #+##+#       #+##+#       #+#   #+#+#    #+#   #+#    #+##+#    #+#         #+#    #+#
// ###    ###    ######     #########     ######       ################    ####    ###    ########  ######## ##################

//Tratamento das pseudo instruções
void tratamento5_c(char *linha,int *cont){

	if(strstr(linha,"mov")!=NULL){
		*cont=*cont+4;//basicamente o addi
	}

	else if(strstr(linha,"li")!=NULL){
		*cont=*cont+8;//achar no site do luiz o esquema das duas funções
	}

	else if(strstr(linha,"la")!=NULL){
		*cont=*cont+8;//deve ta la no site tbm
	}

	else if(strstr(linha,"bge")!=NULL){
		*cont=*cont+8;
	}

	else if(strstr(linha,"bgt")!=NULL){
		*cont=*cont+8;
	}

	else if(strstr(linha,"ble")!=NULL){
		*cont=*cont+8;	
	}

	else if(strstr(linha,"blt")!=NULL){
		*cont=*cont+8;	
	}	

	return;
}

//           :::     :::::::: :::    :::    :::              :::           :::    ::::::::: :::::::::::::
//        :+: :+:  :+:    :+::+:    :+:  :+: :+:            :+:         :+: :+:  :+:    :+::+:       :+:
//      +:+   +:+ +:+       +:+    +:+ +:+   +:+           +:+        +:+   +:+ +:+    +:++:+       +:+
//    +#++:++#++:+#+       +#++:++#+++#++:++#++:          +#+       +#++:++#++:+#++:++#+ +#++:++#  +#+
//   +#+     +#++#+       +#+    +#++#+     +#+          +#+       +#+     +#++#+    +#++#+       +#+
//  #+#     #+##+#    #+##+#    #+##+#     #+#          #+#       #+#     #+##+#    #+##+#       #+#
// ###     ### ######## ###    ######     ##########################     ############ ####################

/*Função que lê o arquivo e coloca em uma TAD todos os labels e seus endereços.*/
void acha_label(char *arq1,int *mem_data,int *mem_text){	
    
    //Se abre o arquivo para leitura
    FILE *fp = inicia_arquivo(arq1, "rt");

    char linha[50]; //variavel que conterá a linha que esta sendo lida
    int contador=0; //contador que conterá a posição do label
    int flag=0;
    int x=2;

    carrega_arquivo(linha,fp,&x);
    while (x!=0){

    	if(strstr(linha,".data")!=NULL){
    		flag=1;
    	}

    	if(flag==1){

    		tipo_label aux;
    		aux.local=1;
    		while(strstr(linha,".text")==NULL){
    			  strcpy(linha,"");
    			  carrega_arquivo(linha,fp,&x);

    			  char op[50];
    			  strcpy(op,linha);
    			  char *lab=strchr(linha,':');

    			  if (lab!=NULL){
    			  	  lab=strtok(linha,":");
	    			  aux.pos=contador;
	    			  int i=0;	    			  
	    			  
	    			  while(lab[i]!='\0' || i>29){
	    			  	aux.label[i]=lab[i];
	    			  	i++;
	    			  }
	    			  aux.label[i]='\0';
	    			  
	    			  add_l(aux);

    			  
    			  	 char *temp=strchr(op,'.');
    			  	 tratamento4_c(temp,&contador);
    			  }
    		}
    		*mem_data=contador;

    		flag=2;
    	}

    	if(flag==2){
    		tipo_label aux;
    		aux.local=2;

    		char op[50];
    		strcpy(op,linha);
    		char *lab=strchr(linha,':');

    		if (lab!=NULL){
    			lab=strtok(linha,":");
	    		aux.pos=contador;
	    		int i=0;
	    			  
	    		while(lab[i]!='\0' || i>29){
	    		  	aux.label[i]=lab[i];
	    			i++;
	    		}
	    		aux.label[i]='\0';
	    		  
	    		add_l(aux);
    			  
   			  	char *temp=strchr(op,':');
   			  	temp=temp+1;

   			  	if(strchr(temp,' ')!=NULL){
   			  		temp=strtok(temp," ");

   			  		int id=identifica_tipo(temp);

		        	if(id==1 || id==2 || id==3){
		        		contador=contador+4;
		        	}

		        	else{
		        		tratamento5_c(temp,&contador);
		        	}
   			  			
   			  	}

   			  	else{
	        		if(strstr(op,"syscall")){
	        			contador=contador+4;
	        		}

	        	}
   			 
	        }

	        else{

	        	if(strchr(op,' ')!=NULL){

		        	char *temp=strtok(op," ");
		        	int id=identifica_tipo(temp);

		        	if(id==1 || id==2 || id==3){
		        		contador=contador+4;
		        	}

		        	else{
		        		tratamento5_c(temp,&contador);
		        	}

	        	}

	        	else{
	        		if(strstr(op,"syscall")){
	        			contador=contador+4;
	        		}

	        	}

	        }

    	}

    	carrega_arquivo(linha,fp,&x);    	
    }

    *mem_text=contador-*mem_data;
    
    fclose(fp);//fecha-se o arquivo

	return;
}

//           :::    :::::::::  ::::::::  :::    ::::::::::::::::::::::: ::::::::::          :::           :::    ::::::::: :::::::::::::
//        :+: :+:  :+:    :+::+:    :+: :+:    :+:    :+:    :+:    :+::+:                 :+:         :+: :+:  :+:    :+::+:       :+:
//      +:+   +:+ +:+    +:++:+    +:+ +:+    +:+    +:+    +:+    +:++:+                 +:+        +:+   +:+ +:+    +:++:+       +:+
//    +#++:++#++:+#+    +:++#+    +:+ +#+    +:+    +#+    +#++:++#: +#++:++#            +#+       +#++:++#++:+#++:++#+ +#++:++#  +#+
//   +#+     +#++#+    +#++#+    +#+ +#+    +#+    +#+    +#+    +#++#+                 +#+       +#+     +#++#+    +#++#+       +#+
//  #+#     #+##+#    #+##+#    #+# #+#    #+#    #+#    #+#    #+##+#                 #+#       #+#     #+##+#    #+##+#       #+#
// ###     ############  ################### ##############    ####################################     ############ ####################

void adquire_label(char *arq1,int *mem_data,int *mem_text){

	celula_ptr v=NULL;

	v=inicia_l(v);
	
	acha_label(arq1,mem_data,mem_text);

	return ;
}