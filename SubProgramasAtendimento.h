#include<stdio.h>
void CadastrarAtendimento(FILE*arq, char placa[]); 
int validarplacacarro(char placa[]);
int busca(FILE*arq, char placa[]); 
void CadastrarServico(FILE*arq, char aux[]);
void RemoverServico(FILE*arq, char aux[]);
void EncerrarAtendimento(FILE*arq, char placa[]);
void ExibirServicos(FILE*arq, 
