#include <stdio.h>
#include <stdlib.h>

#include "TAD_Decode.h"
#include "Simulador.h"

void execute1(unsigned int inst,Simulador *X);
void execute2(unsigned int inst,Simulador *X);
void execute3(unsigned int inst,Simulador *X);
void execute4(Simulador *X);

//       :::::::::::::    ::::::::::::::::::::: :::    ::::::::::::::::::::::::  :::
//      :+:       :+:    :+::+:      :+:    :+::+:    :+:    :+:    :+:       :+:+:
//     +:+        +:+  +:+ +:+      +:+       +:+    +:+    +:+    +:+         +:+
//    +#++:++#    +#++:+  +#++:++# +#+       +#+    +:+    +#+    +#++:++#    +#+
//   +#+        +#+  +#+ +#+      +#+       +#+    +#+    +#+    +#+         +#+
//  #+#       #+#    #+##+#      #+#    #+##+#    #+#    #+#    #+#         #+#
// #############    #####################  ########     ###    #################

//instruções do tipo R
void execute1(unsigned int inst,Simulador *X){

	unsigned int r1=get_register(inst,1);
	unsigned int r2=get_register(inst,2);
	unsigned int r3=get_register(inst,3);
	unsigned int shampt=get_shampt(inst);
	unsigned int funct=get_funct(inst);

	//ADD
	if(funct==32){
		X->reg[r3]=X->reg[r2] + X->reg[r1];
	}
	//ADDU
	else if(funct==33){
		X->reg[r3]=(unsigned int)X->reg[r2] + (unsigned int)X->reg[r1];
	}
	//AND
	else if(funct==36){
		X->reg[r3]=X->reg[r2] & X->reg[r1];
	}
	//NOR o not é ~
	else if(funct==39){
		X->reg[r3]=X->reg[r2] | X->reg[r1];
		X->reg[r3]=~X->reg[r3];
	}
	//OR
	else if(funct==37){
		X->reg[r3]=X->reg[r2] | X->reg[r1];
	}
	//SLT
	else if(funct==42){
		if(X->reg[r2] < X->reg[r1]){
			X->reg[r3]=1;
		}
		else{
			X->reg[r3]=0;
		}
	}
	//SUB
	else if(funct==34){
		X->reg[r3]=X->reg[r2] - X->reg[r1];
	}
	//SUBU
	else if(funct==35){
		X->reg[r3]=(unsigned int)X->reg[r2] - (unsigned int)X->reg[r1];
	}
	//XOR
	else if(funct==38){
		X->reg[r3]= X->reg[r2] ^ X->reg[r1];
	}

	// a partir daqui começa o tratamentos do rs e rt trocados de lugares porém com 3 registradores ainda 

	//SLLV
	else if(funct==4){
		X->reg[r3]=X->reg[r2] << X->reg[r1];
	}
	//SRAV
	else if(funct==7){
		X->reg[r3]=X->reg[r2] >> X->reg[r1];
	}
	//SRLV
	else if(funct==6){
		X->reg[r3]=(unsigned int)X->reg[r2] >> (unsigned int)X->reg[r1];
	}

	// a partir daqui começa os tratamentos que tem shamt

	//SLL
	else if(funct==0){
		X->reg[r3]=X->reg[r2] << shampt;
	}
	//SRA
	else if(funct==3){
		X->reg[r3]=X->reg[r2] >> shampt;
	}
	//SRL
	else if(funct==2){
		X->reg[r3]=(unsigned int)X->reg[r2] >> (unsigned int)shampt;
	}

	//a partir daqui começa os tratamentos que só possui um registrador

	//MFHI
	else if(funct==16){

	}
	//MFLO
	else if(funct==18){

	}
	//JR
	else if(funct==8){
		X->pc=X->npc;
		X->npc=X->reg[r1];
	}
	//SYSCALL
	else if(funct==12){
		execute4(X);
	}

}

//       :::::::::::::    ::::::::::::::::::::: :::    :::::::::::::::::::::::: ::::::::
//      :+:       :+:    :+::+:      :+:    :+::+:    :+:    :+:    :+:       :+:    :+:
//     +:+        +:+  +:+ +:+      +:+       +:+    +:+    +:+    +:+             +:+
//    +#++:++#    +#++:+  +#++:++# +#+       +#+    +:+    +#+    +#++:++#      +#+
//   +#+        +#+  +#+ +#+      +#+       +#+    +#+    +#+    +#+         +#+
//  #+#       #+#    #+##+#      #+#    #+##+#    #+#    #+#    #+#        #+#
// #############    #####################  ########     ###    ####################

