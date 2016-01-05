#include<stdio.h>
int buscacarro(char placa[7],int *t,FILE*arq);
void cadastrarcarro(int*t,FILE*arq);
void procurarcarros(char cpf[9],int *t,FILE*arq);
void exibirdadoscarro(char placa[7],int *t,FILE*arq);
void exibirdadosdono(char cpf[9],int*t,FILE*arq);
void removercarro(char placa[7],int*t,FILE*arq);
int validarplacacarro(char placa[]);
