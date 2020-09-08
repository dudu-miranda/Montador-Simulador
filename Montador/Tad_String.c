/*  Aluno:Eduardo Gabriel Reis Miranda
    Matricula:0026495
    Data:31/05/2017
    Sinopse:Arquivo que contém funções que manipulam strings para facilitar os tratamentos que serão feitos na tradução e na
    parte de ler os labels.
*/

#include <string.h>
#include <ctype.h>

void avancar(int *i,char *linha,char *x);
void apaga_comentario(char *x);
void apaga_espaco(char *str);
void tira_ident(char *str);
void limpa_str(char *str);
void juntar1(char *opcode, char *r1, char *r2, char *r3, char *shamp, char *funct,char *x);
void juntar2(char *opcode, char *r1, char *r2, char *immediate,char *x);
void juntar3(char *opcode,char *adress,char *x);

int identifica_hex(char *inst);
int identifica_lab(char *inst);
void decimal_binario(int num, char *vet,int tam);
char bin_hexa(char *v);
int identifica_tipo(char *inst);

/*=================================================================================================================================
										ANVANCA NA LINHA PARA COLETA DE INFORMACOES
=================================================================================================================================*/
//           ###    ###     ###    ###    ####    ### ########     ###    #########
//        ### ###  ###     ###  ### ###  #####   ######    ###  ### ###  ###    ###
//      ###   ### ###     ### ###   ### ######  ######        ###   ### ###    ###
//    ##############     ################# ### ######       ####################
//   ###     ### ###   ### ###     ######  #########       ###     ######    ###
//  ###     ###  #######  ###     ######   ########    ######     ######    ###
// ###     ###    ###    ###     ######    #### ######## ###     ######    ###

void avancar(int *i,char *linha,char *x){

	int cont=0;

	while (linha[*i]!=' ' && linha[*i]!='\0'){

		if(linha[*i]!=' ' && linha[*i]!=','){
			x[cont]=linha[*i];
			cont++;
		}

		*i=*i+1;;
	}

	//cont++;
	x[cont]='\0';
	*i=*i+1;	

	return;
}

//           :::    :::::::::    :::     ::::::::     :::              :::::::::::::::::: :::::::::    :::     ::::::::  ::::::::
//        :+: :+:  :+:    :+: :+: :+:  :+:    :+:  :+: :+:            :+:      :+:    :+::+:    :+: :+: :+:  :+:    :+::+:    :+:
//      +:+   +:+ +:+    +:++:+   +:+ +:+        +:+   +:+           +:+      +:+       +:+    +:++:+   +:+ +:+       +:+    +:+
//    +#++:++#++:+#++:++#++#++:++#++::#:       +#++:++#++:          +#++:++# +#++:++#+++#++:++#++#++:++#++:+#+       +#+    +:+
//   +#+     +#++#+      +#+     +#++#+   +#+#+#+     +#+          +#+             +#++#+      +#+     +#++#+       +#+    +#+
//  #+#     #+##+#      #+#     #+##+#    #+##+#     #+#          #+#      #+#    #+##+#      #+#     #+##+#    #+##+#    #+#
// ###     ######      ###     ### ######## ###     ############################### ###      ###     ### ########  ########

