#include<stdio.h>
#include"Types.h"
int validarcpf(Tcliente a);
void cadclientes(Tcliente c, int *n, FILE*arq);
void altcliente(Tcliente c, int n, FILE*arq);
void excliente(Tcliente a, int n, FILE*arq);
int concliente(Tcliente a, int n, FILE*arq);
void remcliente(Tcliente a, int n, FILE*arqcli,FILE*arqcar);
