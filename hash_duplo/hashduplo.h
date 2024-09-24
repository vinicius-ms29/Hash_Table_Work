#ifndef HASHDUPLO_H
#define HASHDUPLO_H

// Arthur Fernandes de Paiva Costa e Vinícius Machado de Souza

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define linha "\n================================================\n"
#define MAX_NOME 100
#define MAX_MATRICULA 20

typedef struct {
    char nome[MAX_NOME];
    char matricula[MAX_MATRICULA];
    int ocupado; // 0: vaga livre, 1: ocupado, -1: removido
} Aluno;

typedef struct {
    Aluno* tabela;
    int tamanho;
    int total_matriculas;
} TabelaHash;

int menuhash();
int eh_primo(int num);
int proximo_primo(int n);
void menu(TabelaHash* tabela);
void remover(TabelaHash* tabela);
void inserir(TabelaHash* tabela);
void imprimir(TabelaHash* tabela);
void pesquisar(TabelaHash* tabela);
int ler_tamanho(const char* arquivo);
TabelaHash* inicializar_tabela(int tamanho);
int calcular_hash(char* matricula, int tamanho);
int calcular_hash2(char* matricula, int tamanho);
void mostrar_total_matriculas(TabelaHash* tabela);
void salvar_dados(TabelaHash* tabela, const char* arquivo);
int remover_matricula(TabelaHash* tabela, char* matricula);
void carregar_dados(TabelaHash* tabela, const char* arquivo);
Aluno* pesquisar_matricula(TabelaHash* tabela, char* matricula);
void inserir_matricula(TabelaHash* tabela, char* nome, char* matricula);
void medir_tempo(void (*funcao)(TabelaHash*), TabelaHash* tabela, const char* nome_funcao);

#endif