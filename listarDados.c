void listarDados(){
  FILE * pont_tabelas;
  FILE *pont_dados_tabela;
  FILE *pont_tamanho_tabela;
  int linha_atual = 1;
  char dados [35] = "";
  char tamanho [35] = "";
  char texto_str[15];
  int esc;
  int ordem = 0;
  int _inteiro = 0;
  int _double = 0;
  int _char = 0;
  int _string = 0;
  char nome[15];
  char valor[30];
  char *origem;
  char *destino;
  int espaco = 0;

  printf("----LISTAR DADOS----\n\n");

  do{
    pont_tabelas = fopen("tabelas//listaTabelas.txt", "r");
    while(fgets(texto_str, 15, pont_tabelas) != NULL){
      printf("%d. %s", ++ordem, texto_str);
    };
    printf("\nQual tabela deseja adicionar linha?");
    scanf("%d", &esc);
    if (esc < 1 || esc > ordem) {
      cabecalho();
      ordem = 0;
      printf("----LISTAR DADOS----\n\n");
      printf("*Opção Inválida!\n");
    }else{
      fclose(pont_tabelas);
    }
  } while (esc < 1 || esc > ordem);

  pont_tabelas = fopen("tabelas//listaTabelas.txt", "r");

  while(fgets(texto_str, 15, pont_tabelas) != NULL){
    if (linha_atual == esc) {

      texto_str[strcspn(texto_str, "\n")] = 0;

      strcat(dados, "dados/");
      strcat (dados, texto_str);
      strcat(dados, "_dados.txt");

      strcat(tamanho, "tamanhos//");
      strcat (tamanho, texto_str);
      strcat(tamanho, "_tamanho.txt");

      linha_atual++;
      continue;
    }
    linha_atual++;
  };
  fclose(pont_tabelas);

  pont_tamanho_tabela = fopen(tamanho, "r");
  Tamanho_Atributo atr;

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
  };

  typedef struct linha Nova_Linha;
  struct linha{
    int inteiros[_inteiro];
    char caracteres[_char];
    double doubles[_double];
    char strings[_string*30];
  };

  Nova_Linha nl;
  _inteiro = 0;
  _double = 0;
  _char = 0;
  _string = 0;

  pont_dados_tabela = fopen(dados, "r");

  cabecalho();
  printf("----LISTAR DADOS----\n\n");
  printf("Listando dados da tabela '%s'\n", texto_str);

  while (fread(&nl, sizeof(Nova_Linha), 1, pont_dados_tabela) == 1 ) {
    pont_tamanho_tabela = fopen(tamanho, "r");
    while (fread(&atr, sizeof(Tamanho_Atributo), 1, pont_tamanho_tabela) == 1 ) {
      switch(atr.tamanho){
    		case 1:
          printf("%s: ", atr.nome);
          printf("%c\n", nl.caracteres[_char]);
          _char++;
    			break;
    		case 4:
          printf("%s: ", atr.nome);
          printf("%d\n", nl.inteiros[_inteiro]);
          _inteiro++;
    			break;
    		case 8:
          printf("%s: ", atr.nome);
          printf("%lf\n", nl.doubles[_double]);
          _double++;
    			break;
    		case 30:
          printf("%s: ", atr.nome);
          printf("%s\n", nl.strings);
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
    printf("\n");
  }
  fclose(pont_dados_tabela);
}
