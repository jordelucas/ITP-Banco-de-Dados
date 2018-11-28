int listarTabelas(){
  cabecalho();
  FILE * pont_tabelas;

  char * texto_str = (char*) malloc(21*sizeof(char));                //reserva memória para identificação da tabela localizada no arquivo
  if(texto_str == NULL){
		printf("ERRO! Memória não alocada.");
		exit(0);
	}

  char respSN;                                                //variável para respostas Sim ou Não do usuário

	printf("---LISTAR TABELAS---\n\n");

  pont_tabelas = fopen("tabelas//listaTabelas.txt", "r");
  if (pont_tabelas == NULL){
		printf("ERRO! O arquivo de nomes não foi aberto!\n");
    exit(0);
	}else{
    if(fgets(texto_str, 21, pont_tabelas) == NULL){           //Não havendo nada na primeira linha do arquivo, significa dizer que não há tabelas cadastradas
      printf("Não há tabelas cadastradas!\n");
      fflush(stdin);
      printf("Deseja cadastrar uma tabela(s/n)? ");
      scanf(" %c", &respSN);
      if (respSN == 's') {
        fclose(pont_tabelas);
        free(texto_str);
        criarTabela();
        return -1;
      }else{
        fclose(pont_tabelas);
        free(texto_str);
        texto_str = NULL;
        return -1;
      }
    }else{                                                    //Havendo linhas, são listados os nomes das tabelas
      do{
        printf("-> %s", texto_str);
      }while (fgets(texto_str, 21, pont_tabelas) != NULL);
      fflush(stdin);
      printf("\nDeseja editar uma tabela(s/n)?");
      scanf(" %c", &respSN);
      if (respSN == 's') {
        printf("OK\n");
      }else{
        printf("Blz\n");
      }
    }
	}
  fclose(pont_tabelas);
  free(texto_str);
  texto_str = NULL;
  return 0;
}
