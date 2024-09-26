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
    //lerCSV(arquivo); // Move lerCSV() call inside the menu loop

    do {
        printf("\n\nEscolha uma das opções:\n");
        printf("1- Mostrar todos os registros (mostrar_todos_registros)\n");
        printf("2- Ordenar registros por data (decrescente_data_ajuizamento)\n");
        printf("3- Mostrar quantidade de cada classe (contarOcorrenciasIdClasse)\n");
        printf("4- Contar classes únicas (idAssustosUnicos)\n");
        printf("5- Sair\n");
        scanf("%d", &opcao);

        if (opcao <= 0 || opcao >= 6) {
            printf("Número digitado inválido.\nTente novamente.\n");
            continue;
        }

        switch (opcao) {
            case 1:
                mostrar_todos_registros();
                break;

            case 2:
                decrescente_data_ajuizamento();
                break;

            case 3:
                contarOcorrenciasIdClasse(lidos);
                break;

            case 4: 
                // Assuming idAssuntoUnico takes an array, count, and new ID
                idAssuntoUnico(registros[TAMANHO_X].id_assunto, 0,); 
                break;

            case 5:
                printf("Até logo ;)\n\n");
                sleep(1);
                exit(1);
                fclose(arquivo);
                return 0;
        }
      lerCSV(arquivo);
    } while (opcao != 5);

    fclose(arquivo);

    return 0;
}
