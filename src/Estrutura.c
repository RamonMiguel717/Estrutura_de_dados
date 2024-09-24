#include <stdio.h>
#include "biblioteca.h"
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
void processar_chaves(char **token); //tratar atributos que comtem "{}"
void processar_chaves(char **token) {
    if (*token != NULL && (*token)[0] == '{') {
        char *inicio = *token;
        while (strchr(inicio, '}') == NULL) {
            char *proximo = strtok(NULL, ",");
            if (proximo != NULL) {
                strcat(inicio, ",");
                strcat(inicio, proximo);
            }
        }
    }
}


//funções

  
datajuizamento OrganizadorData(const char *dataStr) //ok
{
    datajuizamento data;

    sscanf(dataStr, "%d-%d-%d %d:%d:%d.%d",&data.ano, &data.mes, &data.dia,&data.hora, &data.minuto, &data.segundo, &data.milissegundos);
    return data;
}

void ler_cabecalho(FILE *arquivo) //ok
{
    char linha[TAM];

    printf("\n*Abertura bem sucedida!!\n");
    printf("lendo cabeçalho...");
    sleep(1);

    if(fgets(linha, sizeof(linha), arquivo))
    {
        remove_newline(linha);
        remove_aspas(linha);

        char *token = strtok(linha, ",");
        int contagem = 0;

        while(token != NULL && contagem < 6)
        {
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

        //printf("\n\nCabeçalho lido:\n"); //confirmação de leitura do cabeçalho
        //for(int i=0;i<1;i++)
        //{
           // printf("id: %s\nnumero: %s\nData-ajuizamento: %s\nId-classe: %s\nId-assunto: %s\nAno eleição: %s\n\n", header[i].id, header[i].numero, header[i].data_ajuizamento, header[i].id_classe, header[i].id_assunto, header[i].ano_eleicao);
        //}
    }
}

void lerCSV(FILE *arquivo) //ok
{
    char linha[TAM];
    int indice = 0;

    printf("Lendo arquivo...\n"); //confirmação de leitura
    sleep(1);

    while (fgets(linha, sizeof(linha), arquivo)) {
        Registro registro;
        remove_newline(linha);
        remove_aspas(linha);

        char *token = strtok(linha, ",");
        if (token != NULL) strcpy(registro.id, token);

        token = strtok(NULL, ",");
        if (token != NULL) {
            registro.numero = strtod(token, NULL); // Convertendo o token para double e armazenando no campo numero
        }

        token = strtok(NULL, ",");
        if (token != NULL) registro.data_ajuizamento = OrganizadorData(token);

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

    // confirmação de armazenamento dos registros
    printf("Quantidade de arquivos lidos: \n%d\n\n", lidos);
}


void ordenacao_crescente_Id() //ok
{
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

void decrescente_data_ajuizamento() //ok
{
    Registro temp;
    int opcao;

    for (int i = 0; i < TAMANHO_X - 1; i++) 
    {
        for (int j = 0; j < TAMANHO_X - 1 - i; j++) 
        {

            // Comparar anos
            if (registros[j].data_ajuizamento.ano < registros[j+1].data_ajuizamento.ano) 
            {
                temp = registros[j];
                registros[j] = registros[j + 1];
                registros[j + 1] = temp;
            }

            // Se os anos forem iguais, comparar meses
            else if (registros[j].data_ajuizamento.ano == registros[j+1].data_ajuizamento.ano) 
            {
                if (registros[j].data_ajuizamento.mes < registros[j+1].data_ajuizamento.mes) 
                {
                    temp = registros[j];
                    registros[j] = registros[j + 1];
                    registros[j + 1] = temp;
                }
                // Se os meses forem iguais, comparar dias
                else if (registros[j].data_ajuizamento.mes == registros[j+1].data_ajuizamento.mes) 
                {
                    if (registros[j].data_ajuizamento.dia < registros[j+1].data_ajuizamento.dia) 
                    {
                        temp = registros[j];
                        registros[j] = registros[j + 1];
                        registros[j + 1] = temp;
                    }
                    // Se os dias forem iguais, comparar horas
                    else if (registros[j].data_ajuizamento.dia == registros[j+1].data_ajuizamento.dia) 
                    {
                        if (registros[j].data_ajuizamento.hora < registros[j+1].data_ajuizamento.hora) 
                        {
                            temp = registros[j];
                            registros[j] = registros[j + 1];
                            registros[j + 1] = temp;
                        }
                        // Se as horas forem iguais, comparar minutos
                        else if (registros[j].data_ajuizamento.hora == registros[j+1].data_ajuizamento.hora) 
                        {
                            if (registros[j].data_ajuizamento.minuto < registros[j+1].data_ajuizamento.minuto) 
                            {
                                temp = registros[j];
                                registros[j] = registros[j + 1];
                                registros[j + 1] = temp;
                            }
                            // Se os minutos forem iguais, comparar segundos
                            else if (registros[j].data_ajuizamento.minuto == registros[j+1].data_ajuizamento.minuto) 
                            {
                                if (registros[j].data_ajuizamento.segundo < registros[j+1].data_ajuizamento.segundo) 
                                {
                                    temp = registros[j];
                                    registros[j] = registros[j + 1];
                                    registros[j + 1] = temp;
                                }
                                // Se os segundos forem iguais, comparar milissegundos
                                else if (registros[j].data_ajuizamento.segundo == registros[j+1].data_ajuizamento.segundo) 
                                {
                                    if (registros[j].data_ajuizamento.milissegundos < registros[j+1].data_ajuizamento.milissegundos) 
                                    {
                                        temp = registros[j];
                                        registros[j] = registros[j + 1];
                                        registros[j + 1] = temp;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        //printf("Processo ordenado! Número: %d\nId: %s\nNúmero: %lf\n Data ajuizamento: %d-%02d-%02d %02d:%02d:%02d.%03d\nId-classe: %s\nId-assunto: %s\nAno-eleição: %s\n\n", i+1, registros[i].id, registros[i].numero, registros[i].data_ajuizamento.ano,
                    //registros[i].data_ajuizamento.mes,
                    //registros[i].data_ajuizamento.dia,
                    //registros[i].data_ajuizamento.hora,
                    //registros[i].data_ajuizamento.minuto,
                    //registros[i].data_ajuizamento.segundo,
                    //registros[i].data_ajuizamento.milissegundos, registros[i].id_classe, registros[i].id_assunto, registros[i].ano_eleicao);
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

void mostrar_todos_registros() //ok
{
    char resp[10];

    printf("Deseja ver a ordenação de todos os registros?\n");
    clean_buffer();
    fgets(resp, sizeof(resp), stdin);
    remove_newline(resp);

    if(strcmp(resp, "sim") == 0 || strcmp(resp, "Sim") == 0)
    {
            if(lidos > 0)
            {
                for(int i=0;i < TAMANHO_X ;i++)
                {
                    printf("Processo número: %d\nId: %s\nNúmero: %lf\n Data ajuizamento: %d-%02d-%02d %02d:%02d:%02d.%03d\nId-classe: %s\nId-assunto: %s\nAno-eleição: %s\n\n", i+1, registros[i].id, registros[i].numero, registros[i].data_ajuizamento.ano,
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

void mostrar_um_registro() //ok
{
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

int idAssuntoUnico(char id_assunto[][50], int count, const char *new_id) {
    for (int i = 0; i < count; i++) {
        if (strcmp(id_assunto[i], new_id) == 0) {
            return 0; // ID já existe
        }
    }
    return 1; // Novo ID
}

void contarIdClasse( int lidos){ //ok
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
}