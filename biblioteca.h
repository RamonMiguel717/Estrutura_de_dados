#ifndef BIBLIOTECA_H
#define BIBLIOTECA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h> // for boolean data type

// Declarações
#define TAM 500
#define TAMANHO_X 1024
#define TAMANHO_Y 100
#define MAX_ID_ASSUNTOS 100 // Capacidade máxima para armazenar id_assuntos

// --- Data Structure for Date ---
typedef struct {
    int ano;
    int mes;
    int dia;
    int hora;
    int minuto;
    int segundo;
    int milissegundos;
} DataJuizamento;

typedef struct {
    int indice;
    char id[50];
    double numero;
    DataJuizamento data_ajuizamento;
    char id_classe[50];
    char id_assunto[50];
    char ano_eleicao[10];
} Registro;

typedef struct {   // struct criada apenas para ler o cabeçalho
    char id[TAMANHO_Y];
    char numero[TAMANHO_Y];
    char data_ajuizamento[TAMANHO_Y];
    char id_classe[TAMANHO_Y];
    char id_assunto[TAMANHO_Y];
    char ano_eleicao[TAMANHO_Y];
} cabecalho;

typedef struct { // struct criada apenas para contagem de classes 
    char id_classe[50];
    int quantidade;
} ClasseContagem;

// Declare variables as extern
extern int lidos;
extern Registro registros[TAMANHO_X];
extern cabecalho header[1];

// Portótipos de funções
DataJuizamento organizarData(const char *dataStr);
void ler_cabecalho(FILE *arquivo);
void lerCSV(FILE *arquivo);
void ordenacao_crescente_Id();
void decrescente_data_ajuizamento();
int contarOcorrenciasIdClasse(int lidos);
int idAssuntoUnico(char (*id_assunto)[50], int count, const char *new_id);
void mostrar_um_registro();
void mostrar_todos_registros();

// Funções de limpeza e manuntenção
void remove_newline(char *str);
void remove_aspas(char *str);
void clean_buffer();

#endif
