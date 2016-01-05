#include<stdio.h>
#include"Types.h"
#include"SubprogramasModuloClientes.h"
void ModuloClientes(FILE*arqcli,FILE*arqcar)
{
	int n=1, o;
	//char cp[12];
	Tcliente ew;
	ew.tel[0] = '/0';
	ew.cpf[0] = '/0';
	ew.nome[0] = '/0';
	ew.email[0] = '0';
	ew.status = -1;
	if (arqcar==NULL)
		printf("erro de execucao do modulo carros");
	if (arqcli == NULL)
		printf("erro de execucao do modulo clientes");
	else
	{
		printf("1-cadastrar cliente\n2-alterar dados do cliente\n3-exibir dados do cliente\n4-remover um cliente\n");
		scanf_s("%d", &o);
		if (o == 1)
		{
			cadclientes(ew, &n, arqcli);
		}
		else if (o == 2)
		{
			printf("Informe o cpf:");
			fflush(stdin);
			fgets(ew.cpf, 11, stdin);
			fflush(stdin);
			altcliente(ew, n, arqcli);
		}
		else if (o == 3)
		{
			printf("Informe o cpf:");
			fflush(stdin);
			fgets(ew.cpf, 11, stdin);
			fflush(stdin);
			excliente(ew, n, arqcli);
		}
		else if (o == 4)
		{
			printf("Informe o cpf:");
			fflush(stdin);
			fgets(ew.cpf, 11, stdin);
			fflush(stdin);
			remcliente(ew, n, arqcli,arqcar);
		}
		else
			return;
	}
}
