#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void apagarTabela(){
  FILE * pont_tabelas;
  FILE * pont_temporario;
  char texto_str[15];
  char nome_tabela_escolhina[15] = "";
  int esc;
  int ordem = 0;
  int linha_atual = 1;
  char dados [35] = "";
  char tamanho [35] = "";

  printf("---APAGAR TABELAS---\n\n");

  do{
    pont_tabelas = fopen("tabelas//listaTabelas.txt", "r");
    while(fgets(texto_str, 15, pont_tabelas) != NULL){
      printf("%d. %s", ++ordem, texto_str);
    };
    printf("\nQual tabela deseja apagar?");
    scanf("%d", &esc);
    if (esc < 1 || esc > ordem) {
      cabecalho();
      ordem = 0;
      printf("---APAGAR TABELAS---\n\n");
      printf("*Opção Inválida!\n");
    }else{
      fclose(pont_tabelas);
    }
  } while (esc < 1 || esc > ordem);

  pont_tabelas = fopen("tabelas//listaTabelas.txt", "r");
  pont_temporario = fopen("tabelas//temporario.txt", "w");
  while(fgets(texto_str, 15, pont_tabelas) != NULL){
    if (linha_atual == esc) {
      strcat(dados, "dados/");
      //printf("%s\n", dados);
      strcat (dados, texto_str);
      //printf("%s\n", dados);
      dados[strcspn(dados, "\n")] = 0;
      //printf("%s\n", dados);
      strcat(dados, "_dados.txt");
      //printf("%s\n", dados);

      strcat(tamanho, "tamanhos//");
      strcat (tamanho, texto_str);
      tamanho[strcspn(tamanho, "\n")] = 0;
      strcat(tamanho, "_tamanho.txt");

      linha_atual++;
      continue;
    }
    linha_atual++;
    fputs(texto_str, pont_temporario);
  };
  fclose(pont_tabelas);
  fclose(pont_temporario);

  remove(dados);
  remove(tamanho);
  remove("tabelas//listaTabelas.txt");
  rename("tabelas//temporario.txt", "tabelas//listaTabelas.txt");
};
