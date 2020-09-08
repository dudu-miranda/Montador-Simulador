/*	Aluno:Eduardo Gabriel Reis Miranda
	Matricula:0026495
	Data:31/05/2017
	Sinopse:Arquivo que contém todas as traduções das instruções normais. Porém quando se trata de uma pseudo instrução ou de uma diretiva
	a tradução e escrita da mesma é diretamente feita aqui.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Tad_Lista.h"
#include "Tad_String.h"
#include "Tad_Arquivo.h"

int get_opcode(char *inst, int tipo,char *x);
void get_func(char *inst,char *x, int *estado);
void get_register(char *reg,char *x);
void get_shamp(char *inst,char *x,int estado);
void get_immediate(char *inst,char *imm);
void get_adress(char *inst,char *adress);
void transformar(char *str);
void tratamento1(char *linha,char *z);
void tratamento2(char *linha,char *z);
void tratamento3(char *linha,char *z);
void tratamento4(char *linha,FILE *arq,char *z);
void tratamento5(char *linha,char *z,FILE *arq_saida);

/*=================================================================================================================================
Função que tem como parâmetro a instrução, o tipo de instrução, e o ponteiro que contém o código
  binário do opcode que será diretamente modificado.
Retorna um inteiro para caso das instruções do tipo I e J, com esse inteiro será decidido o que 
  fazer a partir dele.
=================================================================================================================================*/
//       ######## #####################          ######## #########  ########  ######## ######### ##########
//     ###    ######           ###             ###    ######    ######    ######    ######    ######
//    ###       ###           ###             ###    ######    ######       ###    ######    ######
//   ###       ########      ###             ###    ############ ###       ###    ######    ###########
//  ###   #######           ###             ###    ######       ###       ###    ######    ######
// ###    ######           ###             ###    ######       ###    ######    ######    ######
// ######## ##########    ###    ################## ###        ########  ######## ######### ##########

int get_opcode(char *inst, int tipo,char *x){

	int est=0;

	//Intruções do tipo R
	if (tipo==1){
		x[0]='0';x[1]='0';x[2]='0';x[3]='0';x[4]='0';x[5]='0';
		return 0;
	}

	//Intruções do tipo I
	else if (tipo==2){
	
 	    if(strcmp(inst,"addi")==0){
			x[0]='0';x[1]='0';x[2]='1';x[3]='0';x[4]='0';x[5]='0';
			est=1;
		}  

		else if(strcmp(inst,"slti")==0){
			x[0]='0';x[1]='0';x[2]='1';x[3]='0';x[4]='1';x[5]='0';
			est=1;
		}  

		else if(strcmp(inst,"andi")==0){
			x[0]='0';x[1]='0';x[2]='1';x[3]='1';x[4]='0';x[5]='0';
			est=1;
		}  

		else if(strcmp(inst,"ori")==0){
			x[0]='0';x[1]='0';x[2]='1';x[3]='1';x[4]='0';x[5]='1';
			est=1;
		}  

		else if(strcmp(inst,"xori")==0){
			x[0]='0';x[1]='0';x[2]='1';x[3]='1';x[4]='1';x[5]='0';
			est=1;
		}   

		else if(strcmp(inst,"beq")==0){
			x[0]='0';x[1]='0';x[2]='0';x[3]='1';x[4]='0';x[5]='0';
			est=5;
		}  

		else if(strcmp(inst,"bne")==0){
			x[0]='0';x[1]='0';x[2]='0';x[3]='1';x[4]='0';x[5]='1';
			est=5;
		}  

		else if(strcmp(inst,"addiu")==0){
			x[0]='0';x[1]='0';x[2]='1';x[3]='0';x[4]='0';x[5]='1';
			est=1;
		}  		  

		else if(strcmp(inst,"bltz")==0){
			x[0]='0';x[1]='0';x[2]='0';x[3]='0';x[4]='0';x[5]='1';
			est=2;
		}  

		else if(strcmp(inst,"lui")==0){
			x[0]='0';x[1]='0';x[2]='1';x[3]='1';x[4]='1';x[5]='1';
			est=3;
		}  

		else if(strcmp(inst,"lw")==0){
			x[0]='1';x[1]='0';x[2]='0';x[3]='0';x[4]='1';x[5]='1';
			est=4;
		}  

		else if(strcmp(inst,"sw")==0){
			x[0]='1';x[1]='0';x[2]='1';x[3]='0';x[4]='1';x[5]='1';
			est=4;
		} 

		else if(strcmp(inst,"lb")==0){
			x[0]='1';x[1]='0';x[2]='0';x[3]='0';x[4]='0';x[5]='0';
			est=4;
		}  

		else if(strcmp(inst,"lbu")==0){
			x[0]='1';x[1]='0';x[2]='0';x[3]='1';x[4]='0';x[5]='0';
			est=4;
		}  

		else if(strcmp(inst,"sb")==0){
			x[0]='1';x[1]='0';x[2]='1';x[3]='0';x[4]='0';x[5]='0';
			est=4;
		}
	}

	//Intruções do tipo J
	else if (tipo==3){

	    if(strcmp(inst,"j")==0){
			x[0]='0';x[1]='0';x[2]='0';x[3]='0';x[4]='1';x[5]='0';
			est=2;
		}  

		else if(strcmp(inst,"jal")==0){
			x[0]='0';x[1]='0';x[2]='0';x[3]='0';x[4]='1';x[5]='1';
			est=3;
		}  

	}	

	return est;
}
/*=================================================================================================================================
PEGANDO BINARIO DA FUNCAO
=================================================================================================================================*/
//       ######## #####################          #############    #######    ### ########
//     ###    ######           ###              ###       ###    ########   ######    ###
//    ###       ###           ###              ###       ###    #########  ######
//   ###       ########      ###              ########  ###    ###### ### ######
//  ###   #######           ###              ###       ###    ######  #########
// ###    ######           ###              ###       ###    ######   ########    ###
// ######## ##########    ###    #############        ######## ###    #### ########

