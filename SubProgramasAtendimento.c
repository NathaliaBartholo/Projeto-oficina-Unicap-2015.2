#include <stdio.h>
#include <ctype.h>
#include "Types.h"
#include <string.h>

/*                                  //TABELA
TServicos tservicos;
char codigos = { '1','2','3','4','5' };
char descricao[5][25] = { "balanceamento\0","alinhamento\0","troca de
pastilha freio\0","troca de oleo\0","troca de filtro de ar\0" };
float valor[5][6] = { 50.00,60.00,70.00,80.00,40.00 };*/

void CadastrarAtendimento(FILE*arq, char placa[]);
int validarplacacarro(char placa[]);
int busca(FILE*arq, char placa[]);
void CadastrarServico(FILE*arq, char aux[]);
void RemoverServico(FILE*arq, char aux[]);
void EncerrarAtendimento(FILE*arq, char placa[]);
void ExibirServicos(FILE*arq, char[]);



int busca(FILE*arq, char placa[]) {
	TAtendimento a;
	int i = -1, status;
	fseek(arq, 0, 0);
	while (1) {
		status = fread(&a, sizeof(TAtendimento), 1, arq);
		if (status == 1) {
			i++;
			if (a.sta == 1) {
				if (strcmp(a.cars.placa, placa) == 0)
					return i;
			}
		}
		else{
			if (!feof(arq))
				printf("erro de leitura\n");
			break;
		}
	}
	return -1;
}

void CadastrarAtendimento(FILE*arq, char placa[]) {//tem q ajeitar
	TAtendimento a;
	int status;
	int x;//int validarplacacarro(char placa[])
	if (validarplacacarro(placa) == 1) {
		if (busca(arq, placa) == -1) {
			status = fseek(arq, 0, 2);
			strcpy_s(a.cars.placa,sizeof(placa) ,placa);
			printf("digite o dia do atendimento: ");
			fgets(a.dma.dia, 3, stdin);
			printf("digite o mes do atendimento: ");
			fgets(a.dma.mes, 10, stdin);
			printf("digite o ano do atendimento: ");
			fgets(a.dma.ano, 5, stdin);
			for (x = 0; x <= 9; x++)//solucao gambiarra
				a.Servicos[x]= '0';//tem que estar vazio, ={0} nao funciona
			a.sta = 1;
			fseek(arq, 0, 2);
			status = fwrite(&a, sizeof(TAtendimento), 1, arq);
			if (status != 1)
				printf("erro de gravacao\n");
			else
				printf("cadastro realizado");
		}
		else
			printf("placa fornecida ja possui atendimento em andamento");
	}
	else
		printf("placa invalida\n");
}

void CadastrarServico(FILE*arq, char aux[]) {
	int n, status, z = -1;
	TAtendimento s;
	if (validarplacacarro(aux) == 1) {
		if (busca != -1) {
			printf("digite o codigo do servico");
			scanf_s("%d", &n);
			if (n < 1 || n>5)
				printf("codigo invalido");
			else {
				fseek(arq, 0, 0);
				while (1) {
					status = fread(&s, sizeof(TAtendimento), 1, arq);
					if (status == 1) {
						z++;
						if (s.Servicos[z] == 0) {
							s.Servicos[z] = n;
							fseek(arq, -sizeof(TAtendimento), 1);
							status = fwrite(&s, sizeof(TAtendimento), 1, arq);
							if (status != 1)
								printf("erro de gravacao");
							else
								printf("servico adicionado");
							break;
						}
					}
					else
						if (!feof(arq)) {
							printf("erro de leitura\n");
							break;
						}
						else
							printf("numero maximo de servico por atendimento alcancado, favor fechar este e criar outro atendimento");
				}
			}
		}
		else
			printf("nao ha atendimento em andamento para a placa fornecida\n");
	}
	else
		printf("placa invalida\n");
}



