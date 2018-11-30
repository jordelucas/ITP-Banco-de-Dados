/*Estrutura para identificação dos atributos e tipos de dados*/
typedef struct tamanhoAtr Tamanho_Atributo;
struct tamanhoAtr{
	char nome[20];
	int tamanho;
};

void adicionarAtributo (FILE * tabela, char * nomeTabela){
	Tamanho_Atributo atributo;
	char continuar = 's';
	int qtdAtr = 1;															//auxiliar para identificar o primeiro atributo da tabela (chave primaria)
	int tipo;																		//auxiliar para identificar tipo de dados

	/*--Adiciona atributos--*/
	do {
		if(qtdAtr == 1){ 													//somente na primeira interação será solicitada a chave primaria
			printf("Nome da chave primária: ");
			fflush(stdin);
			scanf("%s", atributo.nome);
			atributo.tamanho = INT;
		}else{
			cabecalho();
			printf("----CRIAR TABELA----\n\n");
			printf("Adicionando atributo a tabela '%s'\n", nomeTabela);
			fflush(stdin);
			printf("Nome do atributo: ");
			scanf("%s", atributo.nome);

			fflush(stdin);
			printf("\n--TIPOS DE DADOS--\n");
			printf("1- Char\n");
			printf("2- Int\n");
			printf("3- Float\n");
			printf("4- Double\n");
			printf("5- String\n");
			printf("\nEscolha o tipo de dado do atributo '%s': ", atributo.nome);
			scanf("%d", &tipo);

			switch(tipo){
				case 1:
				atributo.tamanho = CHAR;
				break;
				case 2:
				atributo.tamanho = INT;
				break;
				case 3:
				atributo.tamanho = FLOAT;
				break;
				case 4:
				atributo.tamanho = DOUBLE;
				break;
				case 5:
				atributo.tamanho = STRING;
				break;
				default:
				printf("\nOpção Inválida!\n");
				break;
			}
		}
		if(fwrite(&atributo, sizeof(Tamanho_Atributo), 1, tabela) != 1){
			printf("ERRO! Não foi possível fazer a escrita do arquivo.\n");
			exit(0);
		}
		qtdAtr++;
		fflush(stdin);
		printf("Deseja continuar adicionando atributos(s/n)? ");
		scanf(" %c", &continuar);
	}while(continuar != 'n');
}
