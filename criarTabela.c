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

	char * texto_str = (char*) malloc(21*sizeof(char));                //reserva memória para verificacao se o nome fornecido para a nova tabela encontra-se disponivel
  if(texto_str == NULL){
		printf("ERRO! Memória não alocada.");
		exit(0);
	}

  char respSN;                                                //variável para respostas Sim ou Não do usuário

	printf("----CRIAR TABELA----\n\n");

	fflush(stdin);
	printf("Nome da tabela: ");
	scanf("%s", nomeTabela);

	pont_tabelas = fopen("tabelas//listaTabelas.txt", "r");
	if (pont_tabelas == NULL){
		printf("ERRO! O arquivo de nomes não foi aberto.\n");
		exit(0);
	}else{
		if(fgets(texto_str, 21, pont_tabelas) == NULL){           //Não havendo nada na primeira linha do arquivo, significa dizer que não há tabelas cadastradas
			printf("ok\n");
		}else{
			do{
				if (texto_str == nomeTabela) {
					printf("\nO nome solicitado já esta cadastrado em outra tabela!\n");
				}
			}while (fgets(texto_str, 21, pont_tabelas) != NULL);
		}
	}
	fclose(pont_tabelas);

	//Adiciona nova tabela a lista
	pont_tabelas = fopen("tabelas//listaTabelas.txt", "a");
	if (pont_tabelas == NULL){
		printf("ERRO! O arquivo de nomes não foi aberto.\n");
		exit(0);
	}else{
		fprintf(pont_tabelas, "%s\n", nomeTabela);
	}
	fclose(pont_tabelas);

	//Cria arquivo de dados
	nome_dados_tabela = diretorioDados(nomeTabela);
	pont_dados_tabela = fopen(nome_dados_tabela, "a");
	if (pont_dados_tabela == NULL){
  	printf("ERRO! O arquivo de dados não foi aberto.\n");
		exit(0);
	}
	fclose(pont_dados_tabela);
	free(nome_dados_tabela);
	pont_dados_tabela = NULL;

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
	free(nomeTabela);
	nomeTabela = NULL;
	free(nome_tamanho_tabela);
	nome_tamanho_tabela = NULL;

	printf("\n*A tabela foi criada e adicionada ao banco!*\n");
	/*fflush(stdin);
	printf("Deseja continuar adicionando tabelas(s/n)? ");
	scanf(" %c", &respSN);
	if (respSN == 's') {
		criarTabela();
	}*/
}
