#include "biblioteca.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h> // for boolean data type

// --- Function to Format Date ---
char* formatarData(DataJuizamento data) {
    // Allocate memory for formatted date string
    char* dataFormatada = malloc(sizeof(char) * 25); 

    if (dataFormatada != NULL) {
        sprintf(dataFormatada, "%04d-%02d-%02d %02d:%02d:%02d.%03d", 
                data.ano, data.mes, data.dia, 
                data.hora, data.minuto, data.segundo, data.milissegundos);
    } else {
        perror("Erro ao alocar memória para data formatada");
        exit(EXIT_FAILURE); // Terminate the program if memory allocation fails
    }

    return dataFormatada;
}

// --- Function to Compare Dates ---
int compararDatas(DataJuizamento data1, DataJuizamento data2) {
    // Compare years
    if (data1.ano < data2.ano) {
        return -1;
    } else if (data1.ano > data2.ano) {
        return 1;
    }

    // Years are equal, compare months
    if (data1.mes < data2.mes) {
        return -1;
    } else if (data1.mes > data2.mes) {
        return 1;
    }

    // Months are equal, compare days
    if (data1.dia < data2.dia) {
        return -1;
    } else if (data1.dia > data2.dia) {
        return 1;
    }

    // Days are equal, compare hours
    // ... continue comparing other fields (hours, minutes, seconds, milliseconds)

    // Dates are equal
    return 0;
}

// --- Function to Parse a Date String ---
DataJuizamento organizarData(const char *dataStr) {
    DataJuizamento data;
    sscanf(dataStr, "%d-%d-%d %d:%d:%d.%d", 
           &data.ano, &data.mes, &data.dia, 
           &data.hora, &data.minuto, &data.segundo, &data.milissegundos);
    return data;
}

// --- Function to Compare Records (for sorting) ---
int compararRegistros(Registro registro1, Registro registro2) {
    return compararDatas(registro1.data_ajuizamento, registro2.data_ajuizamento);
}

// --- Function to Sort Records by DataJuizamento (using Quicksort) ---
void quicksortRegistros(Registro registros[], int inicio, int fim) {
    if (inicio < fim) {
        int pivo = inicio;
        int i = inicio + 1;
        int j = fim;

        while (i <= j) {
            while (i <= fim && compararRegistros(registros[i], registros[pivo]) <= 0) {
                i++;
            }

            while (j >= inicio && compararRegistros(registros[j], registros[pivo]) > 0) {
                j--;
            }

            if (i < j) {
                Registro temp = registros[i];
                registros[i] = registros[j];
                registros[j] = temp;
            }
        }

        Registro temp = registros[pivo];
        registros[pivo] = registros[j];
        registros[j] = temp;

        quicksortRegistros(registros, inicio, j - 1);
        quicksortRegistros(registros, j + 1, fim);
    }
}

void decrescente_data_ajuizamento() {
    int opcao;
    quicksortRegistros(registros, 0, lidos - 1); // Assuming `lidos` is the number of valid records

    printf("Registros ordenados por data:\n");
    mostrar_todos_registros(); // You can re-use mostrar_todos_registros to print the sorted data

    printf("\n1-Mostra todos os registros ordenados\n2- Mostrar um registro específico\n3- Voltar\n\n");
    scanf("%d", &opcao);

    switch (opcao) {
        case 1:
            mostrar_todos_registros();
            break;

        case 2:
            mostrar_um_registro();
            break;

        case 3:
            return;
    }
}

int contarOcorrenciasIdClasse(int lidos) {
    ClasseContagem contagens[TAMANHO_Y];
        int totalClasses = 0;

        for (int i = 0; i < lidos; i++) {
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
            printf("Número de processos vinculados ao id_classe '%s': %d\n", contagens[i].id_classe, contagens[i].quantidade);
        }
        return totalClasses;}    