/*Função que tem como paramêtro a instrução e o ponteiro que contém o código binário da func,
  que será diretamente modificada de acordo com a função passada.*/
void get_func(char *inst,char *x, int *estado){

	if  ((strcmp(inst,"add"))==0){
		x[0]='1';x[1]='0';x[2]='0';x[3]='0';x[4]='0';x[5]='0';
		*estado = 1;
	}

	else if  ((strcmp(inst,"addu"))==0){
		x[0]='1';x[1]='0';x[2]='0';x[3]='0';x[4]='0';x[5]='1';
		*estado = 1;
	}

	else if  ((strcmp(inst,"and"))==0){
		x[0]='1';x[1]='0';x[2]='0';x[3]='1';x[4]='0';x[5]='0';
		*estado = 1;
	}

	else if  ((strcmp(inst,"nor"))==0){
		x[0]='1';x[1]='0';x[2]='0';x[3]='1';x[4]='1';x[5]='1';
		*estado = 1;
	}

	else if  ((strcmp(inst,"or"))==0){
		x[0]='1';x[1]='0';x[2]='0';x[3]='1';x[4]='0';x[5]='1';
		*estado = 1;
	}

	else if  ((strcmp(inst,"slt"))==0){
		x[0]='1';x[1]='0';x[2]='1';x[3]='0';x[4]='1';x[5]='0';
		*estado = 1;
	}

	else if  ((strcmp(inst,"sub"))==0){
		x[0]='1';x[1]='0';x[2]='0';x[3]='0';x[4]='1';x[5]='0';
		*estado = 1;
	}

	else if  ((strcmp(inst,"subu"))==0){
		x[0]='1';x[1]='0';x[2]='0';x[3]='0';x[4]='1';x[5]='1';
		*estado = 1;
	}

	else if  ((strcmp(inst,"xor"))==0){
		x[0]='1';x[1]='0';x[2]='0';x[3]='1';x[4]='1';x[5]='0';
		*estado = 1;
	}

	// a partir daqui começa o tratamento do rs e rt trocados de lugares porém com 3 registradores ainda 
	
	else if  ((strcmp(inst,"sllv"))==0){
		x[0]='0';x[1]='0';x[2]='0';x[3]='1';x[4]='0';x[5]='0';
		*estado = 2;
	}

	else if  ((strcmp(inst,"srav"))==0){
		x[0]='0';x[1]='0';x[2]='0';x[3]='1';x[4]='1';x[5]='1';
		*estado = 2;
	}

	else if  ((strcmp(inst,"srlv"))==0){
		x[0]='0';x[1]='0';x[2]='0';x[3]='1';x[4]='1';x[5]='0';
		*estado = 2;
	}


	// a partir daqui começa os tratamento que tem shamt

	else if  ((strcmp(inst,"sll"))==0){
		x[0]='0';x[1]='0';x[2]='0';x[3]='0';x[4]='0';x[5]='0';
		*estado = 3;
	}

	else if  ((strcmp(inst,"sra"))==0){
		x[0]='0';x[1]='0';x[2]='0';x[3]='0';x[4]='1';x[5]='1';
		*estado = 3;
	}

	else if  ((strcmp(inst,"srl"))==0){
		x[0]='0';x[1]='0';x[2]='0';x[3]='0';x[4]='1';x[5]='0';
		*estado = 3;
	}

	//a partir daqui começa os tratamentos que só possui um registrador

	else if  ((strcmp(inst,"mfhi"))==0){
		x[0]='0';x[1]='1';x[2]='0';x[3]='0';x[4]='0';x[5]='0';
		*estado = 4;
	}

	else if  ((strcmp(inst,"mflo"))==0){
		x[0]='0';x[1]='1';x[2]='0';x[3]='0';x[4]='1';x[5]='0';
		*estado = 4;
	}

	else if  ((strcmp(inst,"jr"))==0){
		x[0]='0';x[1]='0';x[2]='1';x[3]='0';x[4]='0';x[5]='0';
		*estado = 5;
	}

	//Tratamentos com nenhum registrador
	else if  ((strcmp(inst,"syscall"))==0){
		x[0]='0';x[1]='0';x[2]='1';x[3]='1';x[4]='0';x[5]='0';
		*estado = 6;
	}

	return;
}
/*=================================================================================================================================
REGISTRADOR
Função para achar o código binário dos registradores baseado em seu nome que é passado
  por parametro para a função. Caso nenhum o registrador passado por parâmetro esteja incorreto
  o default será o registrador $0.
=================================================================================================================================*/
//       ######## #####################          ######### ###################################################################
//     ###    ######           ###              ###    ######      ###    ###   ###   ###    ###   ###    ###       ###    ###
//    ###       ###           ###              ###    ######      ###          ###   ###          ###    ###       ###    ###
//   ###       ########      ###              ######### ######## ###          ###   ##########   ###    ########  #########
//  ###   #######           ###              ###    ######      ###   ####   ###          ###   ###    ###       ###    ###
// ###    ######           ###              ###    ######      ###    ###   ###   ###    ###   ###    ###       ###    ###
// ######## ##########    ###    #############    ########################################    ###    #############    ###
void get_register(char *reg,char *x){

	x[0]='0';x[1]='0';x[2]='0';x[3]='0';x[4]='0';


	if(strcmp(reg,"$0")==0 || (strcmp(reg,"$zero"))==0){
			x[0]='0';x[1]='0';x[2]='0';x[3]='0';x[4]='0';
	}

	else if(strcmp(reg,"$1")==0 || (strcmp(reg,"$at"))==0){
			x[0]='0';x[1]='0';x[2]='0';x[3]='0';x[4]='1';
	}

	else if(strcmp(reg,"$2")==0 || (strcmp(reg,"$v0"))==0){
			x[0]='0';x[1]='0';x[2]='0';x[3]='1';x[4]='0';
	}

	else if(strcmp(reg,"$3")==0 || (strcmp(reg,"$v1"))==0){
			x[0]='0';x[1]='0';x[2]='0';x[3]='1';x[4]='1';
	}

	else if(strcmp(reg,"$4")==0 || (strcmp(reg,"$a0"))==0){
			x[0]='0';x[1]='0';x[2]='1';x[3]='0';x[4]='0';
	}

	else if(strcmp(reg,"$5")==0 || (strcmp(reg,"$a1"))==0){
			x[0]='0';x[1]='0';x[2]='1';x[3]='0';x[4]='1';
	}

	else if(strcmp(reg,"$6")==0 || (strcmp(reg,"$a2"))==0){
			x[0]='0';x[1]='0';x[2]='1';x[3]='1';x[4]='0';
	}

	else if(strcmp(reg,"$7")==0 || (strcmp(reg,"$a3"))==0){
			x[0]='0';x[1]='0';x[2]='1';x[3]='1';x[4]='1';
	}

	else if(strcmp(reg,"$8")==0 || (strcmp(reg,"$t0"))==0){
			x[0]='0';x[1]='1';x[2]='0';x[3]='0';x[4]='0';
	}

	else if(strcmp(reg,"$9")==0 || (strcmp(reg,"$t1"))==0){
			x[0]='0';x[1]='1';x[2]='0';x[3]='0';x[4]='1';
	}

	else if(strcmp(reg,"$10")==0 || (strcmp(reg,"$t2"))==0){
			x[0]='0';x[1]='1';x[2]='0';x[3]='1';x[4]='0';
	}

	else if(strcmp(reg,"$11")==0 || (strcmp(reg,"$t3"))==0){
			x[0]='0';x[1]='1';x[2]='0';x[3]='1';x[4]='1';
	}

	else if(strcmp(reg,"$12")==0 || (strcmp(reg,"$t4"))==0){
			x[0]='0';x[1]='1';x[2]='1';x[3]='0';x[4]='0';
	}

	else if(strcmp(reg,"$13")==0 || (strcmp(reg,"$t5"))==0){
			x[0]='0';x[1]='1';x[2]='1';x[3]='0';x[4]='1';
	}

	else if(strcmp(reg,"$14")==0 || (strcmp(reg,"$t6"))==0){
			x[0]='0';x[1]='1';x[2]='1';x[3]='1';x[4]='0';
	}

	else if(strcmp(reg,"$15")==0 || (strcmp(reg,"$t7"))==0){
			x[0]='0';x[1]='1';x[2]='1';x[3]='1';x[4]='1';
	}

	else if(strcmp(reg,"$16")==0 || (strcmp(reg,"$s0"))==0){
			x[0]='1';x[1]='0';x[2]='0';x[3]='0';x[4]='0';
	}

	else if(strcmp(reg,"$17")==0 || (strcmp(reg,"$s1"))==0){
			x[0]='1';x[1]='0';x[2]='0';x[3]='0';x[4]='1';
	}

	else if(strcmp(reg,"$18")==0 || (strcmp(reg,"$s2"))==0){
			x[0]='1';x[1]='0';x[2]='0';x[3]='1';x[4]='0';
	}

	else if(strcmp(reg,"$19")==0 || (strcmp(reg,"$s3"))==0){
			x[0]='1';x[1]='0';x[2]='0';x[3]='1';x[4]='1';
	}

	else if(strcmp(reg,"$20")==0 || (strcmp(reg,"$s4"))==0){
			x[0]='1';x[1]='0';x[2]='1';x[3]='0';x[4]='0';
	}

	else if(strcmp(reg,"$21")==0 || (strcmp(reg,"$s5"))==0){
			x[0]='1';x[1]='0';x[2]='1';x[3]='0';x[4]='1';
	}

	else if(strcmp(reg,"$22")==0 || (strcmp(reg,"$s6"))==0){
			x[0]='1';x[1]='0';x[2]='1';x[3]='1';x[4]='0';
	}

	else if(strcmp(reg,"$23")==0 || (strcmp(reg,"$s7"))==0){
			x[0]='1';x[1]='0';x[2]='1';x[3]='1';x[4]='1';
	}

	else if(strcmp(reg,"$24")==0 || (strcmp(reg,"$t8"))==0){
			x[0]='1';x[1]='1';x[2]='0';x[3]='0';x[4]='0';
	}

	else if(strcmp(reg,"$25")==0 || (strcmp(reg,"$t9"))==0){
			x[0]='1';x[1]='1';x[2]='0';x[3]='0';x[4]='1';
	}

	else if(strcmp(reg,"$26")==0 || (strcmp(reg,"$k0"))==0){
			x[0]='1';x[1]='1';x[2]='0';x[3]='1';x[4]='0';
	}

	else if(strcmp(reg,"$27")==0 || (strcmp(reg,"$k1"))==0){
			x[0]='1';x[1]='1';x[2]='0';x[3]='1';x[4]='1';
	}

	else if(strcmp(reg,"$28")==0 || (strcmp(reg,"$gp"))==0){
			x[0]='1';x[1]='1';x[2]='1';x[3]='0';x[4]='0';
	}

	else if(strcmp(reg,"$29")==0 || (strcmp(reg,"$sp"))==0){
			x[0]='1';x[1]='1';x[2]='1';x[3]='0';x[4]='1';
	}

	else if(strcmp(reg,"$30")==0 || (strcmp(reg,"$fp"))==0){
			x[0]='1';x[1]='1';x[2]='1';x[3]='1';x[4]='0';
	}

	else if(strcmp(reg,"$31")==0 || (strcmp(reg,"$ra"))==0){
			x[0]='1';x[1]='1';x[2]='1';x[3]='1';x[4]='1';
	}

	return;
}
/*=================================================================================================================================
Função que tem como parâmetro a instrução e o ponteiro que contém o binário do shamp e um inteiro para decisão
  de como proceder para conseguir o shamp.
=================================================================================================================================*/
//       ######## #####################          ######## ###    ###    ###      ###   ###  #########
//     ###    ######           ###             ###    ######    ###  ### ###   ##### ##### ###    ###
//    ###       ###           ###             ###       ###    ### ###   ### ### ##### ######    ###
//   ###       ########      ###             ##################################  ###  ############
//  ###   #######           ###                    ######    ######     ######       ######
// ###    ######           ###             ###    ######    ######     ######       ######
// ######## ##########    ###    ################## ###    ######     ######       ######

