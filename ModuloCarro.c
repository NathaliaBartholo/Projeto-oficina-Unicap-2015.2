#include<stdio.h>
#include"SubprogramasModuloCarro.h"

ModuloCarro (FILE*arq){
	int op,t=0;
	char cpf[9], placa[8],filenam="Modulo de carro.dat";
	printf("Menu principal:\nEscolha a operação desejada:\n1-Cadastrar carro;\n2-Procurar carro atraves do cpf;\n3-Exibir dados do carro\n4-Exibir dados do proprietario do carro;\n5-Remover carro;e\n6-Retornar\nEscolha:");
	scanf_s("%d", &op);
	fflush(stdin);
	while (op >= 7 || op <= 0){
		printf("Opção invalida!\nEscolha a operação desejada:\n1-Cadastrar carro;\n2-Procurar carro atraves do cpf;\n3-Exibir dados do carro\n4-Exibir dados do proprietario do carro;\n5-Remover carro;e\n6-Retornar\nEscolha:");
		scanf_s("%d", &op);
		fflush(stdin);
	}
	switch (op){
	case 1:
		cadastrarcarro(arq,&t);
		break;
	case 2:printf("Informe o cpf:");
		fgets(cpf,11,stdin);
		fflush(stdin);
		procurarcarros(cpf,&t,arq);
		break;
	case 3:printf("Informe a placa do carro: ");
		fgets(placa,8,stdin);
		fflush(stdin);
		while (1){
			op = validarplacacarro(placa);
			if (op == 0)
				printf("Placa invalida.");
			else if (op != 0)
				break;
		}
		exibirdadoscarro(placa,&t,arq);
		break;
	case 4:printf("Informe a placa do carro: ");
		fgets(placa,8,stdin);
		fflush(stdin);
		exibirdadosdono(placa,&t,arq);
		break;
	case 5:printf("Informe a placa do carro: ");
		fgets(placa,8,stdin);
		fflush(stdin);
		removercarro(placa,&t,arq);
		break;
	case 6:return;
	}
}