/*Função para apagar os espaços extras que possam ser colocados.*/
void apaga_espaco(char *str){

    //Apaga espaços duplos
    for(int x = 0; str[x] != '\0'; x++)
    {
        while(str[x] == ' ' && str[x+1] == ' ')
        {
            for(int y = x; str[y] != '\0'; y++)
            {
                str[y] = str[y + 1];
            }
        }
    }

    //Apaga espaços anteriores a virgulas
    for(int x = 0; str[x] != '\0'; x++)
    {
        while(str[x] == ' ' && str[x+1] == ',')
        {
            for(int y = x; str[y] != '\0'; y++)
            {
                str[y] = str[y + 1];
            }
        }
    }

    //Caso tenha um espaço na primeira posição ele e apagado
    if (str[0]==' '){
        int i;
        for (i = 0; i < strlen(str)-1; ++i){
            str[i]=str[i+1];
        }
        str[i]='\0';
    }    

    //Caso tenha um espaço na ultima posição ele e apagado
    if (str[strlen(str)-1]==' '){
        str[strlen(str)-1]='\0';
    }

    //Coloca um espaço caso tenha uma virgula e não tenha um espaço após ela
    for(int x = 0; str[x] != '\0'; x++)
    {
        if(str[x] == ',' && str[x+1] != ' ')
        {
            int y;
            for(y = strlen(str)-1; y!=x; y--)
            {
                str[y+1] = str[y];
            }
            str[y+1]=' ';
        }
    }

    return ;
}

//           :::    :::::::::    :::     ::::::::     :::              ::::::::  ::::::::   :::   :::  ::::::::::::::    :::::::::::::::::    ::::::::: :::::::::::::::::::
//        :+: :+:  :+:    :+: :+: :+:  :+:    :+:  :+: :+:           :+:    :+::+:    :+: :+:+: :+:+: :+:       :+:+:   :+:    :+:  :+: :+:  :+:    :+:    :+:   :+:    :+:
//      +:+   +:+ +:+    +:++:+   +:+ +:+        +:+   +:+          +:+       +:+    +:++:+ +:+:+ +:++:+       :+:+:+  +:+    +:+ +:+   +:+ +:+    +:+    +:+   +:+    +:+
//    +#++:++#++:+#++:++#++#++:++#++::#:       +#++:++#++:         +#+       +#+    +:++#+  +:+  +#++#++:++#  +#+ +:+ +#+    +#++#++:++#++:+#++:++#:     +#+   +#+    +:+
//   +#+     +#++#+      +#+     +#++#+   +#+#+#+     +#+         +#+       +#+    +#++#+       +#++#+       +#+  +#+#+#    +#++#+     +#++#+    +#+    +#+   +#+    +#+
//  #+#     #+##+#      #+#     #+##+#    #+##+#     #+#         #+#    #+##+#    #+##+#       #+##+#       #+#   #+#+#    #+##+#     #+##+#    #+#    #+#   #+#    #+#
// ###     ######      ###     ### ######## ###     #####################  ######## ###       ################    ####    ######     ######    ######################

/*Função que ignorará todos os cometários facilitando assim a leitura dos dados*/
void apaga_comentario(char *x){

	for (int i = 0; i < strlen(x); ++i){

		if (x[i]=='#'){
			x[i]='\0';
			return;
		}
	}

	return;

}

//   :::::::::::::::::::::::::::::::     :::              :::::::::::::::::::: ::::::::::::::    ::::::::::::::
//      :+:        :+:    :+:    :+:  :+: :+:                :+:    :+:    :+::+:       :+:+:   :+:    :+:
//     +:+        +:+    +:+    +:+ +:+   +:+               +:+    +:+    +:++:+       :+:+:+  +:+    +:+
//    +#+        +#+    +#++:++#: +#++:++#++:              +#+    +#+    +:++#++:++#  +#+ +:+ +#+    +#+
//   +#+        +#+    +#+    +#++#+     +#+              +#+    +#+    +#++#+       +#+  +#+#+#    +#+
//  #+#        #+#    #+#    #+##+#     #+#              #+#    #+#    #+##+#       #+#   #+#+#    #+#
// ###    ##############    ######     ################################# #############    ####    ###

/*Função para apagar determinados tipos de identação que possam ser colocadas.*/
void tira_ident(char *str){

    char *temp;

    do{
        temp=strchr(str,'\t');

        if(temp!=NULL){
            
            int i;
            for (i = 0; i < strlen(temp)-1; ++i){
                temp[i]=temp[i+1];    
            }
            temp[i]='\0';
        }
    }while(temp!=NULL); 

    temp=strchr(str,'\r');
    if(temp!=NULL){
        temp[0]='\0';
    }   

    temp=strchr(str,'\n');
    if(temp!=NULL){
        temp[0]='\0';
    } 

    return;
}