void get_shamp(char *inst,char *x,int estado){

	if(estado!=3){
		x[0]='0';x[1]='0';x[2]='0';x[3]='0';x[4]='0';
	}

	else{

		//tratamento para numero decimal e labels
		if(identifica_hex(inst)==1){

			//tratamento para decimal
			if(identifica_lab(inst)==0){
				long int temp=strtol(inst,NULL,10);

				if(temp<32 && temp>=0){
				decimal_binario(temp,x,5);
				return;
				}
			}	

			//tratamento para label
			else{
				int temp=retorna_item(inst);

				if(temp<32 && temp>=0){
				decimal_binario(temp,x,5);
				return;
				}
			}

			get_shamp(inst,x,3);	
		}

		//tratamento para hexadecimal
		else{

			long int temp2=strtol(inst,NULL,16);

			if (temp2<31 && temp2>=0){
				decimal_binario(temp2,x,5);
				return;
			}

			get_shamp(inst,x,3);
		}

	}

	return;
}
/*=================================================================================================================================
Função que tem como parâmetro a instrução e o ponteiro que contém o binário do imediato.
=================================================================================================================================*/
//       ######## #####################          ###########  ###   ###    ###   ###  ##############################    ########################
//     ###    ######           ###                  ###     ##### #####  ##### ##### ###       ###    ###   ###      ### ###  ###    ###
//    ###       ###           ###                  ###    ### ##### ###### ##### ######       ###    ###   ###     ###   ### ###    ###
//   ###       ########      ###                  ###    ###  ###  ######  ###  ###########  ###    ###   ###    ##############    ########
//  ###   #######           ###                  ###    ###       ######       ######       ###    ###   ###    ###     ######    ###
// ###    ######           ###                  ###    ###       ######       ######       ###    ###   ###    ###     ######    ###
// ######## ##########    ###    ########################       ######       ####################################     ######    ##########
void get_immediate(char *inst,char *imm){

	//tratamento para numero decimal e label
		if(identifica_hex(inst)==1){

			//tratamento para decimal
			if(identifica_lab(inst)==0){
				long int temp=strtol(inst,NULL,10);

				if(temp<65535 && temp>=0){
				decimal_binario(temp,imm,16);
				return;
				}	
			}

			//tratamento para label
			else{
				int temp=retorna_item(inst);

				if(temp<65535 && temp>=0){
				decimal_binario(temp,imm,16);
				return;
				}

			}
		}

		//tratamento para hexadecimal
		else{

			long int temp2=strtol(inst,NULL,16);

			if (temp2<65535 && temp2>=0){
				decimal_binario(temp2,imm,16);
				return;
			}

		}

	return;
}
/*=================================================================================================================================
Função que tem como parâmetro a instrução e o ponteiro que contém o binário do endereço.
=================================================================================================================================*/
//       ######## #####################              ###    ######### ######### ##################  ########
//     ###    ######           ###                ### ###  ###    ######    ######      ###    ######    ###
//    ###       ###           ###               ###   ### ###    ######    ######      ###       ###
//   ###       ########      ###              ##############    ############ ######## ####################
//  ###   #######           ###              ###     ######    ######    ######             ###       ###
// ###    ######           ###              ###     ######    ######    ######      ###    ######    ###
// ######## ##########    ###    #############     ############ ###    #####################  ########
void get_adress(char *inst,char *adress){

	//tratamento para numero decimal e label
		if(identifica_hex(inst)==1){

			//tratamento para decimal
			if(identifica_lab(inst)==0){
				long int temp=strtol(inst,NULL,10);

				if(temp<67108864 && temp>=0){
				decimal_binario(temp,adress,26);
				return;
				}	
			}

			//tratamento para label
			else{
				int temp=retorna_item(inst);

				if(temp<67108864 && temp>=0){
				decimal_binario(temp,adress,26);
				return;
				}	

			}
		}

		//tratamento para hexadecimal
		else{

			long int temp2=strtol(inst,NULL,16);

			if (temp2<67108864 && temp2>=0){
				decimal_binario(temp2,adress,26);
				return;
			}

		}

	return;
}

