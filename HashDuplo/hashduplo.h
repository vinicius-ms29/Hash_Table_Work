#ifndef HASHDUPLO_H
#define HASHDUPLO_H

// INCLUSÃO DE BIBLIOTECAS ==============================
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
//=======================================================

//#define LINHA"\n==================================================\n"

// STRUCT ARMAZENA DADOS ==============================
struct Alunos {
    char nome[100];  // Substituindo string C++ por array de chars
    long long int matricula;
    int flag;
};
//=======================================================

// FUNÇÕES CRIAR VETOR ==============================
int getTamanhoVetor();
int getTamanhoArquivo(const char* nome_arquivo);
int calcularVetor(const char* nome_arquivo, int fator_tamanho);
void lerArquivoParaHash(struct Alunos* hash, int tamanho, const char* nome_arquivo);
//=======================================================

// FUNÇÕES HASH DUPLO ==============================
int calcHash(long long int matricula, int tamanho_vetor);
int calcHash2(long long int matricula, int tamanho_vetor);
int reHash(int ind, int h2, int tamanho_vetor);
//=======================================================

// FUNÇÕES NÚMERO PRIMO ==============================
int verificarPrimo(int primo);
int proximoNumeroPrimo(int primo_tamanho);
//=======================================================

// FUNÇÕES MENU ==============================
int escolhaMenu();
void salvarNoArquivo(struct Alunos* hash, int tamanho_vetor, const char* nome_arquivo);
void menu(struct Alunos* hash, int tamanho_vetor, const char* nome_arquivo);
void salvarNoArquivo(struct Alunos* hash, int tamanho_vetor, const char* nome_arquivo);
//=======================================================

// FUNÇÕES AÇÕES ==============================
void dadosInserir(struct Alunos* hash, const char* nome_arquivo);
void inserir(struct Alunos* hash, const char* nome_arquivo, 
                char* new_nome, long long int new_matricula);
//=======================================================
void dadosExcluir(struct Alunos* hash, int tamanho_vetor);
void excluir(struct Alunos* hash, int tamanho_vetor, long long int matricula);
//=======================================================
void dadosPesquisar(struct Alunos* hash, int tamanho_vetor);
int pesquisar(struct Alunos* hash, int tamanho_vetor, long long int matricula);
//=======================================================
void exibirTotal(const char* nome_arquivo);
void exibirVetor(struct Alunos* hash, int tamanho_vetor);
//=======================================================

#endif
