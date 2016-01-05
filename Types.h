#ifndef carro
#define carro
typedef struct cadastro{
	char placa[9], chassi[11], marca[51], modelo[51], cor[11],cpf[12],del ;
	int ano;
}Tcarros;
#endif

#ifndef data
#define	data
typedef struct data {
	char dia[3], mes[10], ano[5];//dia no formato 1 a 31 + /0, mes para caber o mes com mais letras fevereiro (9) + /0, ano para quatro digitos + /0
}TData;

#endif
#ifndef clientes
#define clientes
typedef struct cliente
{
	char nome[30], cpf[12], tel[9], email[20];
	int status;
}Tcliente;
#endif
#ifndef atendimento
#define atendimento
typedef struct atendimento {
	Tcliente cli;
	Tcarros cars ;
	TData dma;//dia mes ano
	int Servicos[10];
	int sta;//0 para encerrado, 1 para em andamento } 
} TAtendimento;
#endif
