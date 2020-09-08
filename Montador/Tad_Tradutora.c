/*	Aluno:Eduardo Gabriel Reis Miranda
	Matricula:0026495
	Data:31/05/2017
	Sinopse:Arquivo que percorrerá por todo o arquivo pela segunda vez, mas desta vez já irá escrever no arquivo de saída.
*/

#include <stdio.h>
#include <string.h>
#include "Tad_Arquivo.h"
#include "Tad_Traducao.h"
#include "Tad_String.h"
#include "Tad_Lista.h"


void tradutor(char *arq1,char *arq2,int mem_data,int mem_text);

//   ::::::::::::::::::::     :::    ::::::::: :::    :::::::::::::::::::::: :::::::::
//      :+:    :+:    :+:  :+: :+:  :+:    :+::+:    :+:    :+:   :+:    :+::+:    :+:
//     +:+    +:+    +:+ +:+   +:+ +:+    +:++:+    +:+    +:+   +:+    +:++:+    +:+
//    +#+    +#++:++#: +#++:++#++:+#+    +:++#+    +:+    +#+   +#+    +:++#++:++#:
//   +#+    +#+    +#++#+     +#++#+    +#++#+    +#+    +#+   +#+    +#++#+    +#+
//  #+#    #+#    #+##+#     #+##+#    #+##+#    #+#    #+#   #+#    #+##+#    #+#
// ###    ###    ######     ############  ########     ###    ######## ###    ###

void tradutor(char *arq1,char *arq2,int mem_data,int mem_text){

	char linha[50];
	char bin[33];  bin[32]='\0';
	FILE *arq_entrada = inicia_arquivo(arq1, "rt");// Abre um arquivo para leitura
	FILE *arq_saida = inicia_arquivo(arq2, "wt");// Cria um arquivo texto para gravação
	int x=2;
	int flag=5;

	carrega_arquivo(linha, arq_entrada, &x);
	while(x!=0){
		
		if(strstr(linha,".data")!=NULL){
    		flag=1;
    	}    	

    	if(flag==1){

			char y[7];
			mem_data=mem_data/4;
			sprintf(y, "%i", mem_data);
    		char salva[20]=".data ";
    		strcat(salva,y);

    		salva_arquivo(salva,arq_saida,flag);
    		escreve_label(arq_saida,1);
    		flag=2;
    		
    		while(strstr(linha,".text")==NULL){
    			  strcpy(linha,"");
    			  carrega_arquivo(linha,arq_entrada,&x);   			  

    			  if (strchr(linha,':')!=NULL){
    			  	  char *temp=strchr(linha,'.');
    			  	  tratamento4(temp,arq_saida,bin);    			  	 
    			  }
    		}

    		flag=3;
    		char *salva2=".enddata";
    		salva_arquivo(salva2,arq_saida,flag);

    		mem_text=mem_text/4;
			sprintf(y, "%i", mem_text);
    		strcpy(salva,"");
    		strcat(salva,".text ");
    		strcat(salva,y);

    		salva_arquivo(salva,arq_saida,flag);
    		flag=4;

    		escreve_label(arq_saida,2);

    		carrega_arquivo(linha, arq_entrada, &x);
    	}

    	if(flag==4){
    
    		char *linha2=strchr(linha,':');

    		if (linha2!=NULL){    	    			  
	    		
	    		linha2=linha2+1;
	    		limpa_str(linha2);   			  	

   			  	if(strchr(linha2,' ')!=NULL){
   			  		char temp[10];
   			  		int i=0;
   			  		avancar(&i,linha2,temp);   			  		

   			  		int id=identifica_tipo(temp);

		        	if(id==1){
		        		tratamento1(linha2,bin);
		        		salva_arquivo(bin, arq_saida,flag);
		        	}
		        	else if(id==2){
		        		tratamento2(linha2,bin);
		        		salva_arquivo(bin, arq_saida,flag);
		        	}
		        	else if(id==3){
		        		tratamento3(linha2,bin);
		        		salva_arquivo(bin, arq_saida,flag);
		        	}		
		        	else{
		        		tratamento5(linha2,bin,arq_saida);
		        	}
   			  			
   			  	}

   			  	else{
	        		if(strstr(linha2,"syscall")){
	        			tratamento1(linha2,bin);
	        			salva_arquivo(bin,arq_saida,flag);
	        		}

	        	}
   			 
	        }

	        else{

	        	if(strchr(linha,' ')!=NULL){

		        	char temp[10];
   			  		int i=0;
   			  		avancar(&i,linha,temp); ;
		        	int id=identifica_tipo(temp);

		        	if(id==1){
		        		tratamento1(linha,bin);
		        		salva_arquivo(bin, arq_saida,flag);
		        	}
		        	else if(id==2){
		        		tratamento2(linha,bin);
		        		salva_arquivo(bin, arq_saida,flag);
		        	}
		        	else if(id==3){
		        		tratamento3(linha,bin);
		        		salva_arquivo(bin, arq_saida,flag);
		        	}		
		        	else{
		        		tratamento5(linha,bin,arq_saida);
		        	}

	        	}

	        	else{
	        		if(strstr(linha,"syscall")){
	        			tratamento1(linha,bin);
	        			salva_arquivo(bin,arq_saida,flag);
	        		}

	        	}

	        }//end flag==4

    	}//end linha!=NULL
    	
		carrega_arquivo(linha, arq_entrada, &x);
	}//end while

	char *salva2=".endtext";
   	salva_arquivo(salva2,arq_saida,3);

	fclose(arq_saida);
	fclose(arq_entrada);

	delete_l();

	return;
}