#include <stdio.h>

void criarTabela() {
	FILE *pont_dados_tabela;
	FILE *pont_tamanho_tabela;

	char nome_tabela[15];
	printf("Nome: ");
	scanf("%s", nome_tabela);

	pont_dados_tabela = fopen(("%s.txt", nome_tabela), "w");

	if (pont_dados_tabela == NULL){
    		printf("ERRO! O arquivo não foi aberto!\n");
	}else{
     		printf("O arquivo foi aberto com sucesso!");
   	}

	fclose(pont_dados_tabela);
}