void ConsultarServico(FILE*arq, char placa[]) {
	TAtendimento a;
	int status, n;
	if (validarplacacarro(placa) == 1) {
		if (busca == 1) {
			fseek(arq, -sizeof(TAtendimento), 1);
			status = fread(&a, sizeof(TAtendimento), 1, arq);
			if (status != 1)
				printf("erro de leitura");
			else
				for (n = 0; a.Servicos != 0; n++)
					printf("%d servico realizado: %", n + 1, a.Servicos[n]);
		}
		else
			printf("placa nao encontrada\n");
	}
	else
		printf("placa invalida\n");
}

void EncerrarAtendimento(FILE*arq, char placa[]) {
	TAtendimento a;
	int status, n = 0;
	float total = 0;
	char tabelacodigos[5] = { '1', '2', '3', '4', '5' };
	char tabeladescricao[5][25] = {"balanceamento\0", "alinhamento\0", "troca de pastilha freio\0", "troca	de oleo\0","troca de filtro de ar\0"};
	float tabelavalor[5] = { 50.00, 60.00, 70.00, 80.00, 40.00 };
	if (validarplacacarro(placa) == 1) {
		if (busca == 1) {
			fseek(arq, -sizeof(TAtendimento), 1);
			status = fread(&a, sizeof(TAtendimento), 1, arq);
			if (status != 1)
				printf("erro de leitura\n");
			else {
				a.sta = 0;
				status = fwrite(&a, sizeof(TAtendimento), 1, arq);
				if (status == 1) {
					while (a.Servicos != 0 && n <= 9) {
						printf("servico realizado: %s\n", tabeladescricao[n][25]);
						printf("com o valor de %.2f", tabelavalor[n]);
						n++;
						total = total + tabelavalor[n];
					}
					printf("atendimento encerrado\n");
					printf("valor total: %.2f", total);
				}
				else
						printf("erro de gravacao\n");
				}
			}
			else
				printf("placa nao encontrada\n");
		}
		else
			printf("placa invalida\n");
	}


void RemoverServico(FILE*arq, char aux) {
		TAtendimento a;
		int status, n;
		if (validarplacacarro(aux) == 1) {
			if (busca == 1) {
				fseek(arq, -sizeof(TAtendimento), 1);
				status = fread(&a, sizeof(TAtendimento), 1, arq);
				if (status != 1)
					printf("erro de leitura\n");
				else {
					ConsultarServico(arq, aux);
					printf("digite o numero do servico que deve ser removido: ");
					scanf_s("%d", &n);
					do {
						a.Servicos[n] = a.Servicos[n + 1];
					} while (a.Servicos[n + 1] != 0);
					fseek(arq, -sizeof(TAtendimento), 1);
					status = fwrite(&a, sizeof(TAtendimento), 1, arq);
					if (status == 1)
						printf("servico removido\n");
					else
						("erro de gravacao\n");
				}
			}
			else
				printf("placa nao encontrada\n");
		}
		else
			printf("placa invalida\n");
	}

void ExibirServicos(FILE*arq, char aux) {
	TAtendimento a;
	char tabelacodigos[5] = { '1', '2', '3', '4', '5' };
	char tabeladescricao[5][25] = { "balanceamento\0", "alinhamento\0", "troca de pastilha freio\0", "troca de oleo\0", "troca de filtro de ar\0" };
	float tabelavalor[5] = { 50.00, 60.00, 70.00, 80.00, 40.00 };
	int status,i = 0, z;
	if (busca(arq, aux) == 1) {
		if (validarplacacarro(aux) == 1) {
			fseek(arq, 0, 0);
			while (1) {
				status = fread(&a, sizeof(TAtendimento), 1, arq);
				if (status == 1) {
					i++;
					if (a.sta == 1)
						if (a.cars.placa[i]== aux)
							for (z = 0; a.Servicos != 0 && z <= 9; z++)
								printf("entrada %d,%d servico realizado: %s", i, z, tabeladescricao[*a.Servicos]);
				}
				else{
					if (!feof(arq))
						printf("erro de leitura\n");
					break;
				}
			}
		}
		else
			printf("placa invalida\n");
	}
	else
		printf("placa nao encontrada\n");	
}

	

