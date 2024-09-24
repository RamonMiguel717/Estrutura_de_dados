#ifndef BIBLIOTECA_H
#define BIBLIOTECA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


//declarações
#define TAM 500
#define TAMANHO_X 1024
#define TAMANHO_Y 100
#define MAX_ID_ASSUNTOS 100 // Capacidade máxima para armazenar id_assuntos
int lidos = 0;

typedef struct {
    int ano;
    int mes;
    int dia;
    int hora;
    int minuto;
    int segundo;
    int milissegundos;
} datajuizamento;

typedef struct {
    int indice;
    char id[50];
    double numero;
    datajuizamento data_ajuizamento;
    char id_classe[50];
    char id_assunto[50];
    char ano_eleicao[10];
} Registro;
Registro registros[TAMANHO_X];

typedef struct{   // struct criada apenas para ler o cabeçalho
    char id[TAMANHO_Y];
    char numero[TAMANHO_Y];
    char data_ajuizamento[TAMANHO_Y];
    char id_classe[TAMANHO_Y];
    char id_assunto[TAMANHO_Y];
    char ano_eleicao[TAMANHO_Y];
}cabecalho;
cabecalho header[1];

typedef struct { // struct criada apenas para contagem de classes 
    char id_classe[50];
    int quantidade;
} ClasseContagem;

//portótipos de funções
datajuizamento OrganizadorData(const char *datastr);
void ler_cabecalho(FILE *arquivo);
void lerCSV(FILE *arquivo);
void ordenacao_crescente_Id();
void decrescente_data_ajuizamento();
void contarIdClasse(int lidos);
int idAssuntoUnico(char id_assunto[][50], int count, const char *new_id);
void mostrar_um_registro();
void mostrar_todos_registros();


//funções de limpeza e manuntenção
void remove_newline(char *str); //  remove o "\n" pelo fgets
void remove_aspas(char *str); //remove o ""
void clean_buffer(); // limpa o buffer do teclado

#endif