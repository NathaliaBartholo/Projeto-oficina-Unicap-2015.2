#include<stdio.h>
#include"Types.h"
#include"SubprogramasAtendimento.h"
#include"SubprogramasMain.h"
#include"SubprogramasModuloCarro.h"
void MenuAtendimentos(FILE*arqcli, FILE*arqcar) {
	FILE * arq;
	char filename[] = { "atendimentos.dat" };
	char op;
	char aux[8]; //placa, data de atendimento, lista de servicos	realizados, status de atendimento
	arq = criararquivo(filename);
	if (arq == NULL)
		printf("erro ao criar ou abrir arquivo\n");
	else {
		do {
			printf("Menu de atendimentos:\n");
			printf("1 - Cadastrar atendimento\n2 - Cadastrar servico\n3 -Consultar servicos realizados\n4 - Remover servico\n5 - Encerrar atendimento\n6 - Exibir atendimentos realizados\n7 - Voltar");
			printf("digite sua opcao: ");
			op = getchar(); fflush(stdin);
			switch (op) {
			case '1':
				printf("digite a placa: ");
				fgets(aux, 8, stdin); fflush(stdin);
				CadastrarAtendimento(arq, aux);
				break;
			case '2':
				printf("digite a placa: ");
				fgets(aux, 8, stdin); fflush(stdin);
				CadastrarServico(arq, aux);
				break;
			case '3':
				printf("digite a placa: ");
				fgets(aux, 8, stdin); fflush(stdin);
				ConsultarServico(arq, aux);
				break;
			case '4':
				printf("digite a placa: ");
				fgets(aux, 8, stdin); fflush(stdin);
				RemoverServico(arq, aux);
				break;
			case '5':
				printf("digite a placa: ");
				fgets(aux, 8, stdin); fflush(stdin);
				EncerrarAtendimento(arq, aux);
				break;
			}
		} while (op != 7);
	}
	return;
}
