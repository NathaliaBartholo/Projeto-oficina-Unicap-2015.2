#include<stdio.h>
FILE*criararquivo(char nome[]) {
	FILE*arq;
	arq = fopen(nome, "r+b");
	if (arq == NULL)
		arq = fopen(nome, "w+b");
	return arq;
}
