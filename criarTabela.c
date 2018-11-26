void criarTabela() {
	cabecalho();
	/*ponteiros para o tipo arquivo*/
	FILE *pont_dados_tabela;
	FILE *pont_tamanho_tabela;
 	FILE *pont_tabelas;
  /*ponteiros para identificação de onde e como salvar os arquivos da tabela criada*/
	char * nome_tamanho_tabela;
	char * nome_dados_tabela;

	char * nomeTabela = (char*)malloc(21*sizeof(char));									//reserva memória para identificação da tabela a ser criada
	if(nomeTabela == NULL){
		printf("ERRO! Memória não alocada.");
		exit(0);
	}

	printf("----CRIAR TABELA----\n\n");

	fflush(stdin);
	printf("Nome da tabela: ");
	scanf("%s", nomeTabela);

	//Adiciona nova tabela a lista
	pont_tabelas = fopen("tabelas//listaTabelas.txt", "a");
	if (pont_tabelas == NULL){
		printf("ERRO! O arquivo de nomes não foi aberto.\n");
		exit(0);
	}else{
		fprintf(pont_tabelas, "%s\n", nomeTabela);
	}
	fclose(pont_tabelas);
	pont_tabelas = NULL;
	free(pont_tabelas);

	//Cria arquivo de dados
	nome_dados_tabela = diretorioDados(nomeTabela);
	pont_dados_tabela = fopen(nome_dados_tabela, "a");
	if (pont_dados_tabela == NULL){
  	printf("ERRO! O arquivo de dados não foi aberto.\n");
		exit(0);
	}
	fclose(pont_dados_tabela);
	pont_dados_tabela = NULL;
	free(pont_dados_tabela);
	pont_dados_tabela = NULL;
	free(nome_dados_tabela);

	//Cria arquivo dos tamanhos e define atributos a tabela
	nome_tamanho_tabela = diretorioTamanhos(nomeTabela);
	pont_tamanho_tabela = fopen(nome_tamanho_tabela, "a");
	if (pont_tamanho_tabela == NULL){
		printf("ERRO! O arquivo dos tamanhos não foi aberto!\n");
		exit(0);
	}else{
		adicionarAtributo(pont_tamanho_tabela, nomeTabela);
	}
	fclose(pont_tamanho_tabela);
	pont_tamanho_tabela = NULL;
	free(pont_tamanho_tabela);
	nomeTabela = NULL;
	free(nomeTabela);
	nome_tamanho_tabela = NULL;
	free(nome_tamanho_tabela);
}
