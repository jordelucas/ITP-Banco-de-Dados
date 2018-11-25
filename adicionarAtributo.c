typedef struct tamanhoAtr Tamanho_Atributo;
struct tamanhoAtr{
	char nome[20];
	int tamanho;
};

void adicionarAtributo (FILE * tabela, char * nomeTabela){
	Tamanho_Atributo atributo;
	char continuar = 's';
	int qtdAtr = 1; //auxiliar para identificar o primeiro atributo da tabela (chave primaria)
	int tipo;
//Adicionando atributos
	do {
		if(qtdAtr == 1){ //somente na primeira interação será solicitado a chave primaria
			printf("Nome da chave primária: ");
			fflush(stdin);
			scanf("%s", atributo.nome);
			atributo.tamanho = 4;
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
		printf("Deseja continuar adicionando atributos(s/n)?");
		scanf(" %c", &continuar);
	}while(continuar != 'n');
	printf("aqui\n");
}