/*=================================================================================================================================
TRATAMENTO DE FUNCAO TIPO R
=================================================================================================================================*/
//   ####################     #################      ###   ###  ##############    ######################   ###
//      ###    ###    ###  ### ###  ###  ### ###   ##### ##### ###       #####   ###    ###   ###    ########
//     ###    ###    ### ###   ### ### ###   ### ### ##### ######       ######  ###    ###   ###    ###  ###
//    ###    ######### ############################  ###  ###########  ### ### ###    ###   ###    ###  ###
//   ###    ###    ######     #########     ######       ######       ###  ######    ###   ###    ###  ###
//  ###    ###    ######     #########     ######       ######       ###   #####    ###   ###    ###  ###
// ###    ###    ######     #########     ######       ################    ####    ###    ######## #######

/*Função que tem como parâmetro a linha lida do arquivo e o ponteiro a ser modificado que conterá a word
  que o comando passado representa.*/
void tratamento1(char *linha,char *z){

	char x[10];//Variavel temporaria que guardará tudo o que precisará ser transformado em binário
	//cada variavel é respectiva a sua parte no binário
	char opcode[6]; char r1[5];     char r2[5];
	//mesmo acima
	char r3[5];     char shamp[5];  char funct[6];
	//variavel que definirá qual tipo de tratamento deverá ser feito para leitura e tratamento dos dados
	int estado;
	//variavel que indicará a posição atual da linha
	int i=0;

	avancar(&i,linha,x);
	get_opcode(x, 1, opcode);
	get_func(x,funct, &estado);

	if (estado==1){	
		avancar(&i,linha,x);	
		get_register(x,r1);
		
		avancar(&i,linha,x);
		get_register(x,r2);

		avancar(&i,linha,x);
		get_register(x,r3);

		get_shamp(x,shamp,1);
	}	

	else if (estado==2){
		avancar(&i,linha,x);
		get_register(x,r1);
		
		avancar(&i,linha,x);
		get_register(x,r3);

		avancar(&i,linha,x);
		get_register(x,r2);

		get_shamp(x,shamp,2);
	}

	else if (estado==3){
		avancar(&i,linha,x);
		get_register(x,r1);
		
		avancar(&i,linha,x);
		get_register(x,r3);
		get_register("$0",r2);

		avancar(&i,linha,x);

		get_shamp(x,shamp,3);
	}

	else if (estado==4){
		avancar(&i,linha,x);
		get_register(x,r1);
		
		get_register("$0",r2);
		get_register("$0",r3);

		get_shamp(x,shamp,4);
	}

	else if (estado==5){
		avancar(&i,linha,x);
		get_register(x,r2);
		
		get_register("$0",r1);
		get_register("$0",r3);

		get_shamp(x,shamp,5);
	}

	else if (estado==6){
		get_register("$0",r1);
		get_register("$0",r2);		
		get_register("$0",r3);

		get_shamp(x,shamp,6);
	}

	juntar1(opcode,r2,r3,r1,shamp,funct,z);
	z[32]='\0';

	return;

}

