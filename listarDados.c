int listarDados(){
	cabecalho();
  /*ponteiros para o tipo arquivo*/
  FILE *pont_tabelas;
  FILE *pont_dados_tabela;
  FILE *pont_tamanho_tabela;

  /*ponteiros para identificação de onde se encontram os arquivos da tabela solicitada*/
  char * dados;
  char * tamanho;

  char * nomeTabela = (char*)malloc(21*sizeof(char));                           //reserva memória para identificação da tabela localizada no arquivo
  if(nomeTabela == NULL){
    printf("ERRO! Memória não alocada.");
    exit(0);
  }

  char * tabelaEscolhida = (char*)malloc(21*sizeof(char));                      //reserva memória para identificação da tabela cujo os dados serão listados
  if(tabelaEscolhida == NULL){
    printf("ERRO! Memória não alocada.");
    exit(0);
  }

  char respSN;                                                                  //variável para respostas Sim ou Não do usuário

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

  printf("----LISTAR DADOS----\n\n");

  /*Lista das tabelas cadastradas*/
  do{
    pont_tabelas = fopen("tabelas//listaTabelas.txt", "r");
    if (pont_tabelas == NULL){
      printf("ERRO! O arquivo de nomes não foi aberto.\n");
      exit(0);
    }else{
      if(fgets(nomeTabela, 20, pont_tabelas) == NULL){                          //Não havendo nada na primeira linha do arquivo, significa dizer que não há tabelas cadastradas
        printf("Não há tabelas cadastradas!\n");
        fflush(stdin);
        printf("Deseja cadastrar uma tabela(s/n)? ");
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
      }else{//Havendo linhas, são listados os nomes das tabelas com um indice ao lado
        ordem = 0;
        do {
          printf("%d. %s", ++ordem, nomeTabela);
        } while(fgets(nomeTabela, 20, pont_tabelas) != NULL);
        fflush(stdin);
        printf("\nQual tabela deseja listar dados? ");
        scanf("%d", &linha_escolhida);
        if (linha_escolhida < 1 || linha_escolhida > ordem) {
          cabecalho();
          printf("----LISTAR DADOS----\n\n");
          printf("*Opção Inválida!\n");
        }
        fclose(pont_tabelas);
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
      if (linha_atual == linha_escolhida) {                               //Busca pelo indice que representa o nome da tabela escolhida
        nomeTabela[strcspn(nomeTabela, "\n")] = 0;                        //retira o '\n'
        strcpy(tabelaEscolhida, nomeTabela);                              //Guarda-se o nome da tabale escolhida
        dados = diretorioDados(nomeTabela);                               //Obtemos o respectivo diretório do arquivo com os dados da tabale
        tamanho = diretorioTamanhos(nomeTabela);                          //Obtemos o respectivo diretório do arquivo com os tamanhos dos tipos de dados da tabela
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
    printf("ERRO! O arquivo de tamanhos não foi aberto!\n");
    exit(0);
  }else{
    while ( fread(&atr, sizeof(Tamanho_Atributo), 1, pont_tamanho_tabela) == 1 ) {//Leitura enquanto houver elementos da estrutura tamanho de atributo
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

  linha_atual = 0;

  /*Exibe os dados da tabela solicitada*/
  pont_dados_tabela = fopen(dados, "r");
  cabecalho();
  printf("----LISTAR DADOS----\n\n");
  printf("Listando dados da tabela '%s'\n\n", tabelaEscolhida);

  if (pont_dados_tabela == NULL){
    printf("ERRO! O arquivo de dados não foi aberto.\n");
    exit(0);
  }else{
    while (fread(&nl, sizeof(Nova_Linha), 1, pont_dados_tabela) == 1 ) {
      pont_tamanho_tabela = fopen(tamanho, "r");
      printf("************** %d ************\n", ++linha_atual);
      while (fread(&atr, sizeof(Tamanho_Atributo), 1, pont_tamanho_tabela) == 1 ) {
        switch(atr.tamanho){
          case 1:
          printf("%s: %c\n", atr.nome, nl.caracteres[_char]);
          _char++;
          break;
          case 4:
          printf("%s: %d\n", atr.nome, nl.inteiros[_inteiro]);
          _inteiro++;
          break;
          case 8:
          printf("%s: %lf\n", atr.nome, nl.doubles[_double]);
          _double++;
          break;
          case 20:
          printf("%s: %s\n", atr.nome, nl.strings[_string]);
          _string++;
          break;
          default:
          printf("\nTipo de dados desconhecido!\n");
          break;
        }
      }
      _inteiro = 0;
      _double = 0;
      _char = 0;
      _string = 0;
      fclose(pont_tamanho_tabela);
    }
  }
  fclose(pont_dados_tabela);
  free(dados);
  dados = NULL;
  free(tamanho);
  tamanho = NULL;
  free(tabelaEscolhida);
  tabelaEscolhida = NULL;

  printf("\nDeseja continuar listando dados das tabelas(s/n)? ");
  scanf(" %c", &respSN);
  if (respSN == 's') {
    listarDados();
  }
  return 0;
}