void ler_cabecalho(FILE *arquivo) {
    char linha[TAM];

    printf("\n*Abertura bem sucedida!!\n");
    printf("lendo cabeçalho...");
    sleep(1);

    if (fgets(linha, sizeof(linha), arquivo)) {
        remove_newline(linha);
        remove_aspas(linha);

        char *token = strtok(linha, ",");
        int contagem = 0;

        while (token != NULL && contagem < 6) {
            // Remove aspas do início e do final do token, se presentes
            if (token[0] == '"') token++;
            if (token[strlen(token) - 1] == '"') token[strlen(token) - 1] = '\0';

            // Atribuir o token ao campo apropriado da struct
            switch (contagem) {
                case 0: strcpy(header->id, token); break;
                case 1: strcpy(header->numero, token); break;
                case 2: strcpy(header->data_ajuizamento, token); break;
                case 3: strcpy(header->id_classe, token); break;
                case 4: strcpy(header->id_assunto, token); break;
                case 5: strcpy(header->ano_eleicao, token); break;
                default: break;
            }

            token = strtok(NULL, ",");
            contagem++;
        }

    }
}

void lerCSV(FILE *arquivo) {
    char linha[TAM];
    int indice = 0;

    printf("Lendo arquivo...\n"); 
    sleep(1);

    while (fgets(linha, sizeof(linha), arquivo)) {
        Registro registro;
        remove_newline(linha);
        remove_aspas(linha);

        char *token = strtok(linha, ",");
        if (token != NULL) strcpy(registro.id, token);

        token = strtok(NULL, ",");
        if (token != NULL) {
            registro.numero = strtod(token, NULL);
        }

        token = strtok(NULL, ",");
        if (token != NULL) registro.data_ajuizamento = organizarData(token);

        token = strtok(NULL, ",");
        if (token != NULL) strcpy(registro.id_classe, token);

        token = strtok(NULL, ",");
        if (token != NULL) strcpy(registro.id_assunto, token);

        token = strtok(NULL, ",");
        if (token != NULL) strcpy(registro.ano_eleicao, token);

        registro.indice = indice;
        registros[indice++] = registro;

        lidos++;

        printf("Id_classe lido: %s\n", registro.id_classe);
    }

    printf("\n*Arquivo 'amostra.csv' armazenado com sucesso!!\n\n");

    printf("Quantidade de arquivos lidos: \n%d\n\n", lidos);
}

void ordenacao_crescente_Id() {
    Registro temp;
    int opcao;

    for (int i=0;i< TAMANHO_X -1; i++)
    {
        for(int j =0; j < TAMANHO_X -1 - i;j++)
        {
            if(strcmp(registros[j].id, registros[j+1].id) > 0)
            {
                temp = registros[j];
                registros[j] = registros[j +1];
                registros[j + 1] = temp;
            }
            //printf("Processo ordenado! Número: %d\nId: %s\nNúmero: %lf\n Data ajuizamento: %d-%02d-%02d %02d:%02d:%02d.%03d\nId-classe: %s\nId-assunto: %s\nAno-eleição: %s\n\n", i+1, registros[i].id, registros[i].numero, registros[i].data_ajuizamento.ano,
                    //registros[i].data_ajuizamento.mes,
                    //registros[i].data_ajuizamento.dia,
                    //registros[i].data_ajuizamento.hora,
                    //registros[i].data_ajuizamento.minuto,
                    //registros[i].data_ajuizamento.segundo,
                    //registros[i].data_ajuizamento.milissegundos, registros[i].id_classe, registros[i].id_assunto, registros[i].ano_eleicao);
        }
    }  
    printf("Ordenação bem sucedida!\n");

    printf("\n1-Mostra todos os registros ordenados\n2- Mostrar um registro específico\n3- Voltar\n\n");
    scanf("%d", &opcao);

    switch(opcao)
    {
        case 1:
        mostrar_todos_registros();
        break;

        case 2:
        mostrar_um_registro();
        break;

        case 3:
        return;
    }

}

