#include <stdio.h>
#include "biblioteca.h"

int main()
{
    int opcao;
    FILE *arquivo = fopen("../Amostra.csv", "r"); 

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        perror("Detalhes do erro: ");
        return 1;
    }

    ler_cabecalho(arquivo);
    lerCSV(arquivo);

    do
    {
        printf("\n\nEscolha uma das opções:\n1- Ordenação crescente de acordo com o atributo 'id'\n2- Ordenação decrescente de acordo com o atributo 'Data_ajuizamento'\n3- Contagem de assuntos únicos\n4- Contagem de registros por 'id_classe'\n5- Sair\n");
        scanf("%d", &opcao);

        if(opcao <= 0 || opcao >= 6)
        {
            printf("Numero digitado inválido.\nTente novamente.");
            sleep(1);
            break;
        }

        switch(opcao)
        {
            case 1:
            ordenacao_crescente_Id();
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
            break;
        }
    }while(opcao != 5);

    free(arquivo);
    fclose(arquivo);
    
    return 0;
}