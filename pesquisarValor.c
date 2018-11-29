int pesquisarValor(){
	cabecalho();
	/*ponteiros para o tipo arquivo*/
	FILE *pont_tabelas;
	FILE *pont_temporario;
	FILE *pont_dados_tabela;
	FILE *pont_tamanho_tabela;

	/*ponteiros para identificação de onde se encontram os arquivos da tabela solicitada*/
	char * dados;
	char * tamanho;

	char * nomeTabela = (char*)malloc(21*sizeof(char));						//reserva memória para identificação da tabela localizada no arquivo
	if(nomeTabela == NULL){
		printf("ERRO! Memória não alocada.");
		exit(0);
	}

	char * tabelaEscolhida = (char*)malloc(21*sizeof(char));               //reserva memória para identificação da tabela que receberá uma linha
	if(tabelaEscolhida == NULL){
		printf("ERRO! Memória não alocada.");
		exit(0);
	}

	char * nomeAtributoEscolhido = (char*)malloc(21*sizeof(char));
	if(nomeAtributoEscolhido == NULL){
		printf("ERRO! Memória não alocada.");
		exit(0);
	}

	int tipoAtributoEscolhido;

	char respSN;                                                    //variável para respostas Sim ou Não do usuário

	/*Variáveis auxiliades para leitura de arquivos*/
	int linha_escolhida = 0;
	int ordem;
	int linha_atual = 1;

	/*Contadores de tipos de dados dos atributos da tabela*/
	int _inteiro = 0;
	int _double = 0;
	int _char = 0;
	int _string = 0;

	Tamanho_Atributo atr;

	int intLido;
	double doubleLido;

	printf("---PESQUISAR VALOR--\n\n");

	/*Lista das tabelas cadastradas*/
	do{
		pont_tabelas = fopen("tabelas//listaTabelas.txt", "r");
		if (pont_tabelas == NULL){
			printf("ERRO! O arquivo de nomes não foi aberto.\n");
			exit(0);
		}else{
			if(fgets(nomeTabela, 20, pont_tabelas) == NULL){                  //Não havendo nada na primeira linha do arquivo, significa dizer que não há tabelas cadastradas
				printf("Não há tabelas cadastradas!\n");
				printf("Deseja cadastrar uma tabela(s/n)? ");
				fflush(stdin);
				scanf(" %c", &respSN);
				if (respSN == 's') {
					fclose(pont_tabelas);
					free(nomeTabela);
					nomeTabela = NULL;
					free(tabelaEscolhida);
					tabelaEscolhida = NULL;
					criarTabela();
					return -1;
				}else{
					fclose(pont_tabelas);
					free(nomeTabela);
					nomeTabela = NULL;
					free(tabelaEscolhida);
					tabelaEscolhida = NULL;
					return -1;
				}
			}else{                                                             //Havendo linhas, são listados os nomes das tabelas com um indice ao lado
				ordem = 0;
				do {
					printf("%d. %s", ++ordem, nomeTabela);
				} while(fgets(nomeTabela, 20, pont_tabelas) != NULL);
				fflush(stdin);
				printf("\nEm qual tabela você deseja pesquisar valor? ");
				scanf("%d", &linha_escolhida);
				if (linha_escolhida < 1 || linha_escolhida > ordem) {            //Controle de que o indice solicitado seja um dos exibidos na tela
					cabecalho();
					printf("---PESQUISAR VALOR--\n\n");
					printf("*Opção Inválida!\n");
					fclose(pont_tabelas);
				}else{
					fclose(pont_tabelas);
				}
			}
		}
	} while (linha_escolhida < 1 || linha_escolhida > ordem);


  /*Localização dos arquivos da tabela solicidata*/
  pont_tabelas = fopen("tabelas//listaTabelas.txt", "r");
  if (pont_tabelas == NULL){
		printf("ERRO! O arquivo de nomes não foi aberto.\n");
    exit(0);
	}else{
    while(fgets(nomeTabela, 20, pont_tabelas) != NULL){
      if (linha_atual == linha_escolhida) {                              //Busca pelo indice que representa o nome da tabela escolhida
        nomeTabela[strcspn(nomeTabela, "\n")] = 0;                       //retira o '\n'
        strcpy(tabelaEscolhida, nomeTabela);                             //Guarda-se o nome da tabale escolhida
        dados = diretorioDados(nomeTabela);                              //Obtemos o respectivo diretório do arquivo com os dados da tabale
        tamanho = diretorioTamanhos(nomeTabela);                         //Obtemos o respectivo diretório do arquivo com os tamanhos dos tipos de dados da tabela
        linha_atual++;
        continue;
      }
      linha_atual++;
    }
  }
  fclose(pont_tabelas);
  free(nomeTabela);
  nomeTabela = NULL;

  /*Contagem da quantidade de cada tipo de dados da tabela*/
  	pont_tamanho_tabela = fopen(tamanho, "r");
  	if (pont_tamanho_tabela == NULL){
		printf("ERRO! O arquivo de tamanhos não foi aberto.\n");
    	exit(0);
	}else{
    	while ( fread(&atr, sizeof(Tamanho_Atributo), 1, pont_tamanho_tabela) == 1 ) {        //Leitura enquanto houver elementos da estrutura tamanho de atributo
    		switch(atr.tamanho){
        		case 1:
          			_char++;
          			break;
        		case 4:
         	 		_inteiro++;
          			break;
        		case 8:
        	  		_double++;
          			break;
        		case 20:
          			_string++;
          			break;
        		default:
          			printf("\nTipo de dados desconhecido!\n");
          			break;
      		}
    	}
  	}

  fclose(pont_tamanho_tabela);
  /*Define estrutura nova linha, que possui arrays que guardam os atributos da linha a partir dos tipos de dados*/
  typedef struct linha Nova_Linha;
  struct linha{
    int inteiros[_inteiro];
    char caracteres[_char];
    double doubles[_double];
  	char strings[_string][30];
  };
  Nova_Linha nl;

  /*Contadores dos tipos de dados*/
  _inteiro = 0;
  _double = 0;
  _char = 0;
  _string = 0;

  cabecalho();
  printf("---PESQUISAR VALOR--\n\n");
  printf("Pesquisando valor na tabela '%s'!\n", tabelaEscolhida);
  printf("Segue a lista de atributos:\n\n");

	do{
		pont_tamanho_tabela = fopen(tamanho, "r");
		if (pont_tamanho_tabela == NULL){
			printf("ERRO! O arquivo de tamanhos não foi aberto.\n");
			exit(0);
		}else{                                                            //Havendo linhas, são listados os nomes das tabelas com um indice ao lado
          	ordem = 0;
  			while (fread(&atr, sizeof(Tamanho_Atributo), 1, pont_tamanho_tabela) == 1 ) {             //Leitura enquanto houver elementos da estrutura tamanho de atributo da respectiva tabela
    			printf("%d. %s\n", ++ordem, atr.nome);
  			}
        	fflush(stdin);
        	printf("\nEscolha um dos atributos para realizar pesquisa? ");
        	scanf("%d", &linha_escolhida);
        	if (linha_escolhida < 1 || linha_escolhida > ordem) {            //Controle de que o indice solicitado seja um dos exibidos na tela
          		cabecalho();
  		  		printf("---PESQUISAR VALOR--\n\n");
  		  		printf("Pesquisando valor na tabela '%s'!\n", tabelaEscolhida);
  				printf("Segue a lista de atributos:\n\n");
          		printf("*Opção Inválida!\n");
          		fclose(pont_tamanho_tabela);
        	}else{
          		fclose(pont_tamanho_tabela);
        	}
      	}
    } while (linha_escolhida < 1 || linha_escolhida > ordem);
	
  /*Localização dos arquivos da tabela solicidata*/
	pont_tamanho_tabela = fopen(tamanho, "r");
	if (pont_tamanho_tabela == NULL){
		printf("ERRO! O arquivo de tamanhos não foi aberto.\n");
		exit(0);
	}else{
		linha_atual = 1;
		while (fread(&atr, sizeof(Tamanho_Atributo), 1, pont_tamanho_tabela) == 1 ) {
			if (linha_atual == linha_escolhida) {
        		linha_atual++;
        		strcpy(nomeAtributoEscolhido, atr.nome);
        		tipoAtributoEscolhido = atr.tamanho;
        		continue;
			}
      		linha_atual++;
    	}
  	}
  	fclose(pont_tamanho_tabela);

	cabecalho();
	printf("---PESQUISAR VALOR--\n\n");
	printf("Pesquisando valores de '%s' na tabela '%s'!\n", nomeAtributoEscolhido, tabelaEscolhida);
	printf("Escolha uma das opções: \n\n");
	
	if (tipoAtributoEscolhido == 4 || tipoAtributoEscolhido == 8){
		do{
			printf("1. valores maior que o valor informado\n");
			printf("2. valores maior ou igual que o valor informado\n");
			printf("3. valores igual o valor informado\n");
			printf("4. valores menor que o valor informado\n");
			printf("5. valores menor ou igual que o valor informado\n");
			fflush(stdin);
			printf("\nOpção: ");
			scanf("%d", &linha_escolhida);
			if (linha_escolhida < 1 || linha_escolhida > 5) {            //Controle de que o indice solicitado seja um dos exibidos na tela
				cabecalho();
				printf("---PESQUISAR VALOR--\n\n");
				printf("Pesquisando valores de '%s' na tabela '%s'!\n", nomeAtributoEscolhido, tabelaEscolhida);
				printf("Escolha uma opcao: \n\n");
				printf("*Opção Inválida!\n");
			}
		} while (linha_escolhida < 1 || linha_escolhida > 5);

		cabecalho();
		printf("---PESQUISAR VALOR--\n\n");
		printf("Pesquisando valores de '%s' na tabela '%s'!\n\n", nomeAtributoEscolhido, tabelaEscolhida);

		switch(linha_escolhida){
			case 1:
				pont_dados_tabela = fopen(dados, "r");
				printf("--Valores maiores que o valor informado--\n");
				if (tipoAtributoEscolhido == 4) {
					printf("Informe um numero para comparar: ");
					scanf("%d", &intLido);
					printf("\n");
					while (fread(&nl, sizeof(Nova_Linha), 1, pont_dados_tabela) == 1 ) {
						pont_tamanho_tabela = fopen(tamanho, "r");
						while (fread(&atr, sizeof(Tamanho_Atributo), 1, pont_tamanho_tabela) == 1 ) {
							if (strcmp (atr.nome, nomeAtributoEscolhido) == 0){
								if (intLido < nl.inteiros[_inteiro]){
									printf("**************************\n");
									printf("-- Chave Primária: %d\n", nl.inteiros[0]);
									printf("-- %s: %d\n", nomeAtributoEscolhido, nl.inteiros[_inteiro]);
								}
							}
							_inteiro++;
							_double++;
						}
						_inteiro = 0;
						_double = 0;
						_char = 0;
						_string = 0;
						fclose(pont_tamanho_tabela);
					}
				}else{
					printf("Informe um numero para comparar: ");
					scanf("%lf", &doubleLido);
					printf("\n");
					while (fread(&nl, sizeof(Nova_Linha), 1, pont_dados_tabela) == 1 ) {
						pont_tamanho_tabela = fopen(tamanho, "r");
						while (fread(&atr, sizeof(Tamanho_Atributo), 1, pont_tamanho_tabela) == 1 ) {
							if (strcmp (atr.nome, nomeAtributoEscolhido) == 0){
								if (doubleLido < nl.doubles[_double]){
									printf("**************************\n");
									printf("-- Chave Primária: %d\n", nl.inteiros[0]);
									printf("-- %s: %lf\n", nomeAtributoEscolhido, nl.doubles[_double]);
								}
							}
							_inteiro++;
							_double++;
						}
						_inteiro = 0;
						_double = 0;
						_char = 0;
						_string = 0;
						fclose(pont_tamanho_tabela);
					}

				}
				pont_dados_tabela;
				break;
			case 2:
				pont_dados_tabela = fopen(dados, "r");
				printf("--Valores maiores ou iguais que o valor informado--\n");
				if (tipoAtributoEscolhido == 4) {
					printf("Informe um numero para comparar: ");
					scanf("%d", &intLido);
					printf("\n");
					while (fread(&nl, sizeof(Nova_Linha), 1, pont_dados_tabela) == 1 ) {
						pont_tamanho_tabela = fopen(tamanho, "r");
						while (fread(&atr, sizeof(Tamanho_Atributo), 1, pont_tamanho_tabela) == 1 ) {
							if (strcmp (atr.nome, nomeAtributoEscolhido) == 0){
								if (intLido <= nl.inteiros[_inteiro]){
									printf("**************************\n");
									printf("-- Chave Primária: %d\n", nl.inteiros[0]);
									printf("-- %s: %d\n", nomeAtributoEscolhido, nl.inteiros[_inteiro]);
								}
							}
							_inteiro++;
							_double++;
						}
						_inteiro = 0;
						_double = 0;
						_char = 0;
						_string = 0;
						fclose(pont_tamanho_tabela);
					}
				}else{
					printf("Informe um numero para comparar: ");
					scanf("%lf", &doubleLido);
					printf("\n");
					while (fread(&nl, sizeof(Nova_Linha), 1, pont_dados_tabela) == 1 ) {
						pont_tamanho_tabela = fopen(tamanho, "r");
						while (fread(&atr, sizeof(Tamanho_Atributo), 1, pont_tamanho_tabela) == 1 ) {
							if (strcmp (atr.nome, nomeAtributoEscolhido) == 0){
								if (doubleLido <= nl.doubles[_double]){
									printf("**************************\n");
									printf("-- Chave Primária: %d\n", nl.inteiros[0]);
									printf("-- %s: %lf\n", nomeAtributoEscolhido, nl.doubles[_double]);
								}
							}
							_inteiro++;
							_double++;
						}
						_inteiro = 0;
						_double = 0;
						_char = 0;
						_string = 0;
						fclose(pont_tamanho_tabela);
					}

				}
				pont_dados_tabela;
				break;
			case 3:
				pont_dados_tabela = fopen(dados, "r");
				printf("--Valores iguais ao valor informado--\n");
				if (tipoAtributoEscolhido == 4) {
					printf("Informe um numero para comparar: ");
					scanf("%d", &intLido);
					printf("\n");
					while (fread(&nl, sizeof(Nova_Linha), 1, pont_dados_tabela) == 1 ) {
						pont_tamanho_tabela = fopen(tamanho, "r");
						while (fread(&atr, sizeof(Tamanho_Atributo), 1, pont_tamanho_tabela) == 1 ) {
							if (strcmp (atr.nome, nomeAtributoEscolhido) == 0){
								if (intLido == nl.inteiros[_inteiro]){
									printf("**************************\n");
									printf("-- Chave Primária: %d\n", nl.inteiros[0]);
									printf("-- %s: %d\n", nomeAtributoEscolhido, nl.inteiros[_inteiro]);
								}
							}
							_inteiro++;
							_double++;
						}
						_inteiro = 0;
						_double = 0;
						_char = 0;
						_string = 0;
						fclose(pont_tamanho_tabela);
					}
				}else{
					printf("Informe um numero para comparar: ");
					scanf("%lf", &doubleLido);
					printf("\n");
					while (fread(&nl, sizeof(Nova_Linha), 1, pont_dados_tabela) == 1 ) {
						pont_tamanho_tabela = fopen(tamanho, "r");
						while (fread(&atr, sizeof(Tamanho_Atributo), 1, pont_tamanho_tabela) == 1 ) {
							if (strcmp (atr.nome, nomeAtributoEscolhido) == 0){
								if (doubleLido == nl.doubles[_double]){
									printf("**************************\n");
									printf("-- Chave Primária: %d\n", nl.inteiros[0]);
									printf("-- %s: %lf\n", nomeAtributoEscolhido, nl.doubles[_double]);
								}
							}
							_inteiro++;
							_double++;
						}
						_inteiro = 0;
						_double = 0;
						_char = 0;
						_string = 0;
						fclose(pont_tamanho_tabela);
					}

				}
				pont_dados_tabela;
				break;
			case 4:
				pont_dados_tabela = fopen(dados, "r");
				printf("--Valores menores que o valor informado--\n");
				if (tipoAtributoEscolhido == 4) {
					printf("Informe um numero para comparar: ");
					scanf("%d", &intLido);
					printf("\n");
					while (fread(&nl, sizeof(Nova_Linha), 1, pont_dados_tabela) == 1 ) {
						pont_tamanho_tabela = fopen(tamanho, "r");
						while (fread(&atr, sizeof(Tamanho_Atributo), 1, pont_tamanho_tabela) == 1 ) {
							if (strcmp (atr.nome, nomeAtributoEscolhido) == 0){
								if (intLido > nl.inteiros[_inteiro]){
									printf("**************************\n");
									printf("-- Chave Primária: %d\n", nl.inteiros[0]);
									printf("-- %s: %d\n", nomeAtributoEscolhido, nl.inteiros[_inteiro]);
								}
							}
							_inteiro++;
							_double++;
						}
						_inteiro = 0;
						_double = 0;
						_char = 0;
						_string = 0;
						fclose(pont_tamanho_tabela);
					}
				}else{
					printf("Informe um numero para comparar: ");
					scanf("%lf", &doubleLido);
					printf("\n");
					while (fread(&nl, sizeof(Nova_Linha), 1, pont_dados_tabela) == 1 ) {
						pont_tamanho_tabela = fopen(tamanho, "r");
						while (fread(&atr, sizeof(Tamanho_Atributo), 1, pont_tamanho_tabela) == 1 ) {
							if (strcmp (atr.nome, nomeAtributoEscolhido) == 0){
								if (doubleLido > nl.doubles[_double]){
									printf("**************************\n");
									printf("-- Chave Primária: %d\n", nl.inteiros[0]);
									printf("-- %s: %lf\n", nomeAtributoEscolhido, nl.doubles[_double]);
								}
							}
							_inteiro++;
							_double++;
						}
						_inteiro = 0;
						_double = 0;
						_char = 0;
						_string = 0;
						fclose(pont_tamanho_tabela);
					}

				}
				pont_dados_tabela;
				break;
			case 5:
				pont_dados_tabela = fopen(dados, "r");
				printf("--Valores menor ou igual que o valor informado--\n");
				if (tipoAtributoEscolhido == 4) {
					printf("Informe um numero para comparar: ");
					scanf("%d", &intLido);
					printf("\n");
					while (fread(&nl, sizeof(Nova_Linha), 1, pont_dados_tabela) == 1 ) {
						pont_tamanho_tabela = fopen(tamanho, "r");
						while (fread(&atr, sizeof(Tamanho_Atributo), 1, pont_tamanho_tabela) == 1 ) {
							if (strcmp (atr.nome, nomeAtributoEscolhido) == 0){
								if (intLido >= nl.inteiros[_inteiro]){
									printf("**************************\n");
									printf("-- Chave Primária: %d\n", nl.inteiros[0]);
									printf("-- %s: %d\n", nomeAtributoEscolhido, nl.inteiros[_inteiro]);
								}
							}
							_inteiro++;
							_double++;
						}
						_inteiro = 0;
						_double = 0;
						_char = 0;
						_string = 0;
						fclose(pont_tamanho_tabela);
					}
				}else{
					printf("Informe um numero para comparar: ");
					scanf("%lf", &doubleLido);
					printf("\n");
					while (fread(&nl, sizeof(Nova_Linha), 1, pont_dados_tabela) == 1 ) {
						pont_tamanho_tabela = fopen(tamanho, "r");
						while (fread(&atr, sizeof(Tamanho_Atributo), 1, pont_tamanho_tabela) == 1 ) {
							if (strcmp (atr.nome, nomeAtributoEscolhido) == 0){
								if (doubleLido >= nl.doubles[_double]){
									printf("**************************\n");
									printf("-- Chave Primária: %d\n", nl.inteiros[0]);
									printf("-- %s: %lf\n", nomeAtributoEscolhido, nl.doubles[_double]);
								}
							}
							_inteiro++;
							_double++;
						}
						_inteiro = 0;
						_double = 0;
						_char = 0;
						_string = 0;
						fclose(pont_tamanho_tabela);
					}

				}
				pont_dados_tabela;
				break;
			default:
				printf("Opção Inválida!\n");
				break;
		}
	}else{
		printf("ok\n");
	}

	printf("\nDeseja continuar pesquisando valores(s/n)? ");
  	scanf(" %c", &respSN);
  	if (respSN == 's') {
    	pesquisarValor();
  	}
  	return 0;
}