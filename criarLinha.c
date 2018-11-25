int criarLinha(){
  FILE *pont_tabelas;
  FILE *pont_dados_tabela;
  FILE *pont_tamanho_tabela;

  char * dados;
  char * tamanho;

  char * nomeTabela = malloc(20*sizeof(char));
  char * tabelaEscolhida = malloc(20*sizeof(char));
  char novaTabela;

  int linha_escolhida = 0;
  int ordem = 0;
  int linha_atual = 1;

  int _inteiro = 0;
  int _double = 0;
  int _char = 0;
  int _string = 0;

  Tamanho_Atributo atr;

  printf("---ADICIONAR LINHA--\n\n");

  do{
    pont_tabelas = fopen("tabelas//listaTabelas.txt", "r");
    if (pont_tabelas == NULL){
  		printf("ERRO! O arquivo de nomes não foi aberto!\n");
  	}else{
      if(fgets(nomeTabela, 20, pont_tabelas) == NULL){
        printf("Não há tabelas cadastradas!\n");
        printf("Deseja cadastrar uma tabela(s/n)? ");
        fflush(stdin);
        scanf(" %c", &novaTabela);
        if (novaTabela == 's') {
          fclose(pont_tabelas);
          cabecalho();
          criarTabela();
          return -1;
        }else{
          fclose(pont_tabelas);
          return -1;
        }
      }else{
        do {
          printf("%d. %s", ++ordem, nomeTabela);
        } while(fgets(nomeTabela, 20, pont_tabelas) != NULL);
        fflush(stdin);
        printf("\nQual tabela deseja adicionar linha? ");
        scanf("%d", &linha_escolhida);
        if (linha_escolhida < 1 || linha_escolhida > ordem) {
          cabecalho();
          ordem = 0;
          printf("---ADICIONAR LINHA--\n\n");
          printf("*Opção Inválida!\n");
          fclose(pont_tabelas);
        }else{
          fclose(pont_tabelas);
        }
      }
    }
  } while (linha_escolhida < 1 || linha_escolhida > ordem);

  pont_tabelas = fopen("tabelas//listaTabelas.txt", "r");
  if (pont_tabelas == NULL){
		printf("ERRO! O arquivo de nomes não foi aberto!\n");
	}else{
    while(fgets(nomeTabela, 20, pont_tabelas) != NULL){
      if (linha_atual == linha_escolhida) {
        nomeTabela[strcspn(nomeTabela, "\n")] = 0; //retira o '\n'
        strcpy(tabelaEscolhida, nomeTabela);
        dados = diretorioDados(nomeTabela);
        tamanho = diretorioTamanhos(nomeTabela);
        linha_atual++;
        continue;
      }
      linha_atual++;
    }
  }
  fclose(pont_tabelas);
  free(nomeTabela);

  pont_tamanho_tabela = fopen(tamanho, "r");
  if (pont_tamanho_tabela == NULL){
		printf("ERRO! O arquivo de nomes não foi aberto!\n");
	}else{
    //contagem de quantos de cada tipo existe na tabela escolhida
    while ( fread(&atr, sizeof(Tamanho_Atributo), 1, pont_tamanho_tabela) == 1 ) {
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
        case 30:
          _string++;
          break;
        default:
          printf("\nTipo de dados desconhecido!\n");
          break;
      }
    }
  }
  fclose(pont_tamanho_tabela);

  //criação da estrutura com arrays com a quantidade de tipos de dados
  typedef struct linha Nova_Linha;
  struct linha{
    int inteiros[_inteiro];
    char caracteres[_char];
    double doubles[_double];
  	char strings[_string][30];
  };

  Nova_Linha nl;
  _inteiro = 0;
  _double = 0;
  _char = 0;
  _string = 0;

  pont_tamanho_tabela = fopen(tamanho, "r");
  cabecalho();
  printf("---ADICIONAR LINHA--\n\n");
  printf("Adicionando linha a tabela '%s'\n", tabelaEscolhida);

  while (fread(&atr, sizeof(Tamanho_Atributo), 1, pont_tamanho_tabela) == 1 ) {
    switch(atr.tamanho){
  		case 1:
        fflush(stdin);
        printf("%s (char): ", atr.nome);
        scanf(" %c", &nl.caracteres[_char]);
        _char++;
  			break;
  		case 4:
        fflush(stdin);
        printf("%s (int): ", atr.nome);
        scanf("%d", &nl.inteiros[_inteiro]);
        _inteiro++;
  			break;
  		case 8:
        fflush(stdin);
        printf("%s (double): ", atr.nome);
        scanf("%lf", &nl.doubles[_double]);
        _double++;
  			break;
  		case 30:
        fflush(stdin);
        printf("%s (string): ", atr.nome);
        fflush(stdin);
        scanf("%s", nl.strings[_string]);
        _string++;
  			break;
  		default:
  			printf("\nTipo de dados desconhecido!\n");
  			break;
    }
  }
  fclose(pont_tamanho_tabela);
  free(tamanho);
  free(tabelaEscolhida);

  pont_dados_tabela = fopen(dados, "a");
  if(fwrite(&nl, sizeof(Nova_Linha), 1, pont_dados_tabela) !=1){
    printf("Erro na escrita do arquivo!\n");
  }
  fclose(pont_dados_tabela);
  free(dados);
  return 0;
}
