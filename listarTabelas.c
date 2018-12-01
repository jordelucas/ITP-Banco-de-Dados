int listarTabelas(){
  cabecalho();
  /*--Ponteiro para o tipo arquivo--*/
  FILE * pont_tabelas;

  char * texto_str = (char*) malloc(21*sizeof(char));               //Reserva memória para identificação dos nomes de tabelas contidos no arquivo
  if(texto_str == NULL){
    printf("ERRO! Memória não alocada.");
    exit(0);
  }

  char respSN;                                                      //Variável para respostas Sim ou Não do usuário

  printf("---LISTAR TABELAS---\n\n");

  /*--Lista das tabelas cadastradas--*/
  pont_tabelas = fopen("tabelas//listaTabelas.txt", "r");
  if (pont_tabelas == NULL){
    printf("ERRO! O arquivo de nomes não foi aberto!\n");
    exit(0);
  }else{
    if(fgets(texto_str, 21, pont_tabelas) == NULL){                 //Não havendo nada na primeira linha do arquivo, significa dizer que não há tabelas cadastradas
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
    }else{                                                          //Havendo linhas, são listados os nomes das tabelas
      do{
        printf("-> %s", texto_str);
      }while (fgets(texto_str, 21, pont_tabelas) != NULL);
      fflush(stdin);
      printf("\nDeseja retornar ao menu(s/n)?");
      scanf(" %c", &respSN);
      if (respSN == 's') {
        fclose(pont_tabelas);
        free(texto_str);
        texto_str = NULL;
        return -1;
      }else{
        fclose(pont_tabelas);
        free(texto_str);
        texto_str = NULL;
        listarTabelas();
        return -1;
      }
    }
  }
  return 0;
}