//       :::       :::::::::::  :::   :::  :::::::::    :::              ::::::::::::::::::::::::::::
//      :+:           :+:     :+:+: :+:+: :+:    :+: :+: :+:           :+:    :+:   :+:    :+:    :+:
//     +:+           +:+    +:+ +:+:+ +:++:+    +:++:+   +:+          +:+          +:+    +:+    +:+
//    +#+           +#+    +#+  +:+  +#++#++:++#++#++:++#++:         +#++:++#++   +#+    +#++:++#:
//   +#+           +#+    +#+       +#++#+      +#+     +#+                +#+   +#+    +#+    +#+
//  #+#           #+#    #+#       #+##+#      #+#     #+#         #+#    #+#   #+#    #+#    #+#
// ########################       ######      ###     #####################    ###    ###    ###

/*Função feita para ser somente feita uma chamada para organização de strings.*/
void limpa_str(char *str){
	apaga_comentario(str);
	tira_ident(str);
	apaga_espaco(str);
	//fazer a função de identar as virgulas
}

/*=================================================================================================================================
Função que junta todas as partes do Tratamento1 e coloca dentro de uma word (string única)
=================================================================================================================================*/
//      ##############    #######    #################    #########   ###
//         ###    ###    ########   ###    ###  ### ###  ###    ########
//        ###    ###    #########  ###    ### ###   ### ###    ###  ###
//       ###    ###    ###### ### ###    #######################   ###
//      ###    ###    ######  ######    ######     ######    ###  ###
// ### ###    ###    ######   #####    ######     ######    ###  ###
// #####      ######## ###    ####    ######     ######    ##########
void juntar1(char *opcode, char *r1, char *r2, char *r3, char *shamp, char *funct,char *x){

    int j=0;

    for (int i = 0; i < 6; ++i) {
        x[j]=opcode[i];
        j++;
    }

    for (int i = 0; i < 5; ++i) {
        x[j]=r1[i];
        j++;
    }

    for (int i = 0; i < 5; ++i) {
        x[j]=r2[i];
        j++;
    }

    for (int i = 0; i < 5; ++i) {
        x[j]=r3[i];
        j++;
    }

    for (int i = 0; i < 5; ++i) {
        x[j]=shamp[i];
        j++;
    }

    for (int i = 0; i < 6; ++i) {
        x[j]=funct[i];
        j++;
    }

    return;
}

/*=================================================================================================================================
Função que junta todas as partes do Tratamento2 e coloca dentro de uma word (string única)
=================================================================================================================================*/
//      ##############    #######    #################    #########  ########
//         ###    ###    ########   ###    ###  ### ###  ###    ######    ###
//        ###    ###    #########  ###    ### ###   ### ###    ###      ###
//       ###    ###    ###### ### ###    #######################     ###
//      ###    ###    ######  ######    ######     ######    ###  ###
// ### ###    ###    ######   #####    ######     ######    ### ###
// #####      ######## ###    ####    ######     ######    #############
void juntar2(char *opcode, char *r1, char *r2, char *immediate,char *x){

    int j=0;

    for (int i = 0; i < 6; ++i) {
        x[j]=opcode[i];
        j++;
    }

    for (int i = 0; i < 5; ++i) {
        x[j]=r1[i];
        j++;
    }

    for (int i = 0; i < 5; ++i) {
        x[j]=r2[i];
        j++;
    }

    for (int i = 0; i < 16; ++i)    {
        x[j]=immediate[i];
        j++;
    }

    return;
}

