#include<stdio.h>
#include<string.h>
#include<conio.h>
#include<ctype.h>
#include"Types.h"
int validarplacacarro(char placa[]) {
	int i;
	if (strlen(placa) > 8)
		return 0;
	for (i = 0; i <= 2; i++){
		if (isalpha(placa[i]) == 0)
			return 0;
	}
	for (i = 3; i <= 7; i++){
		if (isdigit(placa[i]) == 0)
			return 0;
	}
		if (i != 7)
			return 0;
		else
			return 1;
	
}

int buscacarro(char placa[8],int *t,FILE*arq){
	int status,tam,com,i;
	Tcarros car;
	tam = sizeof(Tcarros);
	fseek(arq,0,0);
	for (i = 0; i<*t; i++){
		status = fread(&car, tam, 1, arq);
		if (status != 1)
			return -2;
		else{
			com = strcmp(car.placa, placa);
			if (com == 0){
				fseek(arq, 0, 0);
				return i;
			}
		}
	}
	return -1;
} // 6
int cadastrarcarro(int*t,FILE*arq){
	Tcarros car;
	char pl[8];
	int i , status, resultado,total;
	car.del = 1;
	total=*t++;
	printf("Informe a placa do carro:\n");
	fgets(pl,7,stdin);
	fflush(stdin);
	i = validarplacacarro(pl);
	if (i == 1)
		printf("Placa ja registrada.");
	else{
		resultado = buscacarro(car.placa,&t,arq);
		if (resultado == -2)
			printf("Erro de leitura.");
		else if (resultado != -1)
			printf("Placa ja registrada anteriormente");
		else{
			printf("Informe o no. do chassi:\n");
			fgets(car.chassi,10,stdin);
			fflush(stdin);
			printf("Informe a marca do carro:\n");
			fgets(car.marca,50,stdin);
			fflush(stdin);
			printf("Informe o modelo do carro:\n");
			fgets(car.modelo,50,stdin);
			fflush(stdin);
			printf("Informe o ano do carro:\n");
			scanf_s("%d", &car.ano);
			fflush(stdin);
			printf("Informe a cor do carro:\n");
			fgets(car.cor,10,stdin);
			fflush(stdin);
			printf("Informe o cpf do dono do carro:\n");
			fgets(car.cpf,11,stdin);
			fflush(stdin);
			status = fwrite(&car, sizeof(Tcarros), 1, arq);
			fflush(arq);
		}
	}
	return *t;
}
void procurarcarros(char cpf[9],int *t,FILE*arq){
	int pos,i,status,tam;
	Tcarros c;
	tam = sizeof(Tcarros);
	fseek(arq, 0, 0);
	for (i = 0; i<t; i++){
		status = fread(&c, tam, 1, arq);
		if (status != 1){
			printf("Erro de leitura.");
			break;
		}
		else{
			if (c.del==1)
				if (strcmp(cpf, c.cpf) == 0){
					printf("Placa: %s \n", c.placa);
					printf("Marca: %s \n", c.marca);
					printf("Modelo: %s \n", c.modelo);
			}
		}
	}
	fseek(arq,0,0);
}  //2
void exibirdadoscarro(char placa[8], int *t,FILE*arq){
	int pos,status,tam;
	Tcarros car;
	pos = buscacarro(placa,&t,arq);
	if (pos == -2)
		printf("Erro ao tentar encontrar o carro.");
	else if (pos == -1)
		printf("Carro nao encontrado");
	else{
		tam = sizeof(Tcarros);
		fseek(arq, tam*pos, 0);// talvez de erro
		status = fread(&car, tam, 1, arq);
		if (status != 1)
			printf("Erro de leitura");
		else{
			if (car.del == 1){
				printf("Nu. do Chassi: %s \n", car.chassi);
				printf("Marca: %s \n", car.marca);
				printf("Modelo: %s \n", car.modelo);
				printf("Ano: %s \n", car.ano);
				printf("Cor: %s \n", car.cor);

			}
		}
	}
}//3
void exibirdadosdono(char placa[8],int*t ,FILE*arq){
	int pos, status, tam;
	TAtendimento car;
	pos = buscacarro(placa,&t,arq);
	if (pos == -2)
		printf("Erro ao tentar encontrar o carro.");
	else if (pos == -1)
		printf("Carro nao encontrado");
	else{
		tam = sizeof(Tcarros);
		fseek(arq, tam*pos, 0);// talves de erro
		status = fread(&car, tam, 1, arq);
		if (status != 1)
			printf("Erro de leitura");
		else{
			if (car.cars.del == 1){
				printf("Nome: %s \n", car.cli.nome);//////////
				printf("Telefone: %s \n", car.cli.tel); ///////////
			}
		}
	}
}//4
void removercarro(char placa[8], int*t,FILE*arq){
	int tam,pos,status;
	TAtendimento car;
	tam = sizeof(Tcarros);
	pos = buscacarro(placa,&t ,arq);
	if (pos == -2)
		printf("Erro ao encontrar carro.");
	else if (pos == -1)
		printf("Carro nao encontrado");
	else{
		if (car.sta == 1){
			printf("Carro nao pode ser removido!Servico pendentes.");
			return;
		}
		else{
			fseek(arq, pos*tam, 0);
			status = fread(&car, tam, 1, arq);
			if (status != 1)
				printf("Erro de leitura");
			else{
				car.cars.del = 0;  ////////////////////////////
				fseek(arq, -tam, 1);
				status = fwrite(&car, tam, 1, arq);
				if (status != 1)
					printf("Erro de escrita.");
				else
					printf("Carro deletado com sucesso");
				fflush(arq);
			}
		}
	}
}//5