void mostrar_todos_registros() {
    char resp[10];

    printf("Deseja ver a ordenação de todos os registros?\n");
    clean_buffer();
    fgets(resp, sizeof(resp), stdin);
    remove_newline(resp);

    if (strcmp(resp, "sim") == 0 || strcmp(resp, "Sim") == 0) {
        if (lidos > 0) {
            for (int i = 0; i < TAMANHO_X; i++) {
                printf("Processo número: %d\nId: %s\nNúmero: %lf\n Data ajuizamento: %d-%02d-%02d %02d:%02d:%02d.%03d\nId-classe: %s\nId-assunto: %s\nAno-eleição: %s\n\n", i + 1, registros[i].id, registros[i].numero, registros[i].data_ajuizamento.ano,
                    registros[i].data_ajuizamento.mes,
                    registros[i].data_ajuizamento.dia,
                    registros[i].data_ajuizamento.hora,
                    registros[i].data_ajuizamento.minuto,
                    registros[i].data_ajuizamento.segundo,
                    registros[i].data_ajuizamento.milissegundos, registros[i].id_classe, registros[i].id_assunto, registros[i].ano_eleicao);
            }   
            printf("Voltando ao menu...");
                sleep(1);
                return;   
        }
        else
        {
            printf("Ainda não existem processos.\n ");
            printf("Voltando ao menu...");
            sleep(1);
            return;
        } 
    }    
    else
    {
        printf("Voltando ao menu...");
        sleep(1);
        return;
    }
}

void mostrar_um_registro() {
    char id_processo[TAMANHO_Y], resp[10];

    printf("Deseja ver a ordenação de um único registro do arquivo?\n");
    clean_buffer();
    fgets(resp, sizeof(resp), stdin);
    remove_newline(resp);

    if(strcmp(resp, "sim") == 0 || strcmp(resp, "Sim") == 0)
    {
        int encontrado = 0;

        printf("Digite o Id do processo que deseja verificar: \n");
        fgets(id_processo, sizeof(id_processo), stdin);
        remove_newline(id_processo);

        for(int i=0;i<TAMANHO_X;i++)
        {
            if(strcmp(id_processo, registros[i].id) == 0)
            {
                printf("\nProcesso número: %d\nId: %s\nNúmero: %lf\n Data ajuizamento: %d-%02d-%02d %02d:%02d:%02d.%03d\nId-classe: %s\nId-assunto: %s\nAno-eleição: %s\n\n", i+1, registros[i].id, registros[i].numero, registros[i].data_ajuizamento.ano,
                registros[i].data_ajuizamento.mes,
                registros[i].data_ajuizamento.dia,
                registros[i].data_ajuizamento.hora,
                registros[i].data_ajuizamento.minuto,
                registros[i].data_ajuizamento.segundo,
                registros[i].data_ajuizamento.milissegundos, registros[i].id_classe, registros[i].id_assunto, registros[i].ano_eleicao);

                encontrado = 1;
                printf("Voltando ao menu...");
                sleep(1);
                break; 
            } 
        }

    if(!encontrado)
    {
        printf("Nenhum processo foi encontrado com o número do id digitado...");
        printf("Voltando ao menu...");
        sleep(1);
         return;
    }   
    }
    else
    {
        printf("Voltando ao menu...");
        sleep(1);
        return; 
    }
}

int idAssuntoUnico(char (*id_assunto)[50], int count, const char *new_id) {
    int numeroDeProcessos;

    // Iterate through records
    for (int i = 0; i < numeroDeProcessos; i++) {
        int found = 0;
        for (int j = 0; j < count; j++) {
            if (strcmp(id_assunto[j], registros[i].id_assunto) == 0) {
                found = 1;
                break;
            }
        }
        if (!found) {
            strcpy(id_assunto[count], registros[i].id_assunto);
            count++;
        }
    }

    // Print the counts (you can modify this to get the counts for each class)
    for (int i = 0; i < count; i++) {
        printf("Id_assunto único: %s\n", id_assunto[i]);
    }

    return count; // Return the count of unique id_assunto
}

void remove_newline(char *str)
{
    int i=0;

    while(str[i] != '\0')
    {
        if(str[i] == '\n')
        {
            str[i] = '\0';
            break;
        }
        i++;
    }
}
void clean_buffer()
{
    int clean;

    while((clean = getchar()) != '\n' && clean != EOF);
}
void remove_aspas(char *str) 
{
    char *dest = str;
    char *src = str;

    while (*src) {
        if (*src != '"') {
            *dest++ = *src;
        }
        src++;
    }
    *dest = '\0';
}