/*=================================================================================================================================
Função que junta todas as partes do Tratamento3 e coloca dentro de uma word (string única)
=================================================================================================================================*/
//      ##############    #######    #################    #########  ########
//         ###    ###    ########   ###    ###  ### ###  ###    ######    ###
//        ###    ###    #########  ###    ### ###   ### ###    ###       ###
//       ###    ###    ###### ### ###    #######################     #####
//      ###    ###    ######  ######    ######     ######    ###       ###
// ### ###    ###    ######   #####    ######     ######    ######    ###
// #####      ######## ###    ####    ######     ######    ### ########
void juntar3(char *opcode,char *adress,char *x){

    int j=0;

    for (int i = 0; i < 6; ++i) {
        x[j]=opcode[i];
        j++;
    }

    for (int i = 0; i < 26; ++i)    {
        x[j]=adress[i];
        j++;
    }

    return;
}

//Funções utilidade

/*=================================================================================================================================
Função que retornará 1 caso o tratamento do shampt tenha que ser decimal, e 0 para tratamento hexadecimal
=================================================================================================================================*/
//       #################### ##############    ######################################################     ###              ###    ################    ###
//          ###    ###    ######       #####   ###    ###        ###    ###           ###   ###    ###  ### ###            ###    ######       ###    ###
//         ###    ###    ######       ######  ###    ###        ###    ###           ###   ###        ###   ###           ###    ######        ###  ###
//        ###    ###    ###########  ### ### ###    ###        ###    ########      ###   ###       ###########          ##################    ######
//       ###    ###    ######       ###  ######    ###        ###    ###           ###   ###       ###     ###          ###    ######        ###  ###
//      ###    ###    ######       ###   #####    ###        ###    ###           ###   ###    ######     ###          ###    ######       ###    ###
// #################### #############    ####    ###    ##############       ################### ###     ################    ################    ###

int identifica_hex(char *inst){

   if(strstr(inst,"0x")==NULL && strstr(inst,"0X")==NULL){
      return 1;
   }
   return 0;
}

//       :::::::::::::::::::: ::::::::::::::    ::::::::::::::::::::::::::::::::::::::::::::::::::::::     :::              :::           :::    :::::::::
//          :+:    :+:    :+::+:       :+:+:   :+:    :+:        :+:    :+:           :+:   :+:    :+:  :+: :+:            :+:         :+: :+:  :+:    :+:
//         +:+    +:+    +:++:+       :+:+:+  +:+    +:+        +:+    +:+           +:+   +:+        +:+   +:+           +:+        +:+   +:+ +:+    +:+
//        +#+    +#+    +:++#++:++#  +#+ +:+ +#+    +#+        +#+    :#::+::#      +#+   +#+       +#++:++#++:          +#+       +#++:++#++:+#++:++#+
//       +#+    +#+    +#++#+       +#+  +#+#+#    +#+        +#+    +#+           +#+   +#+       +#+     +#+          +#+       +#+     +#++#+    +#+
//      #+#    #+#    #+##+#       #+#   #+#+#    #+#        #+#    #+#           #+#   #+#    #+##+#     #+#          #+#       #+#     #+##+#    #+#
// #################### #############    ####    ###    ##############       ################### ###     ##########################     ############

int identifica_lab(char *inst){

    char *alfabeto="abcdefghijklmnopqrstuvwxyz";
    int flag=0;

    for (int i = 0; i < 24; ++i){
    
        if(strchr(inst,alfabeto[i])!=NULL || strchr(inst,toupper(alfabeto[i]))!=NULL){
            flag=1;
            return flag;
        }   
    }
    
    return flag;
}

