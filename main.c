#include "biblioteca.h"
#include <stdio.h>
#include <stdlib.h>

int lidos = 0; // Define lidos here
Registro registros[TAMANHO_X]; // Define registros here
cabecalho header[1]; // Define header here

int main() {
  int opcao;
  FILE *arquivo = fopen("Amostra.csv", "r");

  if (arquivo == NULL) {
    printf("Erro ao abrir o arquivo.\n");
    perror("Detalhes do erro: ");
    return 1;
  }

  ler_cabecalho(arquivo);
  // Move lerCSV() call inside the menu loop
  do {
    printf("\n\nEscolha uma das opções:\n");
    printf("1- Mostrar todos os registros (mostrar_todos_registros)\n");
    printf("2- Ordenar registros por data (decrescente_data_ajuizamento)\n");
    printf("3- Contar classes únicas (idAssuntoUnico)\n");
    printf("4- Contar quantidade de cada classe (contarIdClasse)\n");
    printf("5- Sair\n");
    scanf("%d", &opcao);

    if (opcao <= 0 || opcao >= 5) {
      printf("Número digitado inválido.\nTente novamente.\n");
      continue;
    }
    lerCSV(arquivo); // Read CSV file here
    switch (opcao) {
      case 1:
        mostrar_todos_registros();
        break;

      case 2:
        decrescente_data_ajuizamento();
        break;

      case 3:
      //idAssuntoUnico(char id_assunto[][50], int cont, const char *new_id);
        break;

      case 4:
        contarIdClasse(lidos);
        break;

      case 5:
        printf("Até logo ;)\n\n");
        sleep(1);
        exit(1);
        fclose(arquivo);
        return 0;
      case 6:
        break; // Exit the switch statement
    }
  } while (opcao != 4);

  fclose(arquivo);

  return 0;
}