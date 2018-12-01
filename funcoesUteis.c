/*--Função para exibição padrão no início das 'telas'--*/
void cabecalho(){
	system("clear");
	printf("--------------------\n");
	printf("      SGBD ITP\n");
	printf("Autor: Jordevá Lucas\n");
	printf("--------------------\n\n");
}

/*--Função responsável por fornecer o diretório
		dos dados de uma tabela, seja na criação de
		uma nova tabela, seja na inclusão de dados,
		entre outros--*/
char* diretorioDados(char * nomeTabela){
  char * nome_dados_tabela = (char *)calloc(1, strlen(nomeTabela)+17);
  strncat(nome_dados_tabela, "dados//", 7);
  strncat(nome_dados_tabela, nomeTabela, strlen(nomeTabela));
  strncat(nome_dados_tabela, "_dados.txt", 10);
  return nome_dados_tabela;
}

/*--Função responsável por fornecer o diretório
		dos tamanhos dos atributos de uma tabela,
		seja na criação de uma nova tabela, seja na
		inclusão de dados, entre outros--*/
char* diretorioTamanhos(char * nomeTabela){
	char * nome_tamanho_tabela = (char *)calloc(1, strlen(nomeTabela)+22);
  strncat(nome_tamanho_tabela, "tamanhos//", 10);
  strncat(nome_tamanho_tabela, nomeTabela, strlen(nomeTabela));
  strncat(nome_tamanho_tabela, "_tamanho.txt", 12);
  return nome_tamanho_tabela;
}