/*=================================================================================================================================
Função que retornará o binário em forma de string a partir de um inteiro que será passado por parâmetro
=================================================================================================================================*/
//       ######### #############################  ###   ###      ###    ###            ########################    ###    ###    ######### ###################
//      ###    ######      ###    ###   ###     ##### #####   ### ###  ###           ###    ###   ###    #####   ###  ### ###  ###    ###    ###   ###    ###
//     ###    ######      ###          ###    ### ##### ### ###   ### ###           ###    ###   ###    ######  ### ###   ### ###    ###    ###   ###    ###
//    ###    ########### ###          ###    ###  ###  #################           #########    ###    ### ### #######################     ###   ###    ###
//   ###    ######      ###          ###    ###       ######     ######           ###    ###   ###    ###  #########     ######    ###    ###   ###    ###
//  ###    ######      ###    ###   ###    ###       ######     ######           ###    ###   ###    ###   ########     ######    ###    ###   ###    ###
// ######### ################################       ######     ########################################    #######     ######    ######################

void decimal_binario(int num, char *vet,int tam){

    for (int i = 0; i < tam; ++i)   {
        vet[i]='0';
    }

    int i=1;

    do {
        if (num%2==0){
            vet[tam-i]='0';

        }
        else{
            vet[tam-i]='1';

        }

        num=num/2;
        i++;
    
    } while(num!= 0);   

    return;

}

//       ::::::::::::::::::::::::    :::          :::    ::::::::::::::::    :::    :::
//      :+:    :+:   :+:    :+:+:   :+:          :+:    :+::+:       :+:    :+:  :+: :+:
//     +:+    +:+   +:+    :+:+:+  +:+          +:+    +:++:+        +:+  +:+  +:+   +:+
//    +#++:++#+    +#+    +#+ +:+ +#+          +#++:++#+++#++:++#    +#++:+  +#++:++#++:
//   +#+    +#+   +#+    +#+  +#+#+#          +#+    +#++#+        +#+  +#+ +#+     +#+
//  #+#    #+#   #+#    #+#   #+#+#          #+#    #+##+#       #+#    #+##+#     #+#
// #######################    #################    ################    ######     ###

/*Função que converte um número binário para hexa-decimal*/
char bin_hexa(char *v){

    if (v[0]=='0' && v[1]=='0' && v[2]=='0' && v[3]=='0'){
        return '0';
    } 

    else if (v[0]=='0' && v[1]=='0' && v[2]=='0' && v[3]=='1'){
            return '1';
    }

    else if (v[0]=='0' && v[1]=='0' && v[2]=='1' && v[3]=='0'){
            return '2';
    }

    else if (v[0]=='0' && v[1]=='0' && v[2]=='1' && v[3]=='1'){
            return '3';
    }

    else if (v[0]=='0' && v[1]=='1' && v[2]=='0' && v[3]=='0'){
            return '4';
    }

    else if (v[0]=='0' && v[1]=='1' && v[2]=='0' && v[3]=='1'){
            return '5';
    }

    else if (v[0]=='0' && v[1]=='1' && v[2]=='1' && v[3]=='0'){
            return '6';
    }

    else if (v[0]=='0' && v[1]=='1' && v[2]=='1' && v[3]=='1'){
            return '7';
    }

    else if (v[0]=='1' && v[1]=='0' && v[2]=='0' && v[3]=='0'){
            return '8';
    } 

    else if (v[0]=='1' && v[1]=='0' && v[2]=='0' && v[3]=='1'){
            return '9';
    }

    else if (v[0]=='1' && v[1]=='0' && v[2]=='1' && v[3]=='0'){
            return 'a';
    }

    else if (v[0]=='1' && v[1]=='0' && v[2]=='1' && v[3]=='1'){
            return 'b';
    }

    else if (v[0]=='1' && v[1]=='1' && v[2]=='0' && v[3]=='0'){
            return 'c';
    }

    else if (v[0]=='1' && v[1]=='1' && v[2]=='0' && v[3]=='1'){
            return 'd';
    }

    else if (v[0]=='1' && v[1]=='1' && v[2]=='1' && v[3]=='0'){
            return 'e';
    }

    else if (v[0]=='1' && v[1]=='1' && v[2]=='1' && v[3]=='1'){
            return 'f';
    }

    return 'X';

}