/*=================================================================================================================================
TRATAMENTO DE FUNCAO TIPO I
=================================================================================================================================*/
//   ####################     #################      ###   ###  ##############    ######################  ########
//      ###    ###    ###  ### ###  ###  ### ###   ##### ##### ###       #####   ###    ###   ###    ######    ###
//     ###    ###    ### ###   ### ### ###   ### ### ##### ######       ######  ###    ###   ###    ###      ###
//    ###    ######### ############################  ###  ###########  ### ### ###    ###   ###    ###    ###
//   ###    ###    ######     #########     ######       ######       ###  ######    ###   ###    ###  ###
//  ###    ###    ######     #########     ######       ######       ###   #####    ###   ###    ### ###
// ###    ###    ######     #########     ######       ################    ####    ###    ######## ##########
void tratamento2(char *linha,char *z){

	char x[10];//Variavel temporaria que guardará tudo o que precisará ser transformado em binário
	//cada variavel é respectiva a sua parte no binário
	char opcode[6]; char r1[5];     char r2[5];
	//variavel contendo binario do imediato
	char immediate[16];
	//variavel que definirá qual tipo de tratamento deverá ser feito para leitura e tratamento dos dados
	int estado;
	//variavel que indicará a posição atual da linha
	int i=0;

	avancar(&i,linha,x);
	estado=get_opcode(x,2,opcode);

	if (estado==1){
		avancar(&i,linha,x);
		get_register(x,r2);
		
		avancar(&i,linha,x);
		get_register(x,r1);

		avancar(&i,linha,x);
		get_immediate(x,immediate);
	}	

	else if (estado==2){
		avancar(&i,linha,x);
		get_register(x,r1);
		
		get_register("$0",r2);

		avancar(&i,linha,x);
		get_immediate(x,immediate);
	}	

	else if (estado==3){
		avancar(&i,linha,x);
		get_register(x,r2);
		
		get_register("$0",r1);

		avancar(&i,linha,x);
		get_immediate(x,immediate);
	}

	else if (estado==4){
		avancar(&i,linha,x);
		get_register(x,r2);

		//conterei o imediato e o registrador
		//exemplo: 4($v0)
		avancar(&i,linha,x);

		char temp[20];
		for(i=0; x[i]!='('; i++){
			temp[i]=x[i];
		}
		temp[i]='\0';

		get_immediate(temp,immediate);
		
		i++;
		int j;
		for(j=0; x[i]!=')'; j++){
			temp[j]=x[i];
			i++;
		}
		temp[j]='\0';

		get_register(temp,r1);		
	}

	if (estado==5){
		avancar(&i,linha,x);
		get_register(x,r1);
		
		avancar(&i,linha,x);
		get_register(x,r2);

		avancar(&i,linha,x);
		get_immediate(x,immediate);
	}

	juntar2(opcode,r1,r2,immediate,z);

	return;
}

