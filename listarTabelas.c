#include <stdio.h>

void listarTabelas(){
  FILE * pont_tabelas;
  char texto_str[15];
  char resp;
	printf("---LISTAR TABELAS---\n\n");

  pont_tabelas = fopen("tabelas//listaTabelas.txt", "r");

  while(fgets(texto_str, 15, pont_tabelas) != NULL){
    printf("-> %s", texto_str);
  }

  printf("\nDeseja editar uma tabela(s/n)?");
  scanf(" %c", &resp);
  if (resp == 's') {
    printf("OK\n");
  }else{
    printf("Blz\n");
  }

  fclose(pont_tabelas);
}
