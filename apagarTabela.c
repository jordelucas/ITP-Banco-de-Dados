#include <stdio.h>
#include <stdlib.h>

void apagarTabela(){
  FILE * pont_tabelas;
  char texto_str[15];
  int resp;
  int ordem = 0;
  int n = 0;


  printf("---APAGAR TABELAS---\n\n");

  do{
    pont_tabelas = fopen("tabelas//listaTabelas.txt", "r");
    while(fgets(texto_str, 15, pont_tabelas) != NULL){
      printf("%d. %s", ++ordem, texto_str);
    };
    printf("\nQual tabela deseja apagar?");
    scanf("%d", &resp);
    if (resp < 1 || resp > ordem) {
      cabecalho();
      ordem = 0;
      printf("---APAGAR TABELAS---\n\n");
      printf("*Opção Inválida!\n");
    }else{
      fclose(pont_tabelas);
    }
  } while (resp < 1 || resp > ordem);


};
