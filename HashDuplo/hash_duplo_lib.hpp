#ifndef HASH_DUPLO_LIB
#define HASH_DUPLO_LIB

// INCLUSÃO DE BIBLIOTECAS ==============================
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <ctime>
#include <cmath>
//==============================

#define LINHA "\n==================================================\n"
using namespace std;

// STRUCT ARMAZENA DADOS ==============================
struct Alunos{string nome; long long int matricula; int flag;};
//==============================

// FUNÇÕES CRIAR VETOR ==============================
int getTamanhoVetor();
int getTamanhoArquivo(const string nome_arquivo);
int calcularVetor(const string nome_arquivo, int fator_tamanho);
void lerArquivoParaHash(vector<struct Alunos>& hash, const string nome_arquivo);
//==============================

// FUNÇÕES HASH DUPLO ==============================
int calcHash(long long int matricula, int tamanho_vetor);
int calcHash2(long long int matricula, int tamanho_vetor);
int reHash(int ind, int h2, int tamanho_vetor);
//==============================

// FUNÇÕES NÚMERO PRIMO ==============================
int verificarPrimo(int primo);
int proximoNumeroPrimo(int primo_tamanho);
//==============================

// FUNÇÕES MENU ==============================
int escolhaMenu();
void menu(vector<struct Alunos>& hash, const string nome_arquivo);
void salvarNoArquivo(vector<struct Alunos>& hash, const string nome_arquivo);
//==============================

// FUNÇÕES AÇÕES ==============================
void dadosInserir(vector<struct Alunos>& hash, const string nome_arquivo);
void inserir(vector<struct Alunos>& hash, const string nome_arquivo, 
                string new_nome, long long int new_matricula);
//==============================
void dadosExcluir(vector<struct Alunos>& hash, const string nome_arquivo);
void excluir(vector<struct Alunos>& hash, const string nome_arquivo, long long int matricula);
//==============================
void dadosPesquisar(vector<struct Alunos>& hash, const string nome_arquivo);
int pesquisar(vector<struct Alunos>& hash, const string nome_arquivo, long long int matricula);
//==============================
ostream& exibirTotal(const string nome_arquivo);
void exibirVetor(vector<struct Alunos>& hash, const string nome_arquivo);
//==============================

#endif