//instruções do tipo I
void execute2(unsigned int inst,Simulador *X){

	unsigned int opcode=get_opcode(inst);
	unsigned int r1=get_register(inst,1);
	unsigned int r2=get_register(inst,2);
	unsigned int immediate=get_immediate(inst);

	//ADDI
	if(opcode==8){
		X->reg[r2]=X->reg[r1] + immediate;
	}
	//SLTI
	else if(opcode==10){
		if(X->reg[r1] < immediate){
			X->reg[r2]=1;
		}
		else{
			X->reg[r2]=0;
		}
	}
	//ANDI
	else if(opcode==12){
		X->reg[r2]=X->reg[r1] & immediate;
	}
	//XORI
	else if(opcode==14){
		X->reg[r2]= X->reg[r1] ^ immediate;
	}
	//ORI
	else if(opcode==13){
		X->reg[r2]=X->reg[r1] | immediate;
	}
	//ADDIU
	else if(opcode==9){
		X->reg[r2]=(unsigned int)X->reg[r1] + (unsigned int)immediate;
	}

	//ESTADO 2

	//BLTZ
	else if(opcode==1){
		if(X->reg[r1]<0){
			X->pc=X->pc+(immediate<<2);
		}
		else{
			X->pc=X->pc+1;
		}
	}

	//ESTADO 3

	//LUI
	else if(opcode==15){
		X->reg[r2]=immediate<<16;
	}

	//ESTADO 4
	
	//LW
	else if(opcode==35){
		if(X->reg[r1]+immediate < X->size_memdata){
			X->reg[r2]=(signed) X->memo_data[X->reg[r1]+immediate];
		}
	}
	//SW
	else if(opcode==43){
		if(X->reg[r1]+immediate < X->size_memdata){
			X->memo_data[X->reg[r1]+immediate]= X->reg[r2];
		}
	}
	//LB
	else if(opcode==32){
		if(X->reg[r1]+immediate < X->size_memdata){
			X->reg[r2]=(signed) X->memo_data[X->reg[r1]+immediate] & 0xff;
		}
	}
	//LBU
	else if(opcode==36){
		if(X->reg[r1]+immediate < X->size_memdata){
			X->reg[r2]=(unsigned) X->memo_data[X->reg[r1]+immediate] & 0xff;
		}
	}
	//SB
	else if(opcode==40){
		if(X->reg[r1]+immediate < X->size_memdata){
			X->memo_data[X->reg[r1]+immediate]= X->reg[r2] & 0xff;
		}
	}

	//ESTADO 5

	//BNE
	else if(opcode==5){
		if(X->reg[r1]!=X->reg[r2]){
			X->pc=X->pc+(immediate<<2);
		}
		else{
			X->pc=X->pc+1;
		}
	}
	//BEQ
	else if(opcode==4){
		if(X->reg[r1]==X->reg[r2]){
			X->pc=X->pc+(immediate<<2);
		}
		else{
			X->pc=X->pc+1;
		}
	}	

}

//       :::::::::::::    ::::::::::::::::::::: :::    ::::::::::::::::::::::::::::::::
//      :+:       :+:    :+::+:      :+:    :+::+:    :+:    :+:    :+:      :+:    :+:
//     +:+        +:+  +:+ +:+      +:+       +:+    +:+    +:+    +:+             +:+
//    +#++:++#    +#++:+  +#++:++# +#+       +#+    +:+    +#+    +#++:++#     +#++:
//   +#+        +#+  +#+ +#+      +#+       +#+    +#+    +#+    +#+             +#+
//  #+#       #+#    #+##+#      #+#    #+##+#    #+#    #+#    #+#      #+#    #+#
// #############    #####################  ########     ###    ##################

//instruções do tipo J
void execute3(unsigned int inst,Simulador *X){

	unsigned int opcode=get_opcode(inst);
	unsigned int adress=get_adress(inst);	

	//J
	if(opcode==2){
		X->pc=X->npc;
		X->npc=(X->pc&0xf0000000) | (adress<<2);
	}
	//JAL
	else if(opcode==3){
		X->reg[31]=X->pc+8;
		X->pc=X->npc;
		X->npc=(X->pc&0xf0000000) | (adress<<2);
	}	

}

//       :::::::::::::    ::::::::::::::::::::: :::    :::::::::::::::::::::::: :::
//      :+:       :+:    :+::+:      :+:    :+::+:    :+:    :+:    :+:       :+:
//     +:+        +:+  +:+ +:+      +:+       +:+    +:+    +:+    +:+      +:+ +:+
//    +#++:++#    +#++:+  +#++:++# +#+       +#+    +:+    +#+    +#++:++#+#+  +:+
//   +#+        +#+  +#+ +#+      +#+       +#+    +#+    +#+    +#+    +#+#+#+#+#+
//  #+#       #+#    #+##+#      #+#    #+##+#    #+#    #+#    #+#          #+#
// #############    #####################  ########     ###    ##########   ###

//Syscall
void execute4(Simulador *X){
	//$v0 = 2
	//$a0-$a3 = 4-7

	//print integer
	if(X->reg[2]==1){
		printf("%d",X->reg[4]);
	}

	//print string
	else if(X->reg[2]==4){
		
		int temp=1;
		int aux=0;
		int local=X->reg[4];
		int shif=0xff;
		int qtd;

		while(shif!=0){
			
			if (aux==0){
			temp=X->memo_data[local];
			local++;
			qtd=0;
			}

			aux++;

			shif= ( temp&(0xff<<qtd) )>>qtd;

			printf("%c",shif);

			qtd=qtd+8;

			if (aux==4){
				aux=0;
			}

		}
	}

	//scan integer
	else if(X->reg[2]==5){
		scanf("%d",&X->reg[2]);
	}

	//scan string
	else if(X->reg[2]==8){

		char str[X->reg[5]];
		scanf("%s",str);

		for (int i = 0; i < X->reg[5]; ++i){
			X->memo_data[X->reg[4] + (i/4)] = X->memo_data[X->reg[4] + (i/4)] | str[i]<<8*(i%4);
		}
	}

	//finalizar programa
	else if(X->reg[2]==10){
		exit(0);
	}

	//print char	
	else if(X->reg[2]==11){
		printf("%c",X->reg[4]&0xff);
	}

	//scan char	
	else if(X->reg[2]==12){
		char z;
		scanf("%c",&z);
		X->reg[2]=z;
	}

	//print hexa	
	else if(X->reg[2]==34){
		printf("%x",X->reg[4]);
	}
}