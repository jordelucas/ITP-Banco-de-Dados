/*--Bibliotecas--*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*--Arquivos externos--*/
#include "cabecalho.c"
#include "criarTabela.c"
#include "listarTabelas.c"
#include "apagarTabela.c"
#include "criarLinha.c"
#include "listarDados.c"

int main(){
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
		scanf("%d", &opcao);
		switch(opcao){
			case 1:
				cabecalho();
				criarTabela();
				cabecalho();
				break;
			case 2:
				cabecalho();
				listarTabelas();
				cabecalho();
				break;
			case 3:
				cabecalho();
				criarLinha();
				cabecalho();
				break;
			case 4:
				cabecalho();
				listarDados();
				cabecalho();
				break;
			case 7:
				cabecalho();
				apagarTabela();
				cabecalho();
				break;
			case 0:
				cabecalho();
				printf("Saindo...\n");
				break;
			default:
				cabecalho();
				printf("\nOpção Inválida!\n");
				break;
		}
	}while(opcao != 0);
	return 0;
}