/*=================================================================================================================================
TRATAMENTO DE FUNCAO TIPO J
=================================================================================================================================*/
//   ####################     #################      ###   ###  ##############    ######################  ########
//      ###    ###    ###  ### ###  ###  ### ###   ##### ##### ###       #####   ###    ###   ###    ######    ###
//     ###    ###    ### ###   ### ### ###   ### ### ##### ######       ######  ###    ###   ###    ###       ###
//    ###    ######### ############################  ###  ###########  ### ### ###    ###   ###    ###    #####
//   ###    ###    ######     #########     ######       ######       ###  ######    ###   ###    ###       ###
//  ###    ###    ######     #########     ######       ######       ###   #####    ###   ###    ######    ###
// ###    ###    ######     #########     ######       ################    ####    ###    ########  ########
void tratamento3(char *linha,char *z){

	char x[12];//Variavel temporaria que guardará tudo o que precisará ser transformado em binário
	//cada variavel é respectiva a sua parte no binário
	char opcode[6]; char adress[26];
	//variavel que indicará a posição atual da linha
	int i=0;

	avancar(&i,linha,x);
	get_opcode(x,3,opcode);

	avancar(&i,linha,x);
	get_adress(x,adress);	

	juntar3(opcode,adress,z);

	return;
}

void transformar(char *str){

	str=strchr(str,'\\');

	if(str[1]=='n'){
		str[0]='\n';
		for(int i=1;i<strlen(str);i++){
			str[i]=str[i+1];
		}
	}

	else if (str[1]=='0'){
		str[0]='\0';
		for(int i=1;i<strlen(str);i++){
			str[i]=str[i+1];
		}
	}

	else if (str[1]=='r'){
		str[0]='\r';
		for(int i=1;i<strlen(str);i++){
			str[i]=str[i+1];
		}
	}
	
	else if (str[1]=='\\'){
		str[0]='\\';
		for(int i=1;i<strlen(str);i++){
			str[i]=str[i+1];
		}
	}

}


//   ::::::::::::::::::::     :::::::::::::::::      :::   :::  ::::::::::::::    ::::::::::::::::::::::     :::
//      :+:    :+:    :+:  :+: :+:  :+:  :+: :+:   :+:+: :+:+: :+:       :+:+:   :+:    :+:   :+:    :+:   :+:
//     +:+    +:+    +:+ +:+   +:+ +:+ +:+   +:+ +:+ +:+:+ +:++:+       :+:+:+  +:+    +:+   +:+    +:+  +:+ +:+
//    +#+    +#++:++#: +#++:++#++:+#++#++:++#++:+#+  +:+  +#++#++:++#  +#+ +:+ +#+    +#+   +#+    +:+ +#+  +:+
//   +#+    +#+    +#++#+     +#++#++#+     +#++#+       +#++#+       +#+  +#+#+#    +#+   +#+    +#++#+#+#+#+#+
//  #+#    #+#    #+##+#     #+##+##+#     #+##+#       #+##+#       #+#   #+#+#    #+#   #+#    #+#      #+#
// ###    ###    ######     #########     ######       ################    ####    ###    ########       ###

