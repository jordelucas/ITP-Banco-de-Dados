int apagarTabela(){
  cabecalho();
  /*ponteiros para o tipo arquivo*/
  FILE * pont_tabelas;
  FILE * pont_temporario;

  /*ponteiros para identificação de onde se encontram os arquivos da tabela solicitada*/
  char * dados;
  char * tamanho;

  char * nomeTabela = malloc(21*sizeof(char));                                  //reserva memória para identificação da tabela localizada no arquivo
  if(nomeTabela == NULL){
		printf("ERRO! Memória não alocada.");
		exit(0);
	}

  char respSN;                                                                  //variável para respostas Sim ou Não do usuário

  /*Variáveis auxiliades para leitura de arquivos*/
  int linha_escolhida = 0;
  int ordem;
  int linha_atual = 1;

  printf("---APAGAR TABELAS---\n\n");

  /*Lista das tabelas cadastradas*/
  do{
    pont_tabelas = fopen("tabelas//listaTabelas.txt", "r");
    if (pont_tabelas == NULL){
      printf("ERRO! O arquivo de nomes não foi aberto.\n");
      exit(0);
    }else{
      if(fgets(nomeTabela, 20, pont_tabelas) == NULL){                          //Não havendo nada na primeira linha do arquivo, significa dizer que não há tabelas cadastradas
        printf("Não há tabelas cadastradas!\n");
        printf("Deseja cadastrar uma tabela(s/n)? ");
        fflush(stdin);
        scanf(" %c", &respSN);
        if (respSN == 's') {
          fclose(pont_tabelas);
          free(nomeTabela);
          nomeTabela = NULL;
          criarTabela();
          return -1;
        }else{
          fclose(pont_tabelas);
          free(nomeTabela);
          nomeTabela = NULL;
          return -1;
        }
      }else{                                                                    //Havendo linhas, são listados os nomes das tabelas com um indice ao lado
        ordem = 0;
        do {
          printf("%d. %s", ++ordem, nomeTabela);
        } while(fgets(nomeTabela, 20, pont_tabelas) != NULL);
        fflush(stdin);
        printf("\nQual tabela deseja apagar? ");
        scanf("%d", &linha_escolhida);
        if (linha_escolhida < 1 || linha_escolhida > ordem) {                   //Controle de que o indice solicitado seja um dos exibidos na tela
          cabecalho();
          printf("---APAGAR TABELAS---\n\n");
          printf("*Opção Inválida!\n");
          fclose(pont_tabelas);
        }else{
          fclose(pont_tabelas);
        }
      }
    }
  } while (linha_escolhida < 1 || linha_escolhida > ordem);

  /*Localização dos arquivos da tabela solicidata e do nome da tabela no arquivo listaTabelas*/
  pont_temporario = fopen("tabelas//temporario.txt", "w");
  pont_tabelas = fopen("tabelas//listaTabelas.txt", "r");
  if (pont_tabelas == NULL || pont_temporario == NULL){
		printf("ERRO! O arquivo de nomes não foi aberto.\n");
    exit(0);
	}else{
    while(fgets(nomeTabela, 20, pont_tabelas) != NULL){
      if (linha_atual == linha_escolhida) {
        nomeTabela[strcspn(nomeTabela, "\n")] = 0;                              //retira o '\n'
        dados = diretorioDados(nomeTabela);
        tamanho = diretorioTamanhos(nomeTabela);
        linha_atual++;
        continue;
      }
      linha_atual++;
      fputs(nomeTabela, pont_temporario);
    }
  }
  fclose(pont_tabelas);
  fclose(pont_temporario);

  remove(tamanho);
  remove(dados);
  free(dados);
  free(tamanho);
  free(nomeTabela);
  nomeTabela = NULL;

  remove("tabelas//listaTabelas.txt");
  rename("tabelas//temporario.txt", "tabelas//listaTabelas.txt");

  printf("\n*A tabela foi excluída do banco!*\n");
 fflush(stdin);
  printf("Deseja continuar apagando tabelas(s/n)? ");
  scanf(" %c", &respSN);
  if (respSN == 's') {
    apagarTabela();
  }
  return 0;
};
