int criarTabela() {
	cabecalho();
	/*--Ponteiros para o tipo arquivo--*/
	FILE *pont_dados_tabela;
	FILE *pont_tamanho_tabela;
	FILE *pont_tabelas;

  /*--Ponteiros para identificação de onde e como salvar os arquivos da tabela criada--*/
	char * nome_tamanho_tabela;
	char * nome_dados_tabela;

	char * nomeTabela = (char*)malloc(21*sizeof(char));									//Reserva memória para definição do nome da tabela
	if(nomeTabela == NULL){
		printf("ERRO! Memória não alocada.");
		exit(0);
	}

	char * texto_str = (char*) malloc(21*sizeof(char));                //Reserva memória para identificação dos nomes de tabelas contidos no arquivo arquivo
	if(texto_str == NULL){
		printf("ERRO! Memória não alocada.");
		exit(0);
	}

  char respSN;                                                //variável para respostas Sim ou Não do usuário

  printf("----CRIAR TABELA----\n\n");

  fflush(stdin);
  printf("Nome da tabela: ");
  scanf("%s", nomeTabela);

	/*--Verifica se o nome fornecido para a tabela é único--*/
  pont_tabelas = fopen("tabelas//listaTabelas.txt", "r");
  if (pont_tabelas == NULL){
  	printf("ERRO! O arquivo de nomes não foi aberto.\n");
  	exit(0);
  }else{
		while (fgets(texto_str, 21, pont_tabelas) != NULL){           //Não havendo nada na primeira linha do arquivo, significa dizer que não há tabelas cadastradas
			texto_str[strcspn(texto_str, "\n")] = 0;
			if (strcmp (texto_str, nomeTabela) == 0){
				printf("\nO nome fornecido já foi cadastrado em outra tabela!\n");
				fflush(stdin);
				printf("Deseja inserir outro nome(s/n)? ");
				scanf(" %c", &respSN);
				if (respSN == 's') {
					fclose(pont_tabelas);
					free(texto_str);
					texto_str = NULL;
					free(nomeTabela);
					nomeTabela = NULL;
					criarTabela();
					return -1;
				}else{
					return -1;
				}
			}
		}
	}
	fclose(pont_tabelas);
	free(texto_str);
	texto_str = NULL;

	/*--Adiciona nova tabela a lista de nomes--*/
	pont_tabelas = fopen("tabelas//listaTabelas.txt", "a");
	if (pont_tabelas == NULL){
		printf("ERRO! O arquivo de nomes não foi aberto.\n");
		exit(0);
	}else{
		fprintf(pont_tabelas, "%s\n", nomeTabela);
	}
	fclose(pont_tabelas);

	/*--Cria arquivo de dados da tabela solicitada--*/
	nome_dados_tabela = diretorioDados(nomeTabela);
	pont_dados_tabela = fopen(nome_dados_tabela, "a");
	if (pont_dados_tabela == NULL){
		printf("ERRO! O arquivo de dados não foi aberto.\n");
		exit(0);
	}
	fclose(pont_dados_tabela);
	free(nome_dados_tabela);
	pont_dados_tabela = NULL;

	/*--Cria arquivo dos tamanhos e define atributos a tabela--*/
	nome_tamanho_tabela = diretorioTamanhos(nomeTabela);
	pont_tamanho_tabela = fopen(nome_tamanho_tabela, "a");
	if (pont_tamanho_tabela == NULL){
		printf("ERRO! O arquivo dos tamanhos não foi aberto!\n");
		exit(0);
	}else{
		adicionarAtributo(pont_tamanho_tabela, nomeTabela);
	}
	fclose(pont_tamanho_tabela);
	free(nomeTabela);
	nomeTabela = NULL;
	free(nome_tamanho_tabela);
	nome_tamanho_tabela = NULL;

	printf("\n*A tabela foi criada e adicionada ao banco!*\n");
	fflush(stdin);
	printf("Deseja continuar adicionando tabelas(s/n)? ");
	scanf(" %c", &respSN);
	if (respSN == 's') {
		criarTabela();
		return -1;
	}
	return 0;
}
