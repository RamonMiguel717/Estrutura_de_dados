#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define TAMANHO_X 1024
#define TAMANHO_Y 100

typedef struct {
  int ano;
  int mes;
  int dia;
  int hora;
  int minuto;
  int segundo;
  int milissegundos;
} DataAjuizamento;

typedef struct {
  int indice;
  char id[50];
  double numero[50];
  DataAjuizamento data_ajuizamento;
  char id_classe[50];
  char id_assunto[50];
  char ano_eleicao[10];
} Registro;

typedef struct {
  char id_classe[50];
  int quantidade;
} ClasseContagem;

DataAjuizamento OrganizadorData(const char *dataStr) {
  DataAjuizamento data;
  sscanf(dataStr, "%d-%d-%d %d:%d:%d.%d", &data.ano, &data.mes, &data.dia,
         &data.hora, &data.minuto, &data.segundo, &data.milissegundos);
  return data;
}

void lerCSV(const char *Arquivo, Registro registros[], int *totalRegistros) {
  FILE *arquivo = fopen(Arquivo, "r");
  if (arquivo == NULL) {
    printf("Erro ao abrir o arquivo.\n");
    perror("Detalhes do erro: ");
    return;
  }

  char linha[TAMANHO_X];
  int indice = 0;

  // Ignora a primeira linha (cabeçalho)
  fgets(linha, sizeof(linha), arquivo);

  while (fgets(linha, sizeof(linha), arquivo)) {
    if (registros != NULL) { // Se registros não é NULL, preenche os dados
      Registro registro;
      registro.indice = indice++;

      char *token = strtok(linha, ",");
      if (token != NULL) {
        // Limite o tamanho da cópia para evitar estouro de buffer
        strncpy(registro.id, token, sizeof(registro.id) - 1);
        registro.id[sizeof(registro.id) - 1] = '\0';
      }

      token = strtok(NULL, ",");
      if (token != NULL)
        registro.numero[0] = atof(token);

      token = strtok(NULL, ",");
      if (token != NULL)
        registro.data_ajuizamento = OrganizadorData(token);

      token = strtok(NULL, ",");
      if (token != NULL) {
        // Limite o tamanho da cópia para evitar estouro de buffer
        strncpy(registro.id_classe, token, sizeof(registro.id_classe) - 1);
        registro.id_classe[sizeof(registro.id_classe) - 1] = '\0';
      }

      token = strtok(NULL, ",");
      if (token != NULL) {
        // Limite o tamanho da cópia para evitar estouro de buffer
        strncpy(registro.id_assunto, token, sizeof(registro.id_assunto) - 1);
        registro.id_assunto[sizeof(registro.id_assunto) - 1] = '\0';
      }

      token = strtok(NULL, ",");
      if (token != NULL) {
        // Limite o tamanho da cópia para evitar estouro de buffer
        strncpy(registro.ano_eleicao, token, sizeof(registro.ano_eleicao) - 1);
        registro.ano_eleicao[sizeof(registro.ano_eleicao) - 1] = '\0';
      }

      registros[indice - 1] = registro;
    } else {
      // Se registros é NULL, apenas conta o número de linhas
      indice++;
    }
  }

  *totalRegistros = indice;
  fclose(arquivo);
}

void contarIdClasse(Registro registros[], int totalRegistros) {
  ClasseContagem contagens[TAMANHO_Y];
  int totalClasses = 0;

  for (int i = 0; i < totalRegistros; i++) {
    int encontrado = 0;
    for (int j = 0; j < totalClasses; j++) {
      if (strcmp(contagens[j].id_classe, registros[i].id_classe) == 0) {
        contagens[j].quantidade++;
        encontrado = 1;
        break;
      }
    }
    if (!encontrado) {
      strcpy(contagens[totalClasses].id_classe, registros[i].id_classe);
      contagens[totalClasses].quantidade = 1;
      totalClasses++;
    }
  }

  for (int i = 0; i < totalClasses; i++) {
    printf("Número de processos vinculados ao id_classe '%s': %d\n",
           contagens[i].id_classe, contagens[i].quantidade);
  }
}

int main() {
  setlocale(LC_ALL, "");
  char caminho_exec[1024];

  if (!getcwd(caminho_exec, sizeof(caminho_exec))) {
    perror("getcwd");
    return 1;
  }

  char *Arquivo = malloc(strlen(caminho_exec) + strlen("/Amostra.csv") + 1);
  sprintf(Arquivo, "%s/Amostra.csv", caminho_exec);

  // Lê o arquivo CSV uma vez para determinar o número de linhas
  int totalRegistros = 0;
  lerCSV(Arquivo, NULL, &totalRegistros);

  // Aloca memória dinamicamente para o array de registros
  Registro *registros = malloc(totalRegistros * sizeof(Registro));
  if (registros == NULL) {
    perror("Erro na alocação de memória");
    free(Arquivo); // Libera a memória alocada para Arquivo
    return 1;
  }

  // Lê o arquivo CSV novamente, agora com memória suficiente alocada
  lerCSV(Arquivo, registros, &totalRegistros);

  contarIdClasse(registros, totalRegistros);

  free(registros); // Libera a memória alocada para registros
  free(Arquivo); // Libera a memória alocada para Arquivo
  return 0;
}
