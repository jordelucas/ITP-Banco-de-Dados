void criarTabela() {
	FILE *pont_dados_tabela;
	FILE *pont_tamanho_tabela;
 	FILE *pont_tabelas;
	char * nomeTabela = malloc(20*sizeof(char));

	printf("----CRIAR TABELA----\n\n");

	fflush(stdin);
	printf("Nome da tabela: ");
	scanf("%s", nomeTabela);

	//Adicionar nova tabela a lista
	pont_tabelas = fopen("tabelas//listaTabelas.txt", "a");
	if (pont_tabelas == NULL){
		printf("ERRO! O arquivo de nomes não foi aberto!\n");
	}else{
		fprintf(pont_tabelas, "%s\n", nomeTabela);
	}
	fclose(pont_tabelas);

	//Criar arquivo de dados
	char * nome_dados_tabela = diretorioDados(nomeTabela);
	pont_dados_tabela = fopen(nome_dados_tabela, "a");
	if (pont_dados_tabela == NULL){
  	printf("ERRO! O arquivo de dados não foi aberto!\n");
	}
	fclose(pont_dados_tabela);
	free(pont_dados_tabela);

	//Criar arquivo dos tamanhos e definir atributos atributos
	char * nome_tamanho_tabela = diretorioTamanhos(nomeTabela);
	pont_tamanho_tabela = fopen(nome_tamanho_tabela, "a");
	if (pont_tamanho_tabela == NULL){
		printf("ERRO! O arquivo dos tamanhos não foi aberto!\n");
	}else{
		adicionarAtributo(pont_tamanho_tabela, nomeTabela);
	}
	fclose(pont_tamanho_tabela);
	free(nomeTabela);
	free(pont_tamanho_tabela);
}
