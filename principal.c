/*--Bibliotecas--*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*--Constantes--*/
#define CHAR 1;
#define INT 4;
#define DOUBLE 8;
#define FLOAT 8;
#define STRING 20;

/*--Arquivos externos--*/
#include "funcoesUteis.c"
#include "adicionarAtributo.c"
#include "criarTabela.c"
#include "listarTabelas.c"
#include "apagarTabela.c"
#include "criarLinha.c"
#include "listarDados.c"
#include "apagarLinha.c"
#include "pesquisarValor.c"

int main(){
	FILE *pont_tabelas;
	pont_tabelas = fopen("tabelas//listaTabelas.txt", "a");
	if (pont_tabelas == NULL){
		printf("ERRO! O arquivo de nomes não foi aberto.\n");
		exit(0);
	}
	int opcao;
	cabecalho();
	do{
		printf("Escolha uma opcão:\n\n");
		printf("1- Criar tabela\n");
		printf("2- Listar tabelas\n");
		printf("3- Criar linha\n");
		printf("4- Listar dados\n");
		printf("5- Pesquisar valor\n");
		printf("6- Apagar valor\n");
		printf("7- Apagar Tabela\n");
		printf("0- Sair\n");
		printf("Opção: ");
		fflush(stdin);
		scanf("%d", &opcao);
		switch(opcao){
			case 1:
				criarTabela();
				cabecalho();
				break;
			case 2:
				listarTabelas();
				cabecalho();
				break;
			case 3:
				criarLinha();
				cabecalho();
				break;
			case 4:
				listarDados();
				cabecalho();
				break;
			case 5:
				pesquisarValor();
				cabecalho();
				break;
			case 6:
				apagarLinha();
				cabecalho();
				break;
			case 7:
				apagarTabela();
				cabecalho();
				break;
			case 0:
				cabecalho();
				printf("Saindo...\n");
				exit(0);
				break;
			default:
				cabecalho();
				printf("Opção Inválida!\n");
				break;
		}
	}while(opcao != 0);
	return 0;
}
