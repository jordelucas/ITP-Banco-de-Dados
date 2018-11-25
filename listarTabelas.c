void listarTabelas(){
  FILE * pont_tabelas;
  char * texto_str = malloc(20*sizeof(char));
  char resp;
	printf("---LISTAR TABELAS---\n\n");

  pont_tabelas = fopen("tabelas//listaTabelas.txt", "r");
  if (pont_tabelas == NULL){
		printf("ERRO! O arquivo de nomes não foi aberto!\n");
	}else{
    if(fgets(texto_str, 20, pont_tabelas) == NULL){
      printf("Não há tabelas cadastradas!\n");
      printf("Deseja cadastrar uma tabela(s/n)?");
      scanf(" %c", &resp);
      if (resp == 's') {
        cabecalho();
        criarTabela();
        cabecalho();
      }
    }else{
      do{
        printf("-> %s", texto_str);
      }while (fgets(texto_str, 20, pont_tabelas) != NULL);
      printf("\nDeseja editar uma tabela(s/n)?");
      scanf(" %c", &resp);
      if (resp == 's') {
        printf("OK\n");
      }else{
        printf("Blz\n");
      }
    }
	}
	fclose(pont_tabelas);
}