/*=================================================================================================================================
IDENTIFICA O TIPO DA FUNCAO
=================================================================================================================================*/
//       #################### ##############    ######################################################     ###             ###############################  ########
//          ###    ###    ######       #####   ###    ###        ###    ###           ###   ###    ###  ### ###               ###        ###    ###    ######    ###
//         ###    ###    ######       ######  ###    ###        ###    ###           ###   ###        ###   ###              ###        ###    ###    ######    ###
//        ###    ###    ###########  ### ### ###    ###        ###    ########      ###   ###       ###########             ###        ###    ######### ###    ###
//       ###    ###    ######       ###  ######    ###        ###    ###           ###   ###       ###     ###             ###        ###    ###       ###    ###
//      ###    ###    ######       ###   #####    ###        ###    ###           ###   ###    ######     ###             ###        ###    ###       ###    ###
// #################### #############    ####    ###    ##############       ################### ###     #############   ###    ##############        ########

/*Função que identificará o que se deve fazer de acordo com a string passada.
  Retornará 1 caso seja um comando do tipo R.
  Retornará 2 caso seja um comando do tipo I.
  Retornará 3 caso seja um comando do tipo J.
  Retornará 4 caso seja alguma diretiva a ser tratada.
  Retornará 5 caso seja uma pseudo instrução.
  Retornará 0 caso não seja nenhuma das opções acima.*/
int identifica_tipo(char *inst){
    /*----TIPO R----*/
    if  ( (strcmp(inst,"add"))==0   || (strcmp(inst,"sub"))==0    || (strcmp(inst,"slt"))==0  || (strcmp(inst,"and"))==0
       || (strcmp(inst,"or"))==0    || (strcmp(inst,"xor"))==0    || (strcmp(inst,"nor"))==0  || (strcmp(inst,"jr"))==0 
       || (strcmp(inst,"mfhi"))==0  || (strcmp(inst,"mflo"))==0   || (strcmp(inst,"addu"))==0 || (strcmp(inst,"subu"))==0
       || (strcmp(inst,"sll"))==0   || (strcmp(inst,"srl"))==0    || (strcmp(inst,"sra"))==0  || (strcmp(inst,"sllv"))==0 
       || (strcmp(inst,"srlv"))==0  || (strcmp(inst,"srav"))==0  ){
            return 1;
    }
    /*----TIPO I----*/
    else if((strcmp(inst,"lui"))==0   || (strcmp(inst,"addi"))==0  || (strcmp(inst,"slti"))==0 || (strcmp(inst,"andi"))==0
        || (strcmp(inst,"ori"))==0    || (strcmp(inst,"xori"))==0  || (strcmp(inst,"lw"))==0   || (strcmp(inst,"sw"))==0
        || (strcmp(inst,"bltz"))==0   || (strcmp(inst,"beq"))==0   || (strcmp(inst,"bne"))==0  || (strcmp(inst,"addiu"))==0 
        || (strcmp(inst,"lb"))==0     || (strcmp(inst,"lbu"))==0   || (strcmp(inst,"sb"))==0    ){
            return 2;
    }
    /*----TIPO J----*/
    else if(strcmp(inst,"j")==0 || strcmp(inst,"jal")==0){
            return 3;
    }   
    /*----TIPO DIRETIVAS----*/
    else if(strcmp(inst,".data")==0   || strcmp(inst,".text")==0 || strcmp(inst,".byte")==0 || strcmp(inst,".word")==0
         || strcmp(inst,".asciiz")==0 || strcmp(inst,".space")==0){
            return 4;
    }   
    /*----TIPO PSEUDO-CODIGO----*/
    else if(strcmp(inst,"mov")==0  || strcmp(inst,"li")==0  || strcmp(inst,"la")==0  || strcmp(inst,"bge")==0 
         || strcmp(inst,"bgt")==0  || strcmp(inst,"ble")==0 || strcmp(inst,"blt")==0){
            return 5;
    }

    return 0;
}