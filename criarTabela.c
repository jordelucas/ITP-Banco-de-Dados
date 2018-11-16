#include <stdio.h>
#include <string.h> //para usar a função que concatena strings

void adicionarAtributo (FILE * tabela);
typedef struct tamanhoAtr Tamanho_Atributo;

struct tamanhoAtr{
	char nome[20];
	int tamanho;
};

void criarTabela() {
	FILE *pont_dados_tabela;
	FILE *pont_tamanho_tabela;
 	FILE *pont_tabelas;
	char nome_dados_tabela[35] = "";
	char nome_tamanho_tabela[35] = "";
	char nome[15];

	printf("----CRIAR TABELA----\n\n");

	fflush(stdin);
	printf("Nome da tabela: ");
	scanf("%s", nome);

	strcat(nome_dados_tabela, "dados//");
	strcat(nome_dados_tabela, nome);
	strcat(nome_dados_tabela, "_dados.txt");
	strcat(nome_tamanho_tabela, "tamanhos//");
	strcat(nome_tamanho_tabela, nome);
	strcat(nome_tamanho_tabela, "_tamanho.txt");

	//Adicionar nova tabela a lista
	pont_tabelas = fopen("tabelas//listaTabelas.txt", "ab");

	if (pont_tabelas == NULL){
		printf("ERRO! O arquivo não foi aberto!\n");
	}else{
		fprintf(pont_tabelas, "%s\n", nome);
	}

	fclose(pont_tabelas);

	//Criar arquivo de dados
	pont_dados_tabela = fopen(nome_dados_tabela, "ab");

	if (pont_dados_tabela == NULL){
  	printf("ERRO! O arquivo de dados não foi aberto!\n");
	}

	fclose(pont_dados_tabela);

	//Criar arquivo dos tamanhos e definir atributos atributos
	pont_tamanho_tabela = fopen(nome_tamanho_tabela, "ab");

	if (pont_tamanho_tabela == NULL){
		printf("ERRO! O arquivo dos tamanhos não foi aberto!\n");
	}else{
		adicionarAtributo(pont_tamanho_tabela);
	}

	fclose(pont_tamanho_tabela);

}

void adicionarAtributo (FILE * tabela){
	Tamanho_Atributo atributo;
	char continuar = 's';
	int qtdAtr = 1; //quantidade de atributos
	int tipo;
//Adicionando atributos
	do {
		if(qtdAtr == 1){
			fflush(stdin);
			printf("\nNome da chave primária: ");
			scanf("%s", atributo.nome);
			atributo.tamanho = 4;

		}else{

			cabecalho();
			printf("----CRIAR TABELA----\n\n");

			fflush(stdin);
			printf("\nNome do atributo: ");
			scanf("%s", atributo.nome);

			fflush(stdin);
			printf("\n--TIPOS DE DADOS--\n");
			printf("1- Char\n");
			printf("2- Int\n");
			printf("3- Float\n");
			printf("4- Double\n");
			printf("5- String\n");
			printf("\nEscolha o tipo de dado do atributo %s: ", atributo.nome);
			scanf("%d", &tipo);

			switch(tipo){
				case 1:
					atributo.tamanho = 1;
					break;
				case 2:
					atributo.tamanho = 4;
					break;
				case 3:
					atributo.tamanho = 8;
					break;
				case 4:
					atributo.tamanho = 8;
					break;
				case 5:
					atributo.tamanho = 30;
					break;
				default:
					printf("\nOpção Inválida!\n");
					break;
			}
		}
		fwrite(&atributo, sizeof(Tamanho_Atributo), 1, tabela);
		qtdAtr++;
		fflush(stdin);
		printf("\nDeseja continuar adicionando atributos(s/n)?");
		scanf(" %c", &continuar);
	}while(continuar != 'n');
}
