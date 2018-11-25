int apagarTabela(){
  FILE * pont_tabelas;
  FILE * pont_temporario;

  char * dados;
  char * tamanho;

  char * nomeTabela = malloc(20*sizeof(char));
  char novaTabela;

  int linha_escolhida = 0;
  int ordem = 0;
  int linha_atual = 1;

  printf("---APAGAR TABELAS---\n\n");

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
        printf("\nQual tabela deseja apagar? ");
        scanf("%d", &linha_escolhida);
        if (linha_escolhida < 1 || linha_escolhida > ordem) {
          cabecalho();
          ordem = 0;
          printf("---APAGAR TABELAS---\n\n");
          printf("*Opção Inválida!\n");
          fclose(pont_tabelas);
        }else{
          fclose(pont_tabelas);
        }
      }
    }
  } while (linha_escolhida < 1 || linha_escolhida > ordem);

  pont_tabelas = fopen("tabelas//listaTabelas.txt", "r");
  pont_temporario = fopen("tabelas//temporario.txt", "w");
  if (pont_tabelas == NULL || pont_temporario == NULL){
		printf("ERRO! O arquivo de nomes não foi aberto!\n");
	}else{
    while(fgets(nomeTabela, 20, pont_tabelas) != NULL){
      if (linha_atual == linha_escolhida) {
        nomeTabela[strcspn(nomeTabela, "\n")] = 0; //retira o '\n'
        dados = diretorioDados(nomeTabela);
        tamanho = diretorioTamanhos(nomeTabela);
        linha_atual++;
        continue;
      }
      linha_atual++;
      fputs(nomeTabela, pont_temporario);
    }
  }
  free(nomeTabela);
  fclose(pont_tabelas);
  fclose(pont_temporario);

  remove(dados);
  remove(tamanho);
  remove("tabelas//listaTabelas.txt");
  rename("tabelas//temporario.txt", "tabelas//listaTabelas.txt");
  free(dados);
  free(tamanho);
};