void tratamento4(char *linha,FILE *arq,char *z){

	if(strstr(linha,".asciiz")!=NULL){

		linha=strchr(linha,'"');
		linha=linha+1;
		int i=0;

		int x;
		int aux=31;
		char v[9]; v[8]='\0';

		linha[strlen(linha)-1]='\0';
		linha[strlen(linha)+1]='"';


		while(linha[i+1]!='"'){

			if (linha[i]=='\\'){
				transformar(linha);
			}

			x=linha[i];

			i++;

			decimal_binario(x,v,8);

			for (int j = 7; j != -1;j--){
				z[aux]=v[j];
				aux--;				
			}			

			if(aux==-1){
				aux=31;
				salva_arquivo(z,arq,2);
			}
		}

		if (aux!=31){

			while(aux!=-1){				
				z[aux]='0';
				aux--;
			}

			salva_arquivo(z,arq,2);
		}

	}

	else if(strstr(linha,".byte")!=NULL){
		//começando big end vai colocando os bytes numeros que o usuario passará multiplo x4


		linha=strchr(linha,' ');
		linha=linha+1;
		int i=0;


		char x[10]; x[9]='\0';
		char v[9]; v[8]='\0';
		int aux=31;


		while(linha[i]!='\0'){
			
			avancar(&i,linha,x);
			//tratamento para decimal
			if(identifica_hex(x)==1){
				decimal_binario(atoi(x),v,8);
			}

			//tratamento para hexadecimal
			else{
				long int temp2=strtol(x,NULL,16);
				decimal_binario(temp2,v,8);
			}

			for (int j = 7; j !=-1; j--){
				z[aux]=v[j];
				aux--;				
			}			

			if(aux==-1){
				aux=31;
				salva_arquivo(z,arq,2);
			}

		}

		if (aux!=31){

			while(aux!=-1){				
				z[aux]='0';
				aux--;
			}

			salva_arquivo(z,arq,2);
		}

	}

	else if(strstr(linha,".word")!=NULL){
		//vai guardando os numeros que o usuario deseja em 32 bits

		char x[10]; x[9]='\0';
		limpa_str(linha);
		linha=strchr(linha,' ');
		linha=linha+1;
		int i=0;
			
		while(linha[i-1]!='\0'){
			avancar(&i,linha,x);

			if(identifica_hex(x)==1){
				decimal_binario(atoi(x),z,32);
			}

			//tratamento para hexadecimal
			else{
				long int temp2=strtol(x,NULL,16);
				decimal_binario(temp2,z,32);
			}

			salva_arquivo(z,arq,2);						
		}			
	}

	else if(strstr(linha,".space")!=NULL){
		//vai guardar N bytes que o usuario mandar e preencher tudo com 0
		char *x=strchr(linha,' ');
			x=x+1;

		int a=atoi(x);

		strcpy(z,"00000000000000000000000000000000\0");

		int i;
		for (i=0; i<a; ++i){
			if(i%4==0){
				salva_arquivo(z,arq,2);
			}
		}		

	}	

	return;

}

//   ::::::::::::::::::::     :::::::::::::::::      :::   :::  ::::::::::::::    :::::::::::::::::::::: ::::::::::
//      :+:    :+:    :+:  :+: :+:  :+:  :+: :+:   :+:+: :+:+: :+:       :+:+:   :+:    :+:   :+:    :+::+:    :+:
//     +:+    +:+    +:+ +:+   +:+ +:+ +:+   +:+ +:+ +:+:+ +:++:+       :+:+:+  +:+    +:+   +:+    +:++:+
//    +#+    +#++:++#: +#++:++#++:+#++#++:++#++:+#+  +:+  +#++#++:++#  +#+ +:+ +#+    +#+   +#+    +:++#++:++#+
//   +#+    +#+    +#++#+     +#++#++#+     +#++#+       +#++#+       +#+  +#+#+#    +#+   +#+    +#+       +#+
//  #+#    #+#    #+##+#     #+##+##+#     #+##+#       #+##+#       #+#   #+#+#    #+#   #+#    #+##+#    #+#
// ###    ###    ######     #########     ######       ################    ####    ###    ########  ########

