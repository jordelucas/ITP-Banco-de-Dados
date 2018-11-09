#include <stdio.h>
#include <stdlib.h>
#include "cabecalho.c"
#include "criarTabela.c"

int main(){
	int opcao = -1;
	cabecalho();
	do{
		printf("\nEscolha uma opcao:\n\n");
		printf("1- Criar tabela\n");
		printf("2- Listar tabelas\n");
		printf("3- Criar linha\n");
		printf("4- Listar dados\n");
		printf("5- Pesuisar valor\n");
		printf("6- Apagar valor\n");
		printf("7- Apagar Tabela\n");
		printf("0- Sair\n");
		printf("Opção: ");
		scanf("%d", &opcao);
		switch(opcao){
			case 1:
				criarTabela();
				cabecalho();
				printf("Entrou\n");	
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
