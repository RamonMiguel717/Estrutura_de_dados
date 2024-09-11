#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
Defini o tamanho padrão por metodo de plano cartesiano, então Tamanho X é a leitura horizontal(caracteres) e Y é a leitura vertical(linhas)

Exemplo:
X:12
Y:10

Resposta: Linha 10 caractere 12
*/
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


/*
Então, eu tomei a liberdade de criar a função de OrganizadorData pois o arquivo original está no modelo US,
o que futuramente geraria alguns problemas na filtragem dos dados, com essa função é possivel organizar os
dados seguindo o modelo AA/MM/DD HH:MM:SS:MS (sendo MS milissegundos)

Além disso, esta função faz a conversão da data string pra int
*/
DataAjuizamento OrganizadorData(const char *dataStr) {
    DataAjuizamento data;

    sscanf(dataStr, "%d-%d-%d %d:%d:%d.%d",&data.ano, &data.mes, &data.dia,&data.hora, &data.minuto, &data.segundo, &data.milissegundos);
    return data;
}

void lerCSV(const char *Arquivo) {
    FILE *arquivo = fopen(Arquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        perror("Detalhes do erro: ");
        return;
    }

    char linha[TAMANHO_X];
    int indice = 0;

  //Esta parte do programa basicamente organiza os dados na struct Registro
    while (fgets(linha, sizeof(linha), arquivo)) {
        Registro registro;

/*
Utilizei duas funções incomuns nesta parte do codigo, que são as funções:

strtok: Basicamente funciona como um Slicing (uma faca) onde você passa dois parametros, o primeiro é o texto (ou variavel) 
que será feita a leitura. O segundo é o identificador do slice.

    Com o uso dessa função fica mais simples de fazer a divisão dos ID´s. Ele evita o problema de outros metodos que são:

        É comum que o programa começe a ler do inicio da linha, o que me faria ter que adicionar uma lógica complementar 
        para que ele pule os id´s lidos anteriormente.

strcpy: Esta função é um tanto mais abrangente, basicamente ela faz uma comparação de dois parametros.
    Como não é possivel passar um parametro dentro de outro, eu criei a variavel "Token", para incluir a função como um
    parametro legivel para a função.
*/
        registro.indice = indice++;

        char *token = strtok(linha, ",");
        if (token != NULL) strcpy(registro.id, token);

        token = strtok(NULL, ",");
        if (token != NULL) strcpy(registro.numero, token);

        token = strtok(NULL, ",");
        if (token != NULL) registro.data_ajuizamento = OrganizadorData(token); 

        token = strtok(NULL, ",");
        if (token != NULL) strcpy(registro.id_classe, token);

        token = strtok(NULL, ",");
        if (token != NULL) strcpy(registro.id_assunto, token);

        token = strtok(NULL, ",");
        if (token != NULL) strcpy(registro.ano_eleicao, token);
    }

    fclose(arquivo);
}
//Vai ser necessario corrigir a passagem do repositório, pois para cada computador tem um caminho diferente, e eu não estou conseguindo
// fazer o programa funcionar se não for pela passagem do caminho absoluto.
int main() {
const char *Arquivo = "C:\\Users\\SAMSUNG\\Desktop\\Estudo\\Faculdade\\Segundo Semestre\\Estrutura de dados\\Atividade em grupo\\Amostra.csv";

    lerCSV(Arquivo);
    return 0;
}