void tratamento5(char *linha,char *z,FILE *arq_saida){

	int i=0;
	
	//mov $rt, $rs 	addi $rt, $rs, 0 
	
	if(strstr(linha,"mov")!=NULL){
		char inst[20]="";
		char x[10]=""; 
		char x2[10]="";
		avancar(&i,linha,x);
		avancar(&i,linha,x);
		avancar(&i,linha,x2);	
		
		strcat(inst,"addi ");
		strcat(inst,x);
		strcat(inst," ,");
		strcat(inst,x2);
		strcat(inst," ,");
		strcat(inst,"0\0");

		tratamento2(inst,z);

		salva_arquivo(z,arq_saida,2);
	}

	//li $rs, big     lui $rs, upper( big )
    //                ori $rs, $rs, lower( big )

	else if(strstr(linha,"li")!=NULL){
		char inst[20]="";
		char x[10]=""; 
		char x2[10]="";
		avancar(&i,linha,x);
		avancar(&i,linha,x);
		avancar(&i,linha,x2);	
		
		//Parte do codigo que pega o numero equivalente aos 16 bits mais significativos do numero passado
		char temp[33]; temp[32]='\0';
		decimal_binario(atoi(x2),temp,32);

		char temp2[17];
		temp2[16]='\0';

		for (int i = 0; i<16; ++i){
			temp2[i]=temp[i];
		}

		long int num=strtol(temp2,NULL,2);
		sprintf(x2,"%li",num);

		strcat(inst,"lui ");
		strcat(inst,"$0");		
		strcat(inst," ,");
		strcat(inst,x);		
		strcat(inst," ,");
		strcat(inst,x2);
		
		tratamento2(inst,z);
		salva_arquivo(z,arq_saida,2);
		strcpy(inst,"");

		//Parte que pega o binario dos 16 bits menos significativos
		for (int i = 0; i<16; ++i){
			temp2[i]=temp[i+16];
		}
		
		num=strtol(temp2,NULL,2);
		sprintf(x2,"%li",num);

		strcat(inst,"ori ");
		strcat(inst,x);		
		strcat(inst," ,");
		strcat(inst,x);		
		strcat(inst," ,");
		strcat(inst,x2);

		tratamento2(inst,z);
		salva_arquivo(z,arq_saida,2);		
	}

	//la $rs, big     lui $rs, upper( big )
    //                ori $rs, $rs, lower( big )

	else if(strstr(linha,"la")!=NULL){
		char inst[20]="";
		char x[10]=""; 
		char x2[10]="";
		avancar(&i,linha,x);
		avancar(&i,linha,x);
		avancar(&i,linha,x2);	
		
		//Parte do codigo que pega o numero equivalente aos 16 bits mais significativos do numero passado
		char temp[33]; temp[32]='\0';
		decimal_binario(retorna_item(x2),temp,32);

		char temp2[17];
		temp2[16]='\0';

		for (int i = 0; i<16; ++i){
			temp2[i]=temp[i];
		}

		long int num=strtol(temp2,NULL,2);
		sprintf(x2,"%li",num);

		strcat(inst,"lui ");
		strcat(inst,"$0");		
		strcat(inst," ,");
		strcat(inst,x);		
		strcat(inst," ,");
		strcat(inst,x2);
		
		tratamento2(inst,z);
		salva_arquivo(z,arq_saida,2);
		strcpy(inst,"");

		//Parte que pega o binario dos 16 bits menos significativos
		for (int i = 0; i<16; ++i){
			temp2[i]=temp[i+16];
		}
		
		num=strtol(temp2,NULL,2);
		sprintf(x2,"%li",num);

		strcat(inst,"ori ");
		strcat(inst,x);		
		strcat(inst," ,");
		strcat(inst,x);		
		strcat(inst," ,");
		strcat(inst,x2);

		tratamento2(inst,z);
		salva_arquivo(z,arq_saida,2);
	}

	//bge $rt, $rs, LABEL ->slt $t0, $rt, $rs
	//						beq $t0, $zero, LABEL

	else if(strstr(linha,"bge")!=NULL){		
		char inst[20]="";
		char x[10]=""; 
		char x2[10]="";
		char x3[10]="";

		avancar(&i,linha,x);
		avancar(&i,linha,x);
		avancar(&i,linha,x2);
		avancar(&i,linha,x3);

		strcat(inst,"slt ");
		strcat(inst,"$t0, ");
		strcat(inst,x);
		strcat(inst,", ");
		strcat(inst,x2);

		tratamento1(inst,z);
		salva_arquivo(z,arq_saida,2);
		strcpy(inst,"");

		strcat(inst,"beq ");
		strcat(inst,"$t0, ");
		strcat(inst,"$zero, ");
		strcat(inst,x3);

		tratamento2(inst,z);
		salva_arquivo(z,arq_saida,2);
	}

	//bgt $rt, $rs, LABEL ->slt $t0, $rs, $rt
	//						bne $t0, $zero, LABEL

	else if(strstr(linha,"bgt")!=NULL){
		char inst[20]="";
		char x[10]=""; 
		char x2[10]="";
		char x3[10]="";

		avancar(&i,linha,x);
		avancar(&i,linha,x);
		avancar(&i,linha,x2);
		avancar(&i,linha,x3);

		strcat(inst,"slt ");
		strcat(inst,"$t0, ");
		strcat(inst,x2);
		strcat(inst,", ");
		strcat(inst,x);

		tratamento1(inst,z);
		salva_arquivo(z,arq_saida,2);
		strcpy(inst,"");

		strcat(inst,"bne ");
		strcat(inst,"$t0, ");
		strcat(inst,"$zero, ");
		strcat(inst,x3);

		tratamento2(inst,z);
		salva_arquivo(z,arq_saida,2);		
	}

	//ble $rt, $rs, LABEL ->slt $t0, $rs, $rt
	//						beq $t0, $zero, LABEL 
	else if(strstr(linha,"ble")!=NULL){
		char inst[20]="";
		char x[10]=""; 
		char x2[10]="";
		char x3[10]="";

		avancar(&i,linha,x);
		avancar(&i,linha,x);
		avancar(&i,linha,x2);
		avancar(&i,linha,x3);

		strcat(inst,"slt ");
		strcat(inst,"$t0, ");
		strcat(inst,x2);
		strcat(inst,", ");
		strcat(inst,x);

		tratamento1(inst,z);
		salva_arquivo(z,arq_saida,2);
		strcpy(inst,"");

		strcat(inst,"beq ");
		strcat(inst,"$t0, ");
		strcat(inst,"$zero, ");
		strcat(inst,x3);

		tratamento2(inst,z);
		salva_arquivo(z,arq_saida,2);				
	}

	//blt $rt, $rs, LABEL ->slt $t0, $rt, $rs
	//						bne $t0, $zero, LABEL
	else if(strstr(linha,"blt")!=NULL){
		char inst[20]="";
		char x[10]=""; 
		char x2[10]="";
		char x3[10]="";

		avancar(&i,linha,x);
		avancar(&i,linha,x);
		avancar(&i,linha,x2);
		avancar(&i,linha,x3);

		strcat(inst,"slt ");
		strcat(inst,"$t0, ");
		strcat(inst,x);
		strcat(inst,", ");
		strcat(inst,x2);

		tratamento1(inst,z);
		salva_arquivo(z,arq_saida,2);
		strcpy(inst,"");

		strcat(inst,"bne ");
		strcat(inst,"$t0, ");
		strcat(inst,"$zero, ");
		strcat(inst,x3);

		tratamento2(inst,z);
		salva_arquivo(z,arq_saida,2);				
	}	

	return;
}