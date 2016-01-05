#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include"Types.h"

int validarcpf(Tcliente a);
void cadclientes(Tcliente c, int *n, FILE*arq);
void altcliente(Tcliente c, int n, FILE*arq);
void excliente(Tcliente a, int n, FILE*arq);
int concliente(Tcliente a, int n, FILE*arq);
void remcliente(Tcliente a, int n, FILE*arqcli, FILE*arq);

int validarcpf(Tcliente a)
{
	int soma=0, i, d, num;
	char d10, d11;
	if (strlen(a.cpf)>12)
		return 0;
	for (i = 0; i<11; i++)
	{
		if (isalpha(a.cpf[i]) != 0)
			return 0;
	}
	for (i = 0; i<9; i++)
	{
		num = a.cpf[i] - 48;
		soma = soma + (num * (10 - i));
	}
	d = 11 - (soma % 11);
	if ((d == 10) || (d == 11))
		d10 = '0';
	else
		d10 = d + 48;


	soma = 0;
	for (i = 0; i<10; i++)
	{
		num = a.cpf[i] - 48;
		soma = soma + (num * (11 - i));
	}
	d = 11 - (soma % 11);
	if ((d == 10) || (d == 11))
		d11 = '0';
	else
		d11 = d + 48;


	if ((d10 != a.cpf[9]) && (d11 != a.cpf[10]))
		return 0;
	else
		return 1;
}
void cadclientes(Tcliente c, int *n, FILE*arq)
{
	int b, d, i, x;

	printf("digite o cpf do cliente\n");
	fflush(stdin);
	fgets(c.cpf,11,stdin); fflush(stdin);
	b = validarcpf(c);
	if (b == 0)
	{
		printf("cpf invalido\n");
		return;

	}
	x = concliente(c, *n, arq);
	if (x != -1 && x != -2)
	{
		printf("esse cliente ja existe");
		return;
	}
	if (x == -2)
	{
		printf("erro de execucao");
		return;
	}


	fseek(arq, sizeof(Tcliente), SEEK_END);/////
	fwrite(&c, sizeof(Tcliente), 1, arq);

	printf("digite o nome do cliente\n");
	fflush(stdin);
	fgets(c.nome,29,stdin); fflush(stdin);
	d = strlen(c.nome);
	for (i = 0; i<d; i++)
	{
		if (isalpha(c.nome[i] == 0))
		{
			printf("nome invalido\n");
			return ;
		}

	}
	fseek(arq, -sizeof(Tcliente), SEEK_END);
	fwrite(&c, sizeof(Tcliente), 1, arq);
	printf("digite o telefone do cliente");
	fflush(stdin);
	fgets(c.tel,8,stdin); fflush(stdin);
	d = strlen(c.tel);
	for (i = 0; i<d; i++)
	{
		if (isalpha(c.tel[i] != 0))
		{
			printf("telefone invalido\n");
			return;
		}
	}
	fseek(arq, -sizeof(Tcliente), SEEK_END);
	fwrite(&c, sizeof(Tcliente), 1, arq);
	printf("digite o email do cliente");
	fflush(stdin);
	fgets(c.email,19,stdin); fflush(stdin);
	fseek(arq, -sizeof(Tcliente), SEEK_END);
	fwrite(&c, sizeof(Tcliente), 1, arq);
	c.status = 1;
	fseek(arq, -sizeof(Tcliente), SEEK_END);
	fwrite(&c, sizeof(int), 1, arq);
	*n = *n + 1;
	printf("cadastro concluido");


}
void altcliente(Tcliente c, int n, FILE*arq)
{
	int o, x,tam;
	tam = sizeof(Tcliente);
	x = concliente(c, n, arq);
	if (x == -1)
	{
		printf("esse cliente nao existe\n");
		return;
	}
	if (x == -2)
	{
		printf("erro de execucao\n");
		return;
	}
	printf("1-alterar nome\n2-alterar telefone\n3-alterar email\n");
	scanf_s("%d", &o);

	if (o == 1)
	{


		printf("digite o novo nome\n");
		fgets(c.nome,29,stdin); fflush(stdin);
		fseek(arq, x*tam, SEEK_SET);
		fwrite(&c, sizeof(Tcliente), 1, arq);
		printf("alteracao feita");


	}


	else if (o == 2)
	{


		printf("digite o novo telefone\n");
		fgets(c.tel,8,stdin); fflush(stdin);
		fseek(arq, x*tam, SEEK_SET);
		fwrite(&c, sizeof(Tcliente), 1, arq);
		printf("alteracao feita\n");

	}


	else if (o == 3)
	{


		printf("digite o novo email\n");
		fgets(c.email,19,stdin); fflush(stdin);
		fseek(arq, x*tam, SEEK_SET);
		fwrite(&c, sizeof(Tcliente), 1, arq);
		printf("alteracao feita\n");

	}


	else
		printf("opcao invalida\n");
}
void excliente(Tcliente a, int n, FILE*arq)
{
	int x;
	Tcliente r;
	x = concliente(a, n, arq);

	if (x != -1 && x != -2)
	{
		fseek(arq, 0, 0);
		fread(&r, sizeof(Tcliente), x, arq);
		printf("o nome do cliente eh:%s\n", r.nome);
		fseek(arq, 0, 0);
		fread(&r, sizeof(Tcliente), x, arq);
		printf("o telefone do cliente eh:%s\n", r.tel);
		fseek(arq, 0, 0);
		fread(&r, sizeof(Tcliente), x, arq);
		printf("o email do cliente eh:%s\n", r.email);

	}


	else if (x == -1)
		printf("esse cliente nao existe\n");
	else
		printf("erro de execucao\n");
}
int concliente(Tcliente a, int n, FILE*arq)
{
	int i;
	Tcliente r;
	fseek(arq, 0, 0);
	for (i = 1; i <= n; i++)
	{
		fread(&r, sizeof(Tcliente), 1, arq);
		if (strcmp(r.cpf, a.cpf) == 0)
			return i-1;
	}
	if (feof(arq))
		return -1;
	return -2;
}
void remcliente(Tcliente a, int n, FILE*arqcli,FILE*arqcar)
{
	int b,i,p,tam;
	tam = sizeof(Tcliente);
	char aux1[12],aux2[12];
	Tcarros r;
	b = concliente(a, n, arqcli);
	a.status = 0;
	if (b != -1 && b != -2)
	{
		i=concliente(a, n, arqcli);
		if (i == -2)
			printf("Erro de leitura");
		else if (i == -1)
			printf("Cliente nao encontrado");
		else{
			fseek(arqcli, 0, 0);
			p=fread(&aux1, i*sizeof(Tcliente), 1, arqcli);
			if (p != 1)
				printf("Erro de leitura");
		}
		i =  concliente(a, n, arqcar);
		if (i == -2)
			printf("Erro de leitura");
		else if (i == -1)
			printf("Proprietario do carro nao encontrado.");
		else{
			fseek(arqcar, 0, 0);
			p = fread(&aux2, i*sizeof(Tcarros), 1, arqcar);
			if (p != 1)
				printf("Erro de leitura.");
			else{
				if (strcmp(aux1, aux2) == 0)
					printf("Nao foi possivel excluir cliente.Existe carro(s) cadastrado(s) no cpf.");
				else{
					fseek(arqcli, b, 0);
					fread(&r, sizeof(Tcliente), 1, arqcli);
					fseek(arqcli, -1*tam, SEEK_CUR);
					fwrite(&a, sizeof(Tcliente), 1, arqcli);
				}
			}
			}
	}
	else if (b == -1)
		printf("esse cliente nao existe\n");
	else
		printf("erro de execucao");
}
