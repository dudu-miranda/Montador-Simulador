/*	Aluno:Eduardo Gabriel Reis Miranda
	Matricula:0026495
	Data:31/05/2017
	Sinopse:Arquivo que contém as funções para manipulação dos arquivos passados.
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "Tad_String.h"

FILE *inicia_arquivo(char *NomeArq, char *Modo);
void carrega_arquivo(char *linha, FILE *arq, int *x);
void salva_arquivo(char *bin, FILE *arq,int flag);

/*=================================================================================================================================
													INICIA ARQUIVO
=================================================================================================================================*/
//       :::::::::::::::    :::::::::::::::::::::::::::::::::    :::                  :::    :::::::::  ::::::::  :::    :::::::::::::::::     ::: ::::::::
//          :+:    :+:+:   :+:    :+:   :+:    :+:   :+:      :+: :+:              :+: :+:  :+:    :+::+:    :+: :+:    :+:    :+:    :+:     :+::+:    :+:
//         +:+    :+:+:+  +:+    +:+   +:+          +:+     +:+   +:+            +:+   +:+ +:+    +:++:+    +:+ +:+    +:+    +:+    +:+     +:++:+    +:+
//        +#+    +#+ +:+ +#+    +#+   +#+          +#+    +#++:++#++:          +#++:++#++:+#++:++#: +#+    +:+ +#+    +:+    +#+    +#+     +:++#+    +:+
//       +#+    +#+  +#+#+#    +#+   +#+          +#+    +#+     +#+          +#+     +#++#+    +#++#+    +#+ +#+    +#+    +#+     +#+   +#+ +#+    +#+
//      #+#    #+#   #+#+#    #+#   #+#    #+#   #+#    #+#     #+#          #+#     #+##+#    #+##+#    #+# #+#    #+#    #+#      #+#+#+#  #+#    #+#
// ##############    #####################################     ################     ######    ### ################### ###########    ###     ########
FILE *inicia_arquivo(char *NomeArq, char *Modo){

	FILE *arq;
// Abre um arquivo TEXTO para LEITURA
	arq = fopen(NomeArq, Modo);


	if (arq == NULL){  // Se houve erro na abertura
		printf("Problemas na abertura do arquivo\n");
    	}

	return arq;

}


/*=================================================================================================================================
													CARREGA ARQUIVO
=================================================================================================================================*/
//       ::::::::     :::    ::::::::: ::::::::: ::::::::::::::::::     :::                  :::    :::::::::  ::::::::  :::    :::::::::::::::::     ::: ::::::::
//     :+:    :+:  :+: :+:  :+:    :+::+:    :+::+:      :+:    :+:  :+: :+:              :+: :+:  :+:    :+::+:    :+: :+:    :+:    :+:    :+:     :+::+:    :+:
//    +:+        +:+   +:+ +:+    +:++:+    +:++:+      +:+        +:+   +:+            +:+   +:+ +:+    +:++:+    +:+ +:+    +:+    +:+    +:+     +:++:+    +:+
//   +#+       +#++:++#++:+#++:++#: +#++:++#: +#++:++# :#:       +#++:++#++:          +#++:++#++:+#++:++#: +#+    +:+ +#+    +:+    +#+    +#+     +:++#+    +:+
//  +#+       +#+     +#++#+    +#++#+    +#++#+      +#+   +#+#+#+     +#+          +#+     +#++#+    +#++#+    +#+ +#+    +#+    +#+     +#+   +#+ +#+    +#+
// #+#    #+##+#     #+##+#    #+##+#    #+##+#      #+#    #+##+#     #+#          #+#     #+##+#    #+##+#    #+# #+#    #+#    #+#      #+#+#+#  #+#    #+#
// ######## ###     ######    ######    ##################### ###     ################     ######    ### ################### ###########    ###     ########
void carrega_arquivo(char *linha, FILE *arq, int *x){

	if (!feof(arq)){ //Verifica se o arquivo não está vazio
		strcpy(linha,"");	//esvazia a string pra ter certeza que não haverá lixo de memória
   		fgets(linha,50,arq);  // o 'fgets' lê até 50 caracteres ou até o '\n' e salva na string linha
   		limpa_str(linha);
	}

	else
		*x=0;

return;
}
/*=================================================================================================================================
														SALVA ARQUIVO
=================================================================================================================================*/
//       ::::::::     :::    :::   :::     :::    :::              ::::    ::: ::::::::     :::    :::::::::  ::::::::  :::    :::::::::::::::::     ::: ::::::::
//     :+:    :+:  :+: :+:  :+:   :+:     :+:  :+: :+:            :+:+:   :+::+:    :+:  :+: :+:  :+:    :+::+:    :+: :+:    :+:    :+:    :+:     :+::+:    :+:
//    +:+        +:+   +:+ +:+   +:+     +:+ +:+   +:+           :+:+:+  +:++:+    +:+ +:+   +:+ +:+    +:++:+    +:+ +:+    +:+    +:+    +:+     +:++:+    +:+
//   +#++:++#+++#++:++#++:+#+   +#+     +:++#++:++#++:          +#+ +:+ +#++#+    +:++#++:++#++:+#++:++#: +#+    +:+ +#+    +:+    +#+    +#+     +:++#+    +:+
//         +#++#+     +#++#+    +#+   +#+ +#+     +#+          +#+  +#+#+#+#+    +#++#+     +#++#+    +#++#+    +#+ +#+    +#+    +#+     +#+   +#+ +#+    +#+
// #+#    #+##+#     #+##+#     #+#+#+#  #+#     #+#          #+#   #+#+##+#    #+##+#     #+##+#    #+##+#    #+# #+#    #+#    #+#      #+#+#+#  #+#    #+#
// ######## ###     ################    ###     ################    #### ######## ###     ######    ### ################### ###########    ###     ########
void salva_arquivo(char *bin, FILE *arq,int flag){

// A funcao 'fprintf' devolve o número de bytes gravados 

  	if(flag%2==0){

	  	int j=0;
	  	char temp[5];
	  	temp[4]='\0';

	  	char hexa[9];
	  	hexa[8]='\0';
	  	int k=0;

	  	for (int i = 0; i < 32; ++i){
	  		temp[j]=bin[i];
	  		j++;

	  		if(j==4){
	  			j=0;
	  			hexa[k]=bin_hexa(temp);
	  			k++;
	  		}  		
	  	}

	    fprintf(arq,"%s\n",hexa);    	
    }	

    else{    
    	fprintf(arq,"%s\n",bin);
	}

return;
}