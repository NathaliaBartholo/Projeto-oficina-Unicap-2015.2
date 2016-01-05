#include<stdio.h>
#include "Modulos.h"
#include"Types.h"
#include"SubprogramasMain.h"
void manutençaocarro(FILE*arq){
	FILE*aux;
	int s, erro = 0;
	Tcarros c;
	aux = fopen("auxiliar.dat", "w+b");
	if (aux == NULL)
		printf("Erro\n");
	else{
		fseek(arq, 0, 0);
		while (1){
			s = fread(&c, sizeof(Tcarros), 1, arq);
			if (s != 1)
				if (!feof(arq)){
					printf("Erro de leitura");
					erro = 1;

					break;
				}
		else{
			if (c.del == 1){
				s = fwrite(&c, sizeof(Tcarros), 1, aux);
				if (s != 1){
					printf("Erro de gravacao");
					erro = 1;
					break;
				}
			}
		}
	 }
		if (erro == 0){
			fclose(arq);
			fclose(aux);
			remove("ModuloCarro");
			rename("Auxiliar", "ModuloCarro");
		}
		else{
			fclose(aux);
			remove("Auxiliar");
		}
	}
}
void manutençaocliente(FILE*arq){
	FILE*aux;
	int s, erro = 0;
	Tcliente c;
	aux = fopen("auxiliar.dat", "w+b");
	if (aux == NULL)
		printf("Erro\n");
	else{
		fseek(arq, 0, 0);
		while (1){
			s = fread(&c, sizeof(Tcliente), 1, arq);
			if (s != 1)
				if (!feof(arq)){
					printf("Erro de leitura");
					erro = 1;

					break;
				}
				else{
					if (c.status == 1){
						s = fwrite(&c, sizeof(Tcliente), 1, aux);
						if (s != 1){
							printf("Erro de gravacao");
							erro = 1;
							break;
						}
					}
				}
		}
		if (erro == 0){
			fclose(arq);
			fclose(aux);
			remove("ModuloCliente");
			rename("Auxiliar", "ModuloCliente");
		}
		else{
			fclose(aux);
			remove("Auxiliar");
		}
	}
}

int main(){
	FILE*arqcarro;
	FILE*arqcliente;
	int o;
	char cliente[] = { "ModuloCliente.dat" }, carros[] = { "ModuloCarro.dat" };
	arqcliente = criararquivo(cliente);
	arqcarro = criararquivo(carros);
	if (arqcliente == NULL)
		printf("Erro ao abrir Modulo de clientes");
	else if (arqcarro == NULL)
		printf("Erro ao abrir Modulo de carros");
	else{
		printf("Menu principal\n1-Modulo de cliente\n2-Modulo de carro\n3-Modulo de atentimentos\n4-Sair\nEscolha uma opcao\nAlternativa:");
		scanf_s("%d", &o);
		while (o < 1 && o >= 5){
			printf("Opção invalida!");
			printf("Informe uma opcao validade.\n1-Modulo de cliente\n2-Modulo de carro\n3-Modulo de atentimentos\n4-Sair\nEscolha uma opção\nAlternativa:");
			scanf_s("%d", &o);
		}
		do{
			switch (o){
			case 1:ModuloClientes(arqcliente, arqcarro);
				break;
			case 2:ModuloCarro(arqcarro);
				break;
			case 3: MenuAtendimentos(arqcliente, arqcarro);
				break;
			case 4:
				manutençaocarro(arqcarro);
				manutençaocliente(arqcliente);
				break;
			}
		} while (o != 4);
		return 0;
	}
}
