#include <stdio.h>
#include <string.h> //para usar a função que concatena strings

void criarTabela() {
	FILE *pont_dados_tabela;
	FILE *pont_tamanho_tabela;
	char nome_dados_tabela[35] = "";
	char nome_tamanho_tabela[35] = "";
	char nome[15];

	printf("Nome: ");
	scanf("%s", nome);

	strcat(nome_dados_tabela, "dados/");
	strcat(nome_dados_tabela, nome);
	strcat(nome_dados_tabela, "_dados.txt");
	strcat(nome_tamanho_tabela, "tamanhos/");
	strcat(nome_tamanho_tabela, nome);
	strcat(nome_tamanho_tabela, "_tamanho.txt");

	//Abrir arquivo de dados
	pont_dados_tabela = fopen(nome_dados_tabela, "w");

	if (pont_dados_tabela == NULL){
    		printf("ERRO! O arquivo de dados não foi aberto!\n");
	}else{
     		printf("O arquivo de dados foi aberto com sucesso!\n");
   	}

	fclose(pont_dados_tabela);

	//Abrir arquivo do tamanho dos atributos
	pont_tamanho_tabela = fopen(nome_tamanho_tabela, "w");

	if (pont_tamanho_tabela == NULL){
				printf("ERRO! O arquivo dos tamanhos não foi aberto!\n");
	}else{
				printf("O arquivo dos tamanhos foi aberto com sucesso!\n");
		}

	fclose(pont_tamanho_tabela);
